#include "stm32f10x.h"


void left(uint8_t x [][8], uint8_t y[][8], uint8_t start[2]);
void right(uint8_t x [][8], uint8_t y[][8], uint8_t start[2]);
void down(uint8_t x [][8], uint8_t y[][8], uint8_t start[2]);
void rotate(uint8_t x [][8], uint8_t curr, uint8_t start[2], uint8_t currShape);
void insertS(uint8_t currShape, uint8_t defaultStart[2], uint8_t mBuffFore_G [][8]);
_Bool ReF(uint8_t x [][8], uint8_t y[][8], int randNum, uint8_t defaultStart[2], uint8_t start[2]);
void checkRow(uint8_t x[][8], uint8_t y[][8]);


void clear(uint8_t x[][8]);
