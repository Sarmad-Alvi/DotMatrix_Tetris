#include "stm32f10x.h"


void refreshMatrix(uint8_t dataPin, uint8_t clockPin, uint8_t latchPin, uint8_t OE_n, int m[][8]);

extern int mBuff[][8];
extern int mBuffB[][8];

