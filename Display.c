#include <DAVE.h>

uint32_t Display_Address = 0x27;
//Delay function defined here
bool LCD_Waiting;

void	Delay_ISR();
{
	LCD_Waiting = false;
}
void Delay(uint32_t w_time)
{
	LCD_Waiting = true;
	SYSTIMER.RestartTimer(TimerId, w_time * 1000);
}

I2C_Write()
{
	I2C_MASTER_SendStart(&I2C_MASTER_0, Display_Address, XMC_I2C_CH_CMD_WRITE);
	while((XMC_I2C_CH_GetStatusFlag(I2C_MASTER_0.channel) & XMC_I2C_CH_STATUS_FLAG_ACK_RECEIVED) == 0U)
	I2C_MASTER_ClearFlag(&I2C_MASTER_0, I2C_MASTER_CH_STATUS_FLAG_ACK_RECEIVED);
	Delay(15); //Delays 
}
void	SendNibbles(uint8_t Data_en0, uint8_t Data_en1)
{
	I2C_MASTER_TransmitByte(&I2C_MASTER_0, Data_en0);
	while((I2C_MASTER_GetFlagStatus(I2C_MASTER_0,  XMC_I2C_CH_STATUS_FLAG_ACK_RECEIVED) == 0U)
        I2C_MASTER_ClearFlag(&I2C_MASTER_0, XMC_I2C_CH_STATUS_FLAG_ACK_RECEIVED);

	I2C_MASTER_TransmitByte(&I2C_MASTER_0, Data_en1);
        while((I2C_MASTER_GetFlagStatus(I2C_MASTER_0,  XMC_I2C_CH_STATUS_FLAG_ACK_RECEIVED) == 0U)
        I2C_MASTER_ClearFlag(&I2C_MASTER_0, XMC_I2C_CH_STATUS_FLAG_ACK_RECEIVED);

	I2C_MASTER_TransmitByte(&I2C_MASTER_0, Data_en0);
        while((I2C_MASTER_GetFlagStatus(I2C_MASTER_0,  XMC_I2C_CH_STATUS_FLAG_ACK_RECEIVED) == 0U)
        I2C_MASTER_ClearFlag(&I2C_MASTER_0, XMC_I2C_CH_STATUS_FLAG_ACK_RECEIVED);
	Delay(10);
}
void	LCD_SendByte(uint8_t data, int mode_select)
{
	I2C_Write();
	uint8_t	xxxx_4bit = data & F0;
	xxxx_4bit	  = xxxx_4bit | 0x08 | mode_select;
	uint8_t xxxx_enable = xxxx_4bit | 0x04;
	uint8_t yyyy_4bit = (data << 1) & 0xF0;
	yyyy_4bit 	= yyyy_4bit | 0x08 | mode_select;
	uint8_t yyyy_enable = yyyy_enable | 0x04;
	LCD_S(xxxx_4bit, xxxx_enable);
	LCD_SendNibbles(yyyy_4bit, yyyy_enable);
	I2C_Stop();
}
void	LCD_SendBits(uint8_t data)
{
	I2C_MASTER_Transmit(I2C_MASTER_0, true, DisplayAddress, &data, 1, true); // sends 8Bits
	while (I2C_MASTER_IsTxBusy(I2C_MASTER_0));
	uint8_t dataEN = data | 0x04;
	I2C_MASTER_Transmit(I2C_MASTER_0, true, DisplayAddress, &dataEN, 1, true)
	while(I2C_MASTER_IsTxBusy(I2C_MASTER_0));
	I2C_MASTER_Transmit(I2C_MASTER_0, true, DisplayAddress, &data, 1, true) 
        while(I2C_MASTER_IsTxBusy(I2C_MASTER_0)); 
}


