#ifndef _GENERAL_DEFINE_H
#define _GENERAL_DEFINE_H

#include "MK60D10.h"

#define ON		1
#define OFF		0

#define PORTA_CLK_ON	(1 << 9)
#define PORTB_CLK_ON	(1 << 10)
#define PORTC_CLK_ON	(1 << 11)
#define PORTD_CLK_ON	(1 << 12)
#define PORTE_CLK_ON	(1 << 13)


void delay5ms(void);
void delay1s(void);


#endif /*GENERAL_DEFINE_H*/
