#include "nixie_tube.h"

const uint8_t 	Nixie_Tube_Num[]  = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};
uint8_t Tube_Show_Num[4] = {0xFF,0xFF,0xFF,0xFF};


void Init_Nixie_Tube(void)     //��ʼ�������
{
	uint8_t i;
	
	
	//������ؼĴ���ʱ��
	SIM->SCGC5 |= PORTB_CLK_ON|PORTC_CLK_ON;
	
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



void Light_Nixie_Tube(uint8_t Tube_Num,uint8_t State)    //����������ܺ���
{
	if(State)
		PTC->PCOR |=(1<<Tube_Num);
	else
		PTC->PSOR |=(1<<Tube_Num);
}



void Light_Nixie_Tube_Num(uint8_t Num,uint8_t State)     //����ܵ���������
{
	if(State)
	{
		PTB->PDOR &= ~(0xFF<<16);
		PTB->PDOR |= (Nixie_Tube_Num[Num]<<16);
	}
	else
		PTB->PDOR |= (0xFF<<16);
}

void Light_Nixie_Tube_NumWithPoint(uint8_t Num,uint8_t State)    //����ܵ������ִ�С��
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


void Tube_Positive_Count(void)        //�����������  ʮ����
{
	uint8_t Scan=0;
	uint8_t Second_Count=0;
	int8_t Behind_Two_Num=0;
	int8_t Front_Two_Num=0;
	while(1)
	{
		if(++Second_Count==200)
		{
			Second_Count=0;
			if(++Behind_Two_Num==100)
			{
				Behind_Two_Num=0;
				if(++Front_Two_Num==100) Front_Two_Num=0;
			}
		}
		Tube_Show_Num[3] = Behind_Two_Num%10;
		Tube_Show_Num[2] = Behind_Two_Num/10;
		Tube_Show_Num[1] = Front_Two_Num%10;
		Tube_Show_Num[0] = Front_Two_Num/10;
		PTB->PDOR &= ~(0xFF<<16);
		Light_Nixie_Tube_Num(Tube_Show_Num[Scan],ON);
		Light_Nixie_Tube(Scan,ON);
		delay5ms();
		Light_Nixie_Tube(Scan,OFF);
		if(++Scan==4) Scan=0;
	}
}


void Tube_Negative_Count(void)       //����ܵ�����  ʮ����
{
	uint8_t Scan=0;
	uint8_t Second_Count=0;
	int8_t Behind_Two_Num=99;
	int8_t Front_Two_Num=99;
	while(1)
	{
		if(++Second_Count==200)
		{
			Second_Count=0;
			if(--Behind_Two_Num==-1)
			{
				Behind_Two_Num=0;
				if(--Front_Two_Num==-1) Front_Two_Num=0;
			}
		}
		Tube_Show_Num[3] = Behind_Two_Num%10;
		Tube_Show_Num[2] = Behind_Two_Num/10;
		Tube_Show_Num[1] = Front_Two_Num%10;
		Tube_Show_Num[0] = Front_Two_Num/10;
		PTB->PDOR &= ~(0xFF<<16);
		Light_Nixie_Tube_Num(Tube_Show_Num[Scan],ON);
		Light_Nixie_Tube(Scan,ON);
		delay5ms();
		Light_Nixie_Tube(Scan,OFF);
		if(++Scan==4) Scan=0;
	}
}


void Tube_Negative_Count_Num(uint32_t Num)     //����ܰ����ֵ�����   ʮ����
{
	uint8_t Scan=0;
	uint8_t Second_Count=0;
	int8_t Behind_Two_Num=Num%100;
	int8_t Front_Two_Num=Num/100;
	while(1)
	{
		if(++Second_Count==200)
		{
			Second_Count=0;
			if(--Behind_Two_Num == -1)
			{
				Behind_Two_Num=0;
				if(--Front_Two_Num == -1) Front_Two_Num=0;
			}
		}
		Tube_Show_Num[3] = Behind_Two_Num%10;
		Tube_Show_Num[2] = Behind_Two_Num/10;
		Tube_Show_Num[1] = Front_Two_Num%10;
		Tube_Show_Num[0] = Front_Two_Num/10;
		PTB->PDOR &= ~(0xFF<<16);
		Light_Nixie_Tube_Num(Tube_Show_Num[Scan],ON);
		Light_Nixie_Tube(Scan,ON);
		delay5ms();
		Light_Nixie_Tube(Scan,OFF);
		if(++Scan==4) Scan=0;
	}
}

