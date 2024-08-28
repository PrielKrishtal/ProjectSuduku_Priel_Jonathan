#include "HeaderForEX1.h"

void checkAndRemoveVal(Array* arr, int* arrSize, int valToCheck)
{

}

void updatePossibilities(Array*** pos, int* row, int* col, int* value)
{
	for (int i = 0; i < SIZE; i++)
	{
		if (pos[*row][i] != NULL)
		{
			checkAndRemoveVal(pos[*row][i]->arr, pos[*row][i]->size, value);
		}

		if (pos[i][*col] != NULL)
		{
			checkAndRemoveVal(pos[i][*col]->arr, pos[i][*col]->size, value);
		}

		int CubeNum = CalWhichCube(*row, *col);
		int row_offset = ROW_OFFSET(CubeNum);
		int col_offset = COL_OFFSET(CubeNum);

		for (int m = 0; m < SIZE; m++) {
			for (int j = 0; j < SIZE; j++) {

				if(pos[row_offset + m][col_offset + j]!=NULL) // check cube values and remove
				{
					checkAndRemoveVal(pos[row_offset + m][col_offset + j]->arr, pos[row_offset + m][col_offset + j]->size, value);
				}
			}
		}
	}
}

//Helper function that frees the Array struct
void freePos(Array* array) 
{
	if (array != NULL) {
		free(array->arr);  // Free the dynamically allocated memory for the array
		array->arr = NULL; // Set the pointer to NULL to avoid dangling pointer
		array->size = 0;   // Reset size to 0
	}
}


int OneStage(short board[][9], Array*** possibilities, int* x, int* y)
{
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {

			if (board[i][j] != -1)
			{
				if (possibilities[i][j]->size == 1) //check if the current position only has a single option
				{
					board[i][j] = possibilities[i][j]; //update the suduko board with the singel value
					freePos(possibilities[i][j]);
					updatePossibilities(possibilities, x, y, board[i][j]); // call the helper funtion to update the possibel values matrix
				}
			}

		}
	}

}
