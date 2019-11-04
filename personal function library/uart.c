#include "uart.h"

void Init_UART(uint32_t baud)
{
	uint64_t sbrvl = 0;
	uint8_t brfavl = 0;
	SIM->SCGC4 |= SIM_SCGC4_UART2_MASK;

	PORTD->PCR[2] |= 0x3<<8;
	PORTD->PCR[2] |= 0x3<<8;
	
	UART2->C1 &= ~UART_C1_PE_MASK;   //У��λ
	UART2->C1 &= ~UART_C1_M_MASK;    //����λ
	UART2->C2 &= ~UART_C2_RE_MASK;   //���ܹر�
	UART2->C2 &= ~UART_C2_TE_MASK;   //���͹ر�
	
	sbrvl = 2*UART2_CLOCK/baud;      //���ò�����
	brfavl = (sbrvl & 0x1F);
	sbrvl >>= 5;
	UART2->C4 &= ~0x1F;
	UART2->C4 |= brfavl;
	UART2->BDL &= ~0xFF;
	UART2->BDL |= (sbrvl & 0xFF);
	UART2->BDH &= ~0x1F;
	UART2->BDH |= ((sbrvl>>8) & 0x1F);
	
	
	UART2->C2 |= UART_C2_RE_MASK;   //��������
	UART2->C2 |= UART_C2_TE_MASK;   //��������
	UART2->C2 |= UART_C2_RIE_MASK;  //�����������жϺ�DMA�����ж�
}
void UART2_TransmitChar(char ch)
{
	while(!(UART2->S1 & UART_S1_TDRE_MASK));
	UART2->D = (unsigned char)ch;
}
void UART2_TransmitString(char	*str)
{
	uint32_t i,length;
	length = strlen(str);
	for(i = 0;i<length;i++) UART2_TransmitChar(str[i]);
}
char UART2_ReceiveChar(void)
{
	while(!(UART2->S1 & UART_S1_RDRF_MASK));
	return UART2->D;
}

