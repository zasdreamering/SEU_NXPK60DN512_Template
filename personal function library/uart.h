#ifndef _UART_H
#define _UART_H

#include "SystemConfig.h"


#define UART2_CLOCK 41943040u



void Init_UART(uint32_t baud);
void UART2_TransmitChar(char ch);
void UART2_TransmitString(char	*str);
char UART2_ReceiveChar(void);

#endif /*_UART_H*/
