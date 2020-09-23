#include "stm32f10x.h"
#include "clock.h"
#include "led_init.h"
#include "multiplex.h"
#include "blocks.h"
#include "event_handler.h"
#include "shapes.h"
#include <time.h>

int curr = 1;
int newPos = 1;
int start[] = {0, 0};
	
int main(void)
{
	clockInit();
	pin_init();
	EXTI_init();
	setPinsHigh(1);
	setPinsHigh(2);
	

	
	while (1)
	{
		refreshMatrix(9, 8, 10, 11, mBuffFore_G);
		delay(20);
	}

}

void EXTI15_10_IRQHandler(void)
{
	if (EXTI->PR & EXTI_PR_PR12)
	{
		
		EXTI->PR |= EXTI_PR_PR12;
		rotate(mBuffFore_G, curr, start, newPos);
		newPos = 0;
		if (curr == 4)
		{
			curr = 1;
		}
		else
		{
			curr++;
		}
	}
}


 void EXTI0_IRQHandler(void)
{
	if (EXTI->PR & EXTI_PR_PR0)
	{
		
		EXTI->PR |= EXTI_PR_PR0;
		right(mBuffFore_G, newPos);
	}
}
void EXTI4_IRQHandler(void)
{
	if (EXTI->PR & EXTI_PR_PR4)
	{
		EXTI->PR |= EXTI_PR_PR4;
		down(mBuffFore_G);
	}
}
