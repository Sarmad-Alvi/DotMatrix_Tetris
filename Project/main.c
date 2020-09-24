#include "stm32f10x.h"
#include "clock.h"
#include "led_init.h"
#include "multiplex.h"
#include "blocks.h"
#include "event_handler.h"
#include "shapes.h"
#include <time.h>

uint8_t curr = 1; //tracks the current rotation of a shape
uint8_t newPos = 1; //1 if shape is in new position, 0 otherwise (used to set rotation axis)
uint8_t start[] = {0, 0}; //coordinates on foreground array of starting coordinates of shape
uint8_t currShape; //keeps track of current shape, see shapes.c
uint8_t defaultStart[] = {0, 3}; //starting coordinates of new shape

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
		rotate(mBuffFore_G, curr, start, newPos, currShape);
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
		newPos = 1;
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
