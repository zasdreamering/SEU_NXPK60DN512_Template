#include "interrupt.h"


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
	Key_Scan();
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
		KEY_0 = OFF;
	}
	if(KEY_1 == ON)
	{
		KEY_1 = OFF;
	}
	if(KEY_2 == ON)
	{
		KEY_2 = OFF;
	}
	if(KEY_3 == ON)
	{
		KEY_F1 = 0;
	}
	if(KEY_4 == ON)
	{
		KEY_F1 = 0;
	}
	if(KEY_5 == ON)
	{
		KEY_5 = OFF;
	}
	if(KEY_6 == ON)
	{
		KEY_6 = OFF;
	}
	if(KEY_7 == ON)
	{
		KEY_7 = OFF;
	}
	if(KEY_8 == ON)
	{
		KEY_8 = OFF;
	}
	if(KEY_9 == ON)
	{
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
		KEY_Star = OFF;
	}
	if(KEY_Well == ON)
	{
		KEY_Well = OFF;
	}
}

