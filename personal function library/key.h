#ifndef _KEY_H
#define _KEY_H


#include "MK60D10.h"
#include "general_function.h"



void Init_Key(void);
uint8_t Key_Scan(uint8_t Key_Num);
void Enable_Key_Interrupt(void);
uint8_t Key_Matrix_Scan(void);
uint8_t Get_Key_Matrix_Sequence(uint8_t Num);



#endif /*_KEY_H*/

