#include "interrupt.h"

extern uint8_t ShowNum[4];
extern uint8_t Count_State;
extern char StartSend;
extern char SendMessage[];


void Enable_Interrupt_IRQ(IRQn_Type IRQ)
{
	uint8_t Div = IRQ/32;
	NVIC->ICPR[Div] |= (1<<(IRQ%32));
	NVIC->ISER[Div] |= (1<<(IRQ%32));
}

void Disable_Interrupt_IRQ(IRQn_Type IRQ)
{
	uint8_t Div = IRQ/32;
	NVIC->ICER[Div] |= (1<<(IRQ%32));
}

void PORTC_IRQHandler()
{
	int8_t i=0;
	Key_Scan();
	if(Count_State == ON)
			for(i=0;i<4;i++) ShowNum[i]=0xFF;
	if(KEY_F1 == ON)
	{
		KEY_F1 = OFF;
	}
	if(KEY_F2 == ON)
	{
		KEY_F2 = OFF;
	}
	if(KEY_F3 == ON)
	{
		KEY_F3 = OFF;
	}
	if(KEY_F4 == ON)
	{
		KEY_F4 = OFF;
	}
	if(KEY_0 == ON)
	{
		for(i=0;i<3;i++) 
		{
			ShowNum[3-i] = ShowNum[2-i];
		}
		ShowNum[0] = 0;
		KEY_0 = OFF;
	}
	if(KEY_1 == ON)
	{
		for(i=0;i<3;i++) 
		{
			ShowNum[3-i] = ShowNum[2-i];
		}
		ShowNum[0] = 1;
		KEY_1 = OFF;
	}
	if(KEY_2 == ON)
	{
		for(i=0;i<3;i++) 
		{
			ShowNum[3-i] = ShowNum[2-i];
		}
		ShowNum[0] = 2;
		KEY_2 = OFF;
	}
	if(KEY_3 == ON)
	{
		for(i=0;i<3;i++) 
		{
			ShowNum[3-i] = ShowNum[2-i];
		}
		ShowNum[0] = 3;
		KEY_3 = 0;
	}
	if(KEY_4 == ON)
	{
		for(i=0;i<3;i++) 
		{
			ShowNum[3-i] = ShowNum[2-i];
		}
		ShowNum[0] = 4;
		KEY_4 = 0;
	}
	if(KEY_5 == ON)
	{
		for(i=0;i<3;i++) 
		{
			ShowNum[3-i] = ShowNum[2-i];
		}
		ShowNum[0] = 5;
		KEY_5 = OFF;
	}
	if(KEY_6 == ON)
	{
		for(i=0;i<3;i++) 
		{
			ShowNum[3-i] = ShowNum[2-i];
		}
		ShowNum[0] = 6;
		KEY_6 = OFF;
	}
	if(KEY_7 == ON)
	{
		for(i=0;i<3;i++) 
		{
			ShowNum[3-i] = ShowNum[2-i];
		}
		ShowNum[0] = 7;
		KEY_7 = OFF;
	}
	if(KEY_8 == ON)
	{
		for(i=0;i<3;i++) 
		{
			ShowNum[3-i] = ShowNum[2-i];
		}
		ShowNum[0] = 8;
		KEY_8 = OFF;
	}
	if(KEY_9 == ON)
	{
		for(i=0;i<3;i++) 
		{
			ShowNum[3-i] = ShowNum[2-i];
		}
		ShowNum[0] = 9;
		KEY_9 = OFF;
	}
	if(KEY_A == ON)
	{
		KEY_A = OFF;
	}
	if(KEY_B == ON)
	{
		KEY_B = OFF;
	}
	if(KEY_C == ON)
	{
		KEY_C = OFF;
	}
	if(KEY_D == ON)
	{
		KEY_D = OFF;
	}
	if(KEY_Star == ON)
	{
		if(StartSend)
			UART2_TransmitString(SendMessage);
		KEY_Star = OFF;
	}
	Count_State = OFF;
	if(KEY_Well == ON)
	{
		Count_State = ON;
		KEY_Well = OFF;
	}
	for(i=8;i<16;i++) PORTC->PCR[i] |= 1<<24;
}
void UART2_RX_TX_IRQHandler()
{
	StartSend = UART2_ReceiveChar();
}

