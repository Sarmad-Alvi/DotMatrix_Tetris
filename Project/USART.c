#include "stm32f10x.h"
#include "multiplex.h"
#include "led_init.h"

void UART3_TX_ROW(int x [][8])
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			while(((USART3->SR & USART_SR_TXE)>>7) != 1)
			{	}
			if (x[i][j] == 0)
				USART3->DR = x[i][j];
			else
				USART3->DR = 1;
		}
	}
	
	
}

void USART3_init(void)
{
    USART3->CR1 |= USART_CR1_UE;
	  USART3->BRR = 0x9C4;
		USART3->CR1 |= USART_CR1_TE;
}

