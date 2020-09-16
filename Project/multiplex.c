#include "stm32f10x.h"
#include "multiplex.h"
#include "led_init.h"


int mBuff[8][8] = {
	
	{1, 0, 1, 1, 0, 0, 0, 1},
	{0, 0, 0, 0, 0, 0, 1, 0},
	{0, 0, 1, 1, 0, 1, 0, 0},
	{0, 0, 1, 0, 1, 0, 0, 0},
	{0, 0, 0, 1, 0, 0, 0, 0},
	{0, 0, 1, 0, 0, 0, 0, 0},
	{0, 1, 0, 0, 0, 0, 0, 0},
	{1, 0, 0, 0, 0, 0, 0, 0}
};

int mBuffB[8][8] = {
	
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
	for (int i = 0; i < 8; i++)
		setPinsLow(dataPin);
	
	delay(200);
	setPinsHigh(clockPin);
	delay(200);
	setPinsLow(clockPin);
	delay(200);
	setPinsHigh(latchPin);
}

void setRowPinsS(uint8_t dataPin, uint8_t clockPin, uint8_t latchPin, int c, int m[][8])
{
	for (int r = 7; r >=0; r--)
	{
		if (m[r][c] == 1)
		{
			setPinsHigh(dataPin);
		}
		else
		{
			setPinsLow(dataPin);
		}
		delay(200);
		setPinsHigh(clockPin);
		delay(200);
		setPinsLow(clockPin);
	}
	return;
}

void refreshMatrix(uint8_t dataPin, uint8_t clockPin, uint8_t latchPin, uint8_t OE_n, int m[][8])
{
	for (int c = 0; c < 8; c++)
	{
		setPinsHigh(OE_n);
		setPinsLow(latchPin);
		setRowPinsS(dataPin, clockPin, latchPin, c, m);
		
		int x = 0xFF;
		x = (x & ~(1 << (c)));
		if (c == 0)
		{
			setPinsLow(12);
		}
		else
		{
			setPinsHigh(12);
		}
		delay(20);
		for (int i = 0; i < 8; i++)
		{
			if ((x & (1 << (7 - i))))
				setPinsHigh(dataPin);
			else
				setPinsLow(dataPin);
			//delay(2);
			//delay(2);
			setPinsHigh(clockPin); 
			//delay(2);
			setPinsLow(clockPin); 
		}
                                                                                                                                                                                                                                                                                                                                                                                             		
		
		//delay(2);
		setPinsHigh(latchPin);
		//delay(200);
		setPinsLow(OE_n);
		delay(2000);
	}
}
