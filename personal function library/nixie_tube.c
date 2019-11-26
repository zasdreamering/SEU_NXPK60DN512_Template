#include "nixie_tube.h"
#include "key.h"

const uint8_t 	Nixie_Tube_Num[]  = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};
extern uint8_t Count_State;
extern uint8_t ShowNum[4];

/**
@brief ��ʼ�������
*/
void Init_Nixie_Tube(void)     
{
	uint8_t i;
	
	
	//������ؼĴ���ʱ��
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK|SIM_SCGC5_PORTC_MASK;
	
	//����ض˿���������ΪGPIOģʽ
	for(i=16;i<24;i++) PORTB->PCR[i] |= (1<<8);
	for(i=0;i<4;i++) PORTC->PCR[i] |= (1<<8);
	
	//����PTC0-PTC4��PTB16-PTB23����Ϊ���ģʽ
	PTB->PDDR |= (0xFF<<16);
	PTC->PDDR |= (0xF);
	
	//�ر���������
	PTB->PDOR |= (0xFF<<16);
	PTC->PDOR |= (0xF);
}

/**
@brief ���õ���������ܺ���  0-3 3Ϊ���λ������������һλ
*/
void Light_Nixie_Tube(uint8_t Tube_Num,uint8_t State)    
{
	if(State)
		PTC->PCOR |=(1<<(3-Tube_Num));
	else
		PTC->PSOR |=(1<<(3-Tube_Num));
}

/**
@brief ��������ܵ���������
*/
void Light_Nixie_Tube_Num(uint8_t Num,uint8_t State)     
{
	if(State)
	{
		PTB->PDOR &= ~(0xFF<<16);
		PTB->PDOR |= (Nixie_Tube_Num[Num]<<16);
	}
	else
		PTB->PDOR |= (0xFF<<16);
}

/**
@brief ����ܵ������ִ�С��
*/
void Light_Nixie_Tube_NumWithPoint(uint8_t Num,uint8_t State)    
{
	if(State)
	{
		PTB->PDOR &= ~(0xFF<<16);
		PTB->PDOR |= (Nixie_Tube_Num[Num]<<16);
		PTB->PDOR &= ~Point;
	}
	else
		PTB->PDOR |= (0xFF<<16);
}


/**
@brief �����������   ʮ���� 
*/
uint8_t Tube_Positive_Count(void)  
{
	uint8_t Scan=0;
	uint8_t Second_Count=0;
	int8_t Behind_Two_Num=0;
	int8_t Front_Two_Num=0;
	while(1)
	{
		Key_Scan();
		if(++Second_Count==200)
			{
				Second_Count=0;
				if(++Behind_Two_Num==100)
					{
						Behind_Two_Num=0;
						if(++Front_Two_Num==100) Front_Two_Num=0;
					}
			}
			if(Count_State)
			{
				ShowNum[0] = Behind_Two_Num%10;
				ShowNum[1] = Behind_Two_Num/10;
				ShowNum[2] = Front_Two_Num%10;
				ShowNum[3] = Front_Two_Num/10;
				PTB->PDOR &= ~(0xFF<<16);
				Light_Nixie_Tube_Num(ShowNum[Scan],ON);
				Light_Nixie_Tube(Scan,ON);
				SysTick_Delay_ms(5);
				Light_Nixie_Tube(Scan,OFF);
				if(++Scan==4) Scan=0;
			}
			else
				return 0;
	}
}

/**
@brief ����ܵ�����   ʮ����  ��Ҫ����
*/

uint8_t Tube_Negative_Count_Num(uint32_t Num)     
{
	uint8_t Scan=0;
	uint8_t Second_Count=0;
	int8_t Behind_Two_Num=Num%100;
	int8_t Front_Two_Num=Num/100;
	while(1)
	{
		
		Key_Scan();
		if(++Second_Count==200)
			{
				Second_Count=0;
				if(--Behind_Two_Num == -1)
					{
						Behind_Two_Num=99;
						if(--Front_Two_Num == -1) 
							{
								Front_Two_Num  = 0;
								Behind_Two_Num = 0;
								return 0;
							}
					}
			}
			if(Count_State)
			{
				ShowNum[0] = Behind_Two_Num%10;
				ShowNum[1] = Behind_Two_Num/10;
				ShowNum[2] = Front_Two_Num%10;
				ShowNum[3] = Front_Two_Num/10;
				PTB->PDOR &= ~(0xFF<<16);
				Light_Nixie_Tube_Num(ShowNum[Scan],ON);
				Light_Nixie_Tube(Scan,ON);
				SysTick_Delay_ms(5);
				Light_Nixie_Tube(Scan,OFF);
				if(++Scan==4) Scan=0;
			}
			else
				return 0;
	}
}
/**
@brief ѭ����ʾ����ܵ�ǰ������
*/

uint8_t Tube_Pause_Count(void)
{
	uint8_t Scan=0;
	while(1)
	{
		if(!Count_State)
		{
			Key_Scan();
			PTB->PDOR &= ~(0xFF<<16);
			Light_Nixie_Tube_Num(ShowNum[Scan],ON);
			Light_Nixie_Tube(Scan,ON);
			SysTick_Delay_ms(5);
			Light_Nixie_Tube(Scan,OFF);
			if(++Scan==4) Scan=0;
		}
		else
			return 0;
	}
}

/**
@brief ����ܼ�ʱ����
*/
uint8_t Tube_Time_Count(void)	
{
	uint8_t Scan=0;
	uint8_t Second_Count=0;
	int8_t Behind_Two_Num=0;
	int8_t Front_Two_Num=0;
	while(1)
	{
		Key_Scan();
		if(++Second_Count==200)
			{
				Second_Count=0;
				if(++Behind_Two_Num==60)
					{
						Behind_Two_Num=0;
						if(++Front_Two_Num==100) Front_Two_Num=0;
					}
			}
			if(Count_State)
			{
				ShowNum[0] = Behind_Two_Num%10;
				ShowNum[1] = Behind_Two_Num/10;
				ShowNum[2] = Front_Two_Num%10;
				ShowNum[3] = Front_Two_Num/10;
				PTB->PDOR &= ~(0xFF<<16);
				Light_Nixie_Tube_Num(ShowNum[Scan],ON);
				Light_Nixie_Tube(Scan,ON);
				SysTick_Delay_ms(5);
				Light_Nixie_Tube(Scan,OFF);
				if(++Scan==4) Scan=0;
			}
			else
				return 0;
	}
}

