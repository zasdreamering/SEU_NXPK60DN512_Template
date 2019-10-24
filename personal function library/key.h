#ifndef _KEY_H
#define _KEY_H


#include "SystemConfig.h"



extern uint8_t Key_Flag[20];

#define KEY_F1    Key_Flag[0]
#define KEY_F2    Key_Flag[1]
#define KEY_F3    Key_Flag[2]
#define KEY_F4    Key_Flag[3]
#define KEY_1     Key_Flag[4]
#define KEY_2     Key_Flag[5]
#define KEY_3     Key_Flag[6]
#define KEY_A     Key_Flag[7]
#define KEY_4     Key_Flag[8]
#define KEY_5     Key_Flag[9]
#define KEY_6     Key_Flag[10]
#define KEY_B     Key_Flag[11]
#define KEY_7     Key_Flag[12]
#define KEY_8     Key_Flag[13]
#define KEY_9     Key_Flag[14]
#define KEY_C     Key_Flag[15]
#define KEY_Star  Key_Flag[16]
#define KEY_0     Key_Flag[17]
#define KEY_Well  Key_Flag[18]
#define KEY_D     Key_Flag[19]

void Init_Key(void);
void Key_Scan(void);
void Enable_Key_Interrupt(void);


#endif /*_KEY_H*/

