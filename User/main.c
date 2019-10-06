#include "MK60D10.h"
#include "nixie_tube.h"
#include "led.h"
#include "key.h"
#include "interrupt.h"
#include "systick.h"

int main(void)
{
	Init_Led();
	while(1)
	{
		SysTick_Delay_ms(500);
		Toggle_Led_Num(1,ON);
	}
}

