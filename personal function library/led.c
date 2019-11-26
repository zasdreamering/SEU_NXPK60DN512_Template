#include "led.h"


void Init_Led(void)
{
	uint8_t i=0;
	
	
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
	for(i=0;i<4;i++)	PORTE->PCR[i] |= (1<<8);
	PTE->PDDR |= 0xF;
	PTE->PDOR |= 0xF;
}

void Light_Led_Num(uint8_t Led_Num,uint8_t State)
{
	if(State)
		PTE->PCOR |= (1<<(Led_Num-1));
	else
		PTE->PSOR |= (1<<(Led_Num-1));
}

void Toggle_Led_Num(uint8_t Led_Num,uint8_t State)
{
	if(State)
		PTE->PTOR |= (1<<(Led_Num-1));
}
