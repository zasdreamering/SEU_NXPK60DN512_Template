#include "adc.h"


void Init_ADC0(void)
{
	SIM->SCGC6   |= SIM_SCGC6_ADC0_MASK;
	
	ADC0->CFG1   |= ADC_CFG1_ADIV(0x2)     |
	                ADC_CFG1_ADLSMP_MASK   |
	                ADC_CFG1_MODE(0x3);
	ADC0->CFG2   |= ADC_CFG2_ADLSTS(0)     |
	                ADC_CFG2_ADHSC_MASK;
	ADC0->SC3    |= ADC_SC3_AVGS(0x3)      |
	                ADC_SC3_AVGE_MASK;
	ADC0->SC1[0] |= ADC_SC1_ADCH(31)       |
	                ADC_SC1_AIEN_MASK;
	Enable_Interrupt_IRQ(ADC0_IRQn);
}


void ADC0_Start(void)
{
	unsigned long Channel;
	Channel = ADC0->SC1[0];
	Channel &= ~(0x1F);
	Channel |= 0x14;
	ADC0->SC1[0] = Channel;
}

