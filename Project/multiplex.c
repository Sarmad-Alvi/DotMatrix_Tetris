#include "stm32f10x.h"
#include "multiplex.h"
#include "led_init.h"


uint8_t mBuffFore_G[16][8] = {
	
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0}
};

uint8_t mBuffBack_G[16][8] = {
	
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0}
};

void init(uint8_t dataPin, uint8_t clockPin, uint8_t latchPin)
{
	setPinsLow(latchPin);
	for (int i = 0; i < 24; i++)
		setPinsLow(dataPin);
	
	delay(200);
	setPinsHigh(clockPin);
	delay(200);
	setPinsLow(clockPin);
	delay(200);
	setPinsHigh(latchPin);
}

void setColumnPinsS(uint8_t dataPin, uint8_t clockPin, uint8_t latchPin, int r, uint8_t m[][8])
{
	for (int c = 0; c < 8 ; c++)
	{
		if (m[r][c] == 1)
		{
			setPinsHigh(dataPin);
		}
		else
		{
			setPinsLow(dataPin);
		}
		delay(20);
		setPinsHigh(clockPin);
		delay(20);
		setPinsLow(clockPin);
	}
	return;
}

void refreshMatrix(uint8_t dataPin, uint8_t clockPin, uint8_t latchPin, uint8_t OE_n, uint8_t m[][8])
{
	for (int r = 0; r < 16; r++)
	{
		setPinsHigh(OE_n);
		delay(20);
		setPinsLow(latchPin);
		setColumnPinsS(dataPin, clockPin, latchPin, r, m);
		
		int x = 0xFFFF;
		x = (x & ~(1 << (r)));
		

		delay(20);
		for (int i = 0; i < 16; i++)
		{
			if ((x & (1 << (15 - i))))
			{
				setPinsHigh(dataPin);
			}
			else
			{
				setPinsLow(dataPin);
			}
			
			setPinsHigh(clockPin); 
			delay(20);
			setPinsLow(clockPin); 
		}
                                                                                                                                                                                                                                                                                                                                                                                             		
		

		setPinsHigh(latchPin);
		delay(20);
		setPinsLow(OE_n);
		delay(1000);
	}
}


