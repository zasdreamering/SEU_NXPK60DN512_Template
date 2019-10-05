#include "interrupt.h"
#include "led.h"


void Enable_Interrupt_IRQ(int8_t IRQ)
{
	uint8_t Div = IRQ/32;
	NVIC->ICPR[Div] |= (1<<(IRQ%32));
	NVIC->ISER[Div] |= (1<<(IRQ%32));
}

void Disable_Interrupt_IRQ(int8_t IRQ)
{
	uint8_t Div = IRQ/32;
	NVIC->ICER[Div] |= (1<<(IRQ%32));
}

void PORTC_IRQHandler()
{
	if(PORTC->ISFR & (1<<15)) 	Toggle_Led_Num(1,ON);
	PORTC->ISFR |= 1<<15;
}

