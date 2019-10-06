#include "systick.h"

void SysTick_Delay_ms(uint32_t time)
{
	uint32_t count;
	SysTick_Config(41940);
	SysTick->CTRL &= ~(SysTick_CTRL_TICKINT_Msk);
	for(count=0;count<time;count++)
	{
		while(!(SysTick->CTRL & (1<<16)));
	}
	SysTick->CTRL &= ~(SysTick_CTRL_ENABLE_Msk);
}
