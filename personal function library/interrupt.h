#ifndef _INTERRUPT_H
#define _INTERRUPT_H

#include "MK60D10.h"
#include "general_function.h"


#define Enable_Interrupts  __asm("CPSIE I")
#define Disable_Interrupts __asm("CPSID I")


void Enable_Interrupt_IRQ(int8_t IRQ);
void Disable_Interrupt_IRQ(int8_t IRQ);


#endif /*_INTERRUPT_H*/
