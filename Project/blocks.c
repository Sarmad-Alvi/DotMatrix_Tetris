#include "multiplex.h"
#include "stm32f10x.h"
#include "shapes.h"
#include "led_init.h"



//copy array 1 into array 2 for 8x8 array
void copy(uint8_t x[][8], uint8_t z[][8])
{
	for (int i = 0; i < 16; i++)
		for (int j = 0; j < 8; j++)
			{
				z[i][j] = x[i][j];
			}
}

//puts elements of array x into array y
void combine(uint8_t x[][8], uint8_t z[][8])
{
	for (int i = 0; i < 16; i++)
		for (int j = 0; j < 8; j++)
			{
				if (x[i][j] == 1)
					z[i][j] = x[i][j];
			}
}

//same as copy but for 3x3 array
void copy1(uint8_t x[][3], uint8_t z[][3])
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			{
				z[i][j] = x[i][j];
			}
}

//clears 8x8 array
void clear(uint8_t x[][8])
{
	for (int i = 0; i < 16; i++)
		for (int j = 0; j < 8; j++)
			{
				x[i][j] = 0;
			}	
}

//moves elements in 8x8 array left by 1
void left(uint8_t x [][8], uint8_t y[][8], uint8_t start[2])
{
	_Bool check = 1;
	for (int i = 0; i < 16; i++)
		if (x[i][0] == 1)
			check = 0;

	for (int i = 0; i < 16; i++)
		for (int j = 0; j < 8; j++)
		{
			if(x[i][j] == 1 && y[i][j-1] == 1)
				check = 0;
		}
			
	if (check == 1)
	{
		uint8_t z [16][8];
		copy(x, z);
		clear(x);
		for (int i = 0; i < 16; i++)
			for (int j = 0; j < 8; j++)
				{
					if (z[i][j] == 1)
					{	
						x[i][j-1] = 1;
					}
				}
		start[1]--;
	}
}


//moves elements in 8x8 array right by 1
void right(uint8_t x [][8], uint8_t y[][8], uint8_t start[2])
{
	_Bool check = 1;
	for (int i = 0; i < 16; i++)
		if (x[i][7] == 1)
			check = 0;
		
	for (int i = 0; i < 16; i++)
		for (int j = 0; j < 8; j++)
		{
			if(x[i][j] == 1 && y[i][j+1] == 1)
				check = 0;
			
		}
	if (check == 1)
	{
		uint8_t z [16][8];
		copy(x, z);
		clear(x);
		for (int i = 0; i < 16; i++)
			for (int j = 0; j < 8; j++)
				{
					if (z[i][j] == 1)
					{	
						x[i][j+1] = 1;
					}
				}
		start[1]++;
	}
}


//moves shape in 8x8 array down by 1
void down(uint8_t x [][8], uint8_t y[][8], uint8_t start[2])
{
	_Bool check = 1;
	for (int i = 0; i < 16; i++)
		for (int j = 0; j < 8; j++)
			{
				if ((x[i][j] == 1) && ((y[i+1][j]) == 1 || (x[15][j] == 1)))
				{
					check = 0;
				}
			}
		
	if (check == 1)
	{
		uint8_t z [16][8];
		copy(x, z);
		clear(x);
		for (int i = 0; i < 16; i++)
			for (int j = 0; j < 8; j++)
				{
					if (z[i][j] == 1)
					{	
						x[i+1][j] = 1;
					}
				}
		start[0]++;
	}
	
}

void shiftDown(uint8_t y[][8])
{
	uint8_t z [16][8];
	copy(y, z);
	clear(y);
	for (int i = 0; i < 16; i++)
		for (int j = 0; j < 8; j++)
			{
				if (z[i][j] >= 1)
				{	
					y[i+1][j] = 1;
				}
			}
	
}

//rotates shape currently in foreground by using premade shape templates, and starting coordinates of current shape, 
void rotate(uint8_t x [][8], uint8_t curr, uint8_t start[2], uint8_t currShape)
{
	uint8_t s [3][3];
		
	if (start[1] == 6)
	{
		start[1]--;
	}
	else if (start[0] == 14)
	{
		start[0]--;
	}
	
	if (curr == 1)
	{
		copy1(SH[currShape].s2, s);
	}
	else if (curr == 2)
	{
		copy1(SH[currShape].s3, s);
	}
	else if (curr == 3)
	{
		copy1(SH[currShape].s4, s);
	}
	else if (curr == 4)
	{
		copy1(SH[currShape].s1, s);
	}
	clear(x);
	for (int i = start[0], k = 0; i < (start[0]+3); i++, k++)
		for (int j = start[1], l = 0; j < (start[1]+3); j++, l++)
			{
				x[i][j] = s[k][l];
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


_Bool ReF(uint8_t x [][8], uint8_t y[][8], uint8_t currShape, uint8_t defaultStart[2], uint8_t start[2])
{
	_Bool check = 0;
	for (int i = 0; i < 16; i++)
		for (int j = 0; j < 8; j++)
			{
				if (((x[i][j] == 1) && (y[i+1][j] == 1)) || (x[15][j] == 1))
				{
					combine(x,y);
					clear(x);
					for (int c = 0; c < 8; c++)
					{
						if (y[0][5] == 1)
						{
							clear(y);
							return 0;
						}
						else
						{
							
							return 1;
						}
					}
					goto end;
					
				}
				else if ((x[i][j] == 1) && (y[i+1][j] == 0))
				{
					check = 1;
				}
			}
	if (check == 1)
	{
		down(x,y, start);
		return 0;
	}
	end:;
}

void clearRow(uint8_t row, uint8_t y[][8])
{
	for ( int c = 0; c < 8; c++)
	{
		y[row][c] = 0;
	}
}


void shift_Rows(uint8_t row, uint8_t y[][8])
{
	uint8_t temp[16][8];
	clear(temp);
	copy(y,temp);
		
	for ( int i = row; i < 16; i++)
	{
		clearRow(i, temp);
	}
	for( int i = row; i >= 0; i--)
	{
		clearRow(i, y);
	}
	shiftDown(temp);
	delay(200);
	combine(temp, y);
	
}


void checkRow(uint8_t x[][8], uint8_t y[][8])
{
	int sum = 0;
	uint8_t row;
	for (int i = 0; i < 16; i++)
	{
		sum = 0;
		for (int j = 0; j < 8; j++)
		{
			if (y[i][j] == 1)
				sum++;
		}
		row = i;
		if (sum == 8)
		{
			clearRow(row, x);
			shift_Rows(row,y);
		}
	}
	
}












