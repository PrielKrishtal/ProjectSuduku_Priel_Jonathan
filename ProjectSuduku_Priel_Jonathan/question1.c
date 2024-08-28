#include "Array.h"


Array*** PossibleDigits(short sudokuBoard[][SIZE])
{
	Array*** allPossibelVal = (Array***)malloc(SIZE * sizeof(Array**));

	for (int i = 0; i < SIZE; i++)
	{
		allPossibelVal[i] = (Array**)malloc(SIZE * sizeof(Array*));
		for (int j = 0; j < SIZE; j++)
		{
			allPossibelVal[i][j] = (Array*)malloc(sizeof(Array));

			allPossibelVal[i][j]->size = 0; //Initialize size to 0

			
			allPossibelVal[i][j]->arr = (Array*)malloc(10 * sizeof(Array));
		}
	}

		

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (sudokuBoard[i, j] != -1)
			{

			}
		}
	}
} 


short* checkRowVal(int row)
{
	
}


short* checkColVal(int col)
{

}


short* allExistingVal(int row, int col)
{

}


