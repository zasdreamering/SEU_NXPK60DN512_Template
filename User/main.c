#include "MK60D10.h"
#include "nixie_tube.h"
#include "led.h"
#include "key.h"
#include "interrupt.h"


int main(void)
{
	Init_Led();
	Init_Key();
	Enable_Key_Interrupt();
	while(1)
	{
		
	}
}

