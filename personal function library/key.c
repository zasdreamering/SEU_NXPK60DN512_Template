#include "key.h"

const uint8_t Key_Matrix_Scan_Sequence[4]={1<<4,1<<5,1<<6,1<<7};  //定义扫描序列

//定义矩阵按键属性
//const uint8_t Key_Matrix_Sequence[17]={0x0,0x1,0x2,0x3,0xA,0x4,0x5,0x6,0xB,0x7,0x8,0x9,0xC,0x10,0x12,0x13,0xD};


/**
@brief 按键标志位
1:按下
0：松开
0-3：F1-F4
4-19:矩阵按键
*/
uint8_t Key_Flag[20]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	
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
	for(i=8;i<12;i++) 	PORTC->PCR[i] |= (1<<8)|0x3|0x9<<16;
	for(i=12;i<16;i++)	PORTC->PCR[i] |= (1<<8)|0x3|0x9<<16;
	NVIC_SetPriorityGrouping(0);
	NVIC_SetPriority(PORTC_IRQn,7);
	Enable_Interrupts;
}

void Key_Scan(void)
{
	uint8_t i=0;
	uint8_t Key_Matrix_Scan_Row = 0;
	uint8_t Key_Matrix_Scan_Column = 0;
	for(i=12;i<15;i++)
	{
		if((PTC->PDIR & (1<<i)) == 0)
			Key_Flag[15-i] = 1;
		else
			Key_Flag[15-i] = 0;
	}
	for(Key_Matrix_Scan_Row=0;Key_Matrix_Scan_Row<4;Key_Matrix_Scan_Row++)
	{
		PTC->PDOR |= (0xF<<4);
		PTC->PDOR &= ~Key_Matrix_Scan_Sequence[Key_Matrix_Scan_Row];
		for(Key_Matrix_Scan_Column=0;Key_Matrix_Scan_Column<4;Key_Matrix_Scan_Column++)
		{
			if((PTC->PDIR & (1<<(8+Key_Matrix_Scan_Column))) == 0) 
				Key_Flag[Key_Matrix_Scan_Row*4+Key_Matrix_Scan_Column+4] = 1;
			else 
				Key_Flag[Key_Matrix_Scan_Row*4+Key_Matrix_Scan_Column+4] = 0;
		}
	}
}


//uint8_t Get_Key_Matrix_Num(void)   //扫描一个周期，确定按下哪一个键
//{
//	uint8_t Key_Matrix_Scan_Row = 0;
//	uint8_t Key_Matrix_Scan_Column = 0;
//	PTC->PDOR |= (0xF<<4);
//	for(Key_Matrix_Scan_Row=0;Key_Matrix_Scan_Row<4;Key_Matrix_Scan_Row++)
//	{
//		PTC->PDOR &= ~Key_Matrix_Scan_Sequence[Key_Matrix_Scan_Row];
//		for(Key_Matrix_Scan_Column=0;Key_Matrix_Scan_Column<4;Key_Matrix_Scan_Column++)
//		{
//			if((PTC->PDIR & (1<<(8+Key_Matrix_Scan_Column))) == 0) 
//			{
//				while((PTC->PDIR & (1<<(8+Key_Matrix_Scan_Column))) == 0);
//				return Key_Matrix_Sequence[4*Key_Matrix_Scan_Row+Key_Matrix_Scan_Column+1];
//			}	
//		}
//		PTC->PDOR |= (0xF<<4);
//	}
//	return 0;
//}

//void Key_Matrix_Scan(void)   //扫描一个周期，用来扫描触发中断，需放在while（1）使用
//{
//	uint8_t Key_Matrix_Scan_Row = 0;
//	uint8_t Key_Matrix_Scan_Column = 0;
//	PTC->PDOR |= (0xF<<4);
//	for(Key_Matrix_Scan_Row=0;Key_Matrix_Scan_Row<4;Key_Matrix_Scan_Row++)
//	{
//		PTC->PDOR &= ~Key_Matrix_Scan_Sequence[Key_Matrix_Scan_Row];
//		for(Key_Matrix_Scan_Column=0;Key_Matrix_Scan_Column<4;Key_Matrix_Scan_Column++)
//		{
//			if((PTC->PDIR & (1<<(8+Key_Matrix_Scan_Column))) == 0) 
//			{
//				SysTick_Delay_ms(20);
//			}	
//		}
//		PTC->PDOR |= (0xF<<4);
//	}
//}

//uint8_t Get_Key_Matrix_Sequence(uint8_t Num)  //参数是16个按键  1-16
//{
//	return Key_Matrix_Sequence[Num];
//}

