#ifndef _LED_H
#define _LED_H



#include "MK60D10.h"
#include "SystemConfig.h"




void Init_Led(void);
void Light_Led_Num(uint8_t Led_Num,uint8_t State);
void Toggle_Led_Num(uint8_t Led_Num,uint8_t State);



#endif /*_LED_H*/
