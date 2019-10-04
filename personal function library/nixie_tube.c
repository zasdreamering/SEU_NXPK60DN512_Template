#include "nixie_tube.h"

const uint8_t 	Nixie_Tube_Num[]  = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};
uint8_t Tube_Show_Num[4] = {0xFF,0xFF,0xFF,0xFF};


void Init_Nixie_Tube(void)     //初始化数码管
{
	uint8_t i;
	
	
	//开启相关寄存器时钟
	SIM->SCGC5 |= PORTB_CLK_ON|PORTC_CLK_ON;
	
	//将相关端口引脚配置为GPIO模式
	for(i=16;i<24;i++) PORTB->PCR[i] |= (1<<8);
	for(i=0;i<4;i++) PORTC->PCR[i] |= (1<<8);
	
	//配置PTC0-PTC4和PTB16-PTB23引脚为输出模式
	PTB->PDDR |= (0xFF<<16);
	PTC->PDDR |= (0xF);
	
	//关闭数码管输出
	PTB->PDOR |= (0xFF<<16);
	PTC->PDOR |= (0xF);
}



void Light_Nixie_Tube(uint8_t Tube_Num,uint8_t State)    //点亮的数码管号码
{
	if(State)
		PTC->PCOR |=(1<<Tube_Num);
	else
		PTC->PSOR |=(1<<Tube_Num);
}



void Light_Nixie_Tube_Num(uint8_t Num,uint8_t State)     //数码管点亮的数字
{
	if(State)
	{
		PTB->PDOR &= ~(0xFF<<16);
		PTB->PDOR |= (Nixie_Tube_Num[Num]<<16);
	}
	else
		PTB->PDOR |= (0xFF<<16);
}

void Light_Nixie_Tube_NumWithPoint(uint8_t Num,uint8_t State)    //数码管点亮数字带小点
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


void Tube_Positive_Count(void)        //数码管正计数  十进制
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


void Tube_Negative_Count(void)       //数码管倒计数  十进制
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


void Tube_Negative_Count_Num(uint32_t Num)     //数码管按数字倒计数   十进制
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

