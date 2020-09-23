#include "stm32f10x.h"
#include "blocks.h"
#include "multiplex.h"

void EXTI_init(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	AFIO->EXTICR[3] |= AFIO_EXTICR4_EXTI12_PB;
	EXTI->IMR |= EXTI_IMR_MR12;
	EXTI->FTSR |= EXTI_RTSR_TR12;
	NVIC->ISER[1] |= NVIC_ISER_SETENA_8;
	
	
	
	AFIO->EXTICR[1] &= ~AFIO_EXTICR2_EXTI4;
	AFIO->EXTICR[0] &= ~AFIO_EXTICR1_EXTI0;
	EXTI->IMR |= EXTI_IMR_MR0 | EXTI_IMR_MR4;;
	EXTI->FTSR |= EXTI_FTSR_TR4 | EXTI_FTSR_TR0;;
	NVIC->ISER[0] |= NVIC_ISER_SETENA_10 | NVIC_ISER_SETENA_6;
}

