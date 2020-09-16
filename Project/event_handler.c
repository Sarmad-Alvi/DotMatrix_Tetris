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
}

