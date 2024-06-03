#include<DAVE.h>
#ifndef DISPLAY_H_
#def	DISPLAY_H_

void 	LCD_Init();	// Initializes LCD
void	LCD_PrintOutput(char **Zeile1, char **Zeile2); //Write on Display
void	LCD_Display_ISR(); 
void	Delay(uint32_t ms);  //Delay Function
void	LCD_SendByte(uint8_t data, int cmd);
void	Receive_Data();
uint32_t	TimerId;
#endif

