#include "pit.h"

void Pit_Delay_ms(uint32_t time,uint32_t Pin)
{
	uint32_t count;
	SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;
	PIT->MCR |= PIT_MCR_MDIS_MASK;
	PIT->MCR |= PIT_MCR_FRZ_MASK;
	PIT->CHANNEL[Pin%4].LDVAL = 41940-1;
	PIT->CHANNEL[Pin%4].TCTRL |= PIT_TCTRL_TEN_MASK;
	PIT->CHANNEL[Pin%4].TCTRL |= PIT_TCTRL_TIE_MASK;
//	for(count=0;count<time;count++)
//	{
//	//	while(!(PIT->CHANNEL[Pin%4].TFLG & 1));
//	}
//	PIT->CHANNEL[Pin%4].TCTRL &= ~PIT_TCTRL_TEN_MASK;
}
