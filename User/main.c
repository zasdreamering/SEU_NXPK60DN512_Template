#include "SystemConfig.h"
#include "nixie_tube.h"
#include "led.h"
#include "key.h"
#include "uart.h"

uint8_t ShowNum[4] = {0xFF,0xFF,0xFF,0xFF};
uint8_t Count_State = OFF;
char SendMessage[] = "The number in the tube is 0000\n";
char StartSend = OFF;

int main(void)
{
	uint32_t Count;
	Init_Key();
	Init_Nixie_Tube();
	Enable_Key_Interrupt();
	Init_UART(115200);
	while(1)
	{
		Tube_Pause_Count();
		if(Count_State)
		{
			if(ShowNum[3] != 0xFF)
				Count = (ShowNum[3]*1000+ShowNum[2]*100+ShowNum[1]*10+ShowNum[0]);
			else if(ShowNum[2] != 0xFF)
				Count = (ShowNum[2]*100+ShowNum[1]*10+ShowNum[0]);
			else if(ShowNum[1] != 0xFF)
				Count = (ShowNum[1]*10+ShowNum[0]);
			else
				Count = (ShowNum[0]);
			Tube_Negative_Count_Num(Count);
			Count_State = OFF;
		}
	}
}

