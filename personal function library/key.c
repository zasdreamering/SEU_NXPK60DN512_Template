#include "key.h"

void Init_Key(void)
{
	uint8_t i;
	
	
	//Dependant Key Initation
	SIM->SCGC5 |= PORTC_CLK_ON;
	for(i=12;i<16;i++) 
	{
		PORTC->PCR[i] |= (1<<8);
		PORTC->PCR[i] |= 0x3;
	}
	PTC->PDDR &= ~(0xF<<12);
	PTC->PDOR |= (0xF<<12);
	
	
	//Key Matrix Initation
	for(i=4;i<12;i++) PORTC->PCR[i] |= (1<<8);
	for(i=8;i<12;i++) PORTC->PCR[i] |= 0x3;
	PTC->PDDR |= (0xF<<4);
	PTC->PDDR &= ~(0xF<<8);
	PTC->PDOR |= (0xFF<<4);
	
}

uint8_t Key_Scan(uint8_t Key_Num)
{
	if((PTC->PDIR&(1<<(16-Key_Num))) == 0) 
	{
		while((PTC->PDIR&(1<<(16-Key_Num))) == 0);  //ËÉ¼ü¼ì²â
		return ON;
	}
	else
		return OFF;
}


uint8_t Key_Matrix_Scan(void)
{
	
}