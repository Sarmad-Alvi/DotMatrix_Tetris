#include "multiplex.h"
#include "stm32f10x.h"
#include "shapes.h"



void copy(uint8_t x[][8], uint8_t z[][8])
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			{
				z[i][j] = x[i][j];
			}
}

void copy1(uint8_t x[][3], uint8_t z[][3])
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			{
				z[i][j] = x[i][j];
			}
}

void clear(uint8_t x[][8])
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			{
				x[i][j] = 0;
			}	
}

void left(uint8_t x [][8], int new)
{
	_Bool check = 1;
	for (int i = 0; i < 8; i++)
		if (x[i][0] == 1)
			check = 0;
		
	if (check == 1)
	{
		uint8_t z [8][8];
		copy(x, z);
		clear(x);
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
				{
					if (z[i][j] == 1)
					{	
						x[i][j-1] = 1;
					}
				}
		new = 1;
	}
}

void right(uint8_t x [][8], int new)
{
	_Bool check = 1;
	for (int i = 0; i < 8; i++)
		if (x[i][7] == 1)
			check = 0;
		
	if (check == 1)
	{
		uint8_t z [8][8];
		copy(x, z);
		clear(x);
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
				{
					if (z[i][j] == 1)
					{	
						x[i][j+1] = 1;
					}
				}
		new = 1;
	}
}

void up(uint8_t x [][8])
{
	_Bool check = 1;
	for (int i = 0; i < 8; i++)
		if (x[1][i] == 1)
			check = 0;
		
	if (check == 1)
	{
		uint8_t z [8][8];
		copy(x, z);
		clear(x);
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
				{
					if (z[i][j] == 1)
					{	
						x[i-1][j] = 1;
					}
				}
	}
	
}

void down(uint8_t x [][8])
{
	_Bool check = 1;
	for (int i = 0; i < 8; i++)
		if (x[7][i] == 1)
			check = 0;
		
	if (check == 1)
	{
		uint8_t z [8][8];
		copy(x, z);
		clear(x);
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
				{
					if (z[i][j] == 1)
					{	
						x[i+1][j] = 1;
					}
				}
	}
	
}

void rotate(uint8_t x [][8], uint8_t curr, uint8_t start[2], uint8_t newPos, uint8_t currShape)
{
	if (curr == 1 || newPos == 1 )
	{
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
				{
					if ( x[i][j] == 1)
					{
						start[0] = i;
						start[1] = j;
						goto break1;
					}
				}
	}
	break1:;
	int pWidth, pHeight;
	
	if (1)
	{
		uint8_t s [3][3];
		
		if (curr == 1)
		{
			copy1(SH[currShape].s2, s);
			for (int i = 0; i < 8; i++)
				{
					if (x[7][i] == 1)
					{
						start[0]--;
					}
				}
		}
		else if (curr == 2)
		{
			copy1(SH[currShape].s3, s);
			for (int i = 0; i < 8; i++)
				{
					if (x[i][7] == 1)
					{
						start[1]--;
					}
				}
		}
		else if (curr == 3)
		{
			copy1(SH[currShape].s4, s);
			for (int i = 0; i < 8; i++)
				{
					if (x[7][i] == 1)
					{
						start[0]--;
					}
				}
		}
		else if (curr == 4)
		{
			copy1(SH[currShape].s1, s);
			for (int i = 0; i < 8; i++)
				{
					if (x[i][7] == 1)
					{
						start[1]--;
					}
				}
		}
		clear(x);
		for (int i = start[0], k = 0; i < (start[0]+3); i++, k++)
			for (int j = start[1], l = 0; j < (start[1]+3); j++, l++)
				{
					x[i][j] = s[k][l];
				}
	}
}

void insertS(uint8_t currShape, uint8_t defaultStart[2], uint8_t mBuffFore_G [][8])
{
	for (int i = defaultStart[0], k = 0; i < (defaultStart[0]+3); i++, k++)
		for (int j = defaultStart[1], l = 0; j < (defaultStart[1]+3); j++, l++)
			{
				mBuffFore_G[i][j] = SH[currShape].s1[k][l];
			}
	
	
}



