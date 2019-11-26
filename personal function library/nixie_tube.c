#include "nixie_tube.h"
#include "key.h"

const uint8_t 	Nixie_Tube_Num[]  = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};
extern uint8_t Count_State;
extern uint8_t ShowNum[4];

/**
@brief 初始化数码管
*/
void Init_Nixie_Tube(void)     
{
	uint8_t i;
	
	
	//开启相关寄存器时钟
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK|SIM_SCGC5_PORTC_MASK;
	
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

/**
@brief 设置点亮的数码管号码  0-3 3为最高位即数码管最左边一位
*/
void Light_Nixie_Tube(uint8_t Tube_Num,uint8_t State)    
{
	if(State)
		PTC->PCOR |=(1<<(3-Tube_Num));
	else
		PTC->PSOR |=(1<<(3-Tube_Num));
}

/**
@brief 设置数码管点亮的数字
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
@brief 数码管点亮数字带小点
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
@brief 数码管正计数   十进制 
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
@brief 数码管倒计数   十进制  需要输入
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
@brief 循环显示数码管当前的数字
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
@brief 数码管计时功能
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

