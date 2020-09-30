#include "stm32f10x.h"


void refreshMatrix(uint8_t dataPin, uint8_t clockPin, uint8_t latchPin, uint8_t OE_n, uint8_t m[][8]);

extern uint8_t mBuffFore_G[16][8];
extern uint8_t mBuffBack_G[16][8];

