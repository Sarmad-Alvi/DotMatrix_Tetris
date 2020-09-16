#include "multiplex.h"
#include "stm32f10x.h"

void copy(int x[][8], int z[][8])
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			{
				z[i][j] = x[i][j];
			}
}

void clear(int x[][8])
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			{
				x[i][j] = 0;
			}	
}

void left(int x [][8])
{
	_Bool check = 1;
	for (int i = 0; i < 8; i++)
		if (x[i][0] == 1)
			check = 0;
		
	if (check == 1)
	{
		int z [8][8];
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
	}
}

void right(int x [][8])
{
	_Bool check = 1;
	for (int i = 0; i < 8; i++)
		if (x[i][7] == 1)
			check = 0;
		
	if (check == 1)
	{
		int z [8][8];
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
	}
}