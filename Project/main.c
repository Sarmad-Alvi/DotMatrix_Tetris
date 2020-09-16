#include "stm32f10x.h"
#include "clock.h"
#include "led_init.h"
#include "multiplex.h"
#include "blocks.h"
#include "event_handler.h"

void refreshMatrixTimer(uint32_t delay);
void refreshMatrixS(uint8_t dataPin, uint8_t clockPin, uint8_t latchPin);
void setRowPinsS(uint8_t dataPin, uint8_t clockPin, uint8_t latchPin, int c, int m[][8]);
void refreshMatrixSS(uint8_t dataPin, uint8_t clockPin, uint8_t latchPin, uint8_t OE, int m[][8]);
void init(uint8_t dataPin, uint8_t clockPin, uint8_t latchPin);

int main(void)
{
	clockInit();
	pin_init();
	init(2, 3, 4);

	
	while (1)
	{
		refreshMatrixSS(9, 8, 10, 11,mBuff);
		delay(200);
		//refreshMatrixSS(9, 8, 10, 11, mBuffB);
		
	}

}

void EXTI15_10_IRQHandler(void)
{
	if (EXTI->PR & EXTI_PR_PR12)
	{
		delay(5000);
		EXTI->PR |= EXTI_PR_PR12;
		delay(5000);
		left(mBuff);
		delay(5000);
	}
}

