#ifndef _INTERRUPT_H
#define _INTERRUPT_H

#include "MK60D10.h"
#include "led.h"
#include "key.h"
#include "uart.h"


#define Enable_Interrupts  __asm("CPSIE I")
#define Disable_Interrupts __asm("CPSID I")


void Enable_Interrupt_IRQ(IRQn_Type IRQ);
void Disable_Interrupt_IRQ(IRQn_Type IRQ);


#endif /*_INTERRUPT_H*/
