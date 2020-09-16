#include "stm32f10x.h"

void SPI_init(void)
{
	SPI1->CR1 |= SPI_CR1_BIDIMODE | SPI_CR1_BIDIOE | SPI_CR1_SSM | (0x3UL<<SPI_CR1_BR_0) | SPI_CR1_MSTR;
	SPI1->CR1 |= SPI_CR1_SPE;
	
	
	
}
