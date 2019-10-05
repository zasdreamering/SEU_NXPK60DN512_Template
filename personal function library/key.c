#include "key.h"
#include "interrupt.h"


const uint8_t Key_Matrix_Scan_Sequence[4]={1<<4,1<<5,1<<6,1<<7};
const uint8_t Key_Matrix_Sequence[16]={0x1,0x2,0x3,0xA,0x4,0x5,0x6,0xB,0x7,0x8,0x9,0xC,0x10,0x12,0x13,0xD};

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
	PTC->PDOR |= (0xFF<<4);
	PTC->PDDR &= ~(0xF<<8);
}

void Enable_Key_Interrupt(void)
{
	uint8_t i;
	Disable_Interrupts;
	Enable_Interrupt_IRQ(PORTC_IRQn);
	for(i=12;i<16;i++)	PORTC->PCR[i] |= (1<<8)|0x3|0x9<<16;
	NVIC_SetPriorityGrouping(0);
	NVIC_SetPriority(PORTC_IRQn,1);
	Enable_Interrupts;
}

uint8_t Key_Scan(uint8_t Key_Num)
{
	if((PTC->PDIR & (1<<(16-Key_Num))) == 0) 
	{
		while((PTC->PDIR & (1<<(16-Key_Num))) == 0);  //松键检测
		return ON;
	}
	else
		return OFF;
}


uint8_t Key_Matrix_Scan(void)
{
	uint8_t Key_Matrix_Scan_Row = 0;
	uint8_t Key_Matrix_Scan_Column = 0;
	PTC->PDOR |= (0xF<<4);
	while(1)
	{
		PTC->PDOR &= ~Key_Matrix_Scan_Sequence[Key_Matrix_Scan_Row];
		for(Key_Matrix_Scan_Column=0;Key_Matrix_Scan_Column<4;Key_Matrix_Scan_Column++)
		{
			if((PTC->PDIR & (1<<(8+Key_Matrix_Scan_Column))) == 0) 
			{
				while((PTC->PDIR & (1<<(8+Key_Matrix_Scan_Column))) == 0);
				return Key_Matrix_Sequence[4*Key_Matrix_Scan_Row+Key_Matrix_Scan_Column];
			}	
		}
		PTC->PDOR |= (0xF<<4);
		if(++Key_Matrix_Scan_Row==4) Key_Matrix_Scan_Row=0;
	}
}

uint8_t Get_Key_Matrix_Sequence(uint8_t Num)  //参数是16个按键  1-16
{
	return Key_Matrix_Sequence[Num-1];
}
