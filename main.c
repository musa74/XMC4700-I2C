#include<DAVE.h>
#include "Display.h"


int main(void)
{
	DAVE_STATUS_t status;
	status = Dave_Init();
	Delay(1000);	//Delay 
	if (status != DAVE_STATUS_SUCCESS)
	{
		XMC_DEBUG("Apps Initialization Failed"); // message to Debugger
		while(1U) // runs indefinitely 
		{
		}
	}	
	LCD_init()
	char *Zeile1, Zeile2;
	Zeile1 = "I saw a Saw";
	Zeile2 = "That can saw";
	while(1U)
	{
		
	}
}
