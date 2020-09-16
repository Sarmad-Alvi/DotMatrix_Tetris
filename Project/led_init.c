#include "stm32f10x.h"
#include "led_init.h"
#include <string.h>
int lookUp(int y);
int lookUp1(int y);

void pin_init (void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPCEN | RCC_APB2ENR_ADC1EN;
	GPIOA->CRL |= GPIO_CRL_MODE0 | GPIO_CRL_MODE1 | GPIO_CRL_MODE2 | GPIO_CRL_MODE3 | GPIO_CRL_MODE4 | GPIO_CRL_MODE5 | GPIO_CRL_MODE6 | GPIO_CRL_MODE7;
	GPIOA->CRL &= ~GPIO_CRL_CNF0& ~GPIO_CRL_CNF1& ~GPIO_CRL_CNF2& ~GPIO_CRL_CNF3& ~GPIO_CRL_CNF4& ~GPIO_CRL_CNF5& ~GPIO_CRL_CNF6& ~GPIO_CRL_CNF7;
	GPIOC->CRH |= GPIO_CRH_MODE10 | GPIO_CRH_MODE11 | GPIO_CRH_MODE12;
	GPIOC->CRH &= ~GPIO_CRH_CNF10& ~GPIO_CRH_CNF11& ~GPIO_CRH_CNF12;
	
	GPIOA->CRH |= GPIO_CRH_MODE8 | GPIO_CRH_MODE9 | GPIO_CRH_MODE10 | GPIO_CRH_MODE11 | GPIO_CRH_MODE12 | GPIO_CRH_MODE13 | GPIO_CRH_MODE14 | GPIO_CRH_MODE15;
	GPIOA->CRH &= ~GPIO_CRH_CNF8& ~GPIO_CRH_CNF9& ~GPIO_CRH_CNF10& ~GPIO_CRH_CNF11& ~GPIO_CRH_CNF12& ~GPIO_CRH_CNF13& ~GPIO_CRH_CNF14& ~GPIO_CRH_CNF15;
	
	GPIOA->BSRR |= B8 | B9 | B10 | B11 | B12;
	GPIOC->BSRR |= B10 | B11 | B12;
	
	GPIOB->CRL |= GPIO_CRL_MODE1_0;
	GPIOB->CRL &= ~GPIO_CRL_MODE1_0;
}

void setPinsHigh(int y)
{
		if (y > 12)
			GPIOC->BSRR |= lookUp(y);
		else
			GPIOA->BSRR |= lookUp(y);

}

void setPinsLow(int y)
{
		if (y > 12)
			GPIOC->BSRR |= lookUp1(y);
		else
			GPIOA->BSRR |= lookUp1(y);
}

void delay(int count)
{
    for(int i = 0; i< count; ++i)
    {
    }
}

int lookUp(int y)
{
	if (y == 0)
		return B0;
	else if (y == 1)
		return B1;
	else if (y == 2)
		return B2;
	else if (y == 3)
		return B3;
	else if (y == 4)
		return B4;
	else if (y == 5)
		return B5;
	else if (y == 6)
		return B6;
	else if (y == 7)
		return B7;
	else if (y == 8)
		return B8;
	else if (y == 9)
		return B9;
	else if (y == 10)
		return B10;
	else if (y == 11)
		return B11;
	else if (y == 12)
		return B12;
	else if (y == 13)
		return B10;
	else if (y == 14)
		return B11;
	else if (y == 15)
		return B12;
	else return 0;
	
}

int lookUp1(int y)
{
	if (y == 0)
		return BR0;
	else if (y == 1)
		return BR1;
	else if (y == 2)
		return BR2;
	else if (y == 3)
		return BR3;
	else if (y == 4)
		return BR4;
	else if (y == 5)
		return BR5;
	else if (y == 6)
		return BR6;
	else if (y == 7)
		return BR7;
	else if (y == 8)
		return BR8;
	else if (y == 9)
		return BR9;
	else if (y == 10)
		return BR10;
	else if (y == 11)
		return BR11;
	else if (y == 12)
		return BR12;
	else if (y == 13)
		return BR10;
	else if (y == 14)
		return BR11;
	else if (y == 15)
		return BR12;
	else return 0;
}	
