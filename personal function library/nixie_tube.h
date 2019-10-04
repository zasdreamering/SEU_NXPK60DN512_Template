#ifndef _NIXIE_TUBE_H
#define _NIXIE_TUBE_H

#include "MK60D10.h"
#include "general_function.h"



#define Point (1<<23)




void delay1s(void);
void delay5ms(void);
void Init_Nixie_Tube(void);
void Light_Nixie_Tube(uint8_t Tube_Num,uint8_t State);
void Light_Nixie_Tube_Num(uint8_t Num,uint8_t State);
void Light_Nixie_Tube_NumWithPoint(uint8_t Num,uint8_t State);
void Tube_Positive_Count(void);
void Tube_Negative_Count(void);
void Tube_Negative_Count_Num(uint32_t Num);



#endif /*_NIXIE_TUBE_H*/
