#include "MK60D10.h"
#include "nixie_tube.h"
#include "led.h"
#include "key.h"



int main(void)
{
	Init_Led();
	Init_Key();
	while(1)
	{
		if(Key_Matrix_Scan() == Get_Key_Matrix_Sequence(1)) Toggle_Led_Num(2,ON);
		delay5ms();
	}
}

