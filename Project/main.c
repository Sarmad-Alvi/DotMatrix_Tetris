#include "stm32f10x.h"
#include "clock.h"
#include "led_init.h"
#include "multiplex.h"
#include "blocks.h"
#include "event_handler.h"
#include "shapes.h"
#include <time.h>
#include <stdlib.h>


uint8_t curr = 1; //tracks the current rotation of a shape
uint8_t newPos = 1; //1 if shape is in new position, 0 otherwise (used to set rotation axis)
uint8_t start[] = {0, 0}; //coordinates on foreground array of starting coordinates of shape
uint8_t currShape = 1; //keeps track of current shape, see shapes.c
uint8_t defaultStart[] = {0, 3}; //starting coordinates of new shape
int randNum;
_Bool state = 1;
int count = 0;

int main(void)
{
	clockInit();
	pin_init();
	EXTI_init();

	setPinsHigh(4);
	setPinsHigh(5);
	setPinsHigh(6);
	setPinsHigh(7);
	
	currShape = 0;
	delay(50);
	insertS(currShape, defaultStart, mBuffFore_G);
	
	while (1)
	{
		refreshMatrix(9, 8, 10, 11, mBuffFore_G);
		refreshMatrix(9, 8, 10, 11, mBuffBack_G);
		
		if (count == 100)
		{
			ReF(mBuffFore_G, mBuffBack_G, randNum, defaultStart);
			count = 0;
			newPos = 1;
			checkRow(mBuffFore_G, mBuffBack_G);
		}
		else
			count++;
	}


}

void TIM4_IRQHandler(void)
{
	state = 1;
	TIM4->SR &= ~TIM_SR_UIF;
	TIM4->CR1 &= ~TIM_CR1_CEN;

}


 void EXTI0_IRQHandler(void)
{
	if (state == 1 && EXTI->PR & EXTI_PR_PR0)
	{
		state = 0;
		EXTI->PR |= EXTI_PR_PR0;
		TIM4->CR1 |= TIM_CR1_CEN;
		state = 0;
		left(mBuffFore_G, mBuffBack_G);
		newPos = 1;
	}
}

 void EXTI1_IRQHandler(void)
{
	if (state == 1 && EXTI->PR & EXTI_PR_PR1)
	{
		state = 0;
		EXTI->PR |= EXTI_PR_PR1;
		TIM4->CR1 |= TIM_CR1_CEN;
		state = 0;
		down(mBuffFore_G, mBuffBack_G);
		newPos = 1;
	}
}

 void EXTI2_IRQHandler(void)
{
	if (state == 1 && EXTI->PR & EXTI_PR_PR2)
	{
		state = 0;
		EXTI->PR |= EXTI_PR_PR2;
		TIM4->CR1 |= TIM_CR1_CEN;
		state = 0;
		right(mBuffFore_G, mBuffBack_G);
		newPos = 1;
	}
}

void EXTI15_10_IRQHandler(void)
{
	if (state == 1 && EXTI->PR & EXTI_PR_PR12)
	{
		state = 0;
		EXTI->PR |= EXTI_PR_PR12;
		TIM4->CR1 |= TIM_CR1_CEN;
		
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


