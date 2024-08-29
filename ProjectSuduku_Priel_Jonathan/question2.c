#include "HeaderForEX1.h"

// Function to remove a specific value from an array of possible values in a Sudoku cell
void checkAndRemoveVal(Array* arr, int valToCheck) 
{
	int indexToRemove = -1; 

	
	for (int i = 0; i < arr->size; i++) {
		if (arr->arr[i] == valToCheck) { // Check if the current element is the value to remove
			indexToRemove = i; // Store the index of the value to be removed
			break; // Exit the loop as the value is found
		}
	}

	// If a value was found and its index is identified
	if (indexToRemove != -1) {
		// Shift elements to the left to fill the gap created by the removed element
		for (int i = indexToRemove; i < arr->size - 1; i++) {
			arr->arr[i] = arr->arr[i + 1]; // Copy the next element to the current position
		}
		arr->size--; // Decrease the size of the array by 1 since an element has been removed
	}
}


// Function to update possible values for Sudoku cells after placing a number on the board
void updatePossibilities(Array*** pos, int* row, int* col, int* value)
{
	for (int i = 0; i < SIZE; i++)
	{
		if (pos[*row][i] != NULL)
		{
			// Remove the placed value from the possibilities of the cell 
			checkAndRemoveVal(pos[*row][i]->arr, pos[*row][i]->size, value);
		}

		if (pos[i][*col] != NULL)
		{
			// Remove the placed value from the possibilities of the cell 
			checkAndRemoveVal(pos[i][*col]->arr, pos[i][*col]->size, value);
		}

		 // Calculate the starting indices of the 3x3 cube that contains the cell
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
	int boardStatus = FINISH_SUCCESS;
	int minPosSize = SIZE+1;//initializing as max value of size
	int tempX = 0, tempY = 0; //temp variables to hold coordinates
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {

			if (board[i][j] != -1)
			{
				if (possibilities[i][j]->size == 1) //check if the current position only has a single option
				{
					board[i][j] = possibilities[i][j]->arr[0]; // Corrected to assign the single possible value; //update the suduko board with the singel value
					freePos(possibilities[i][j]);
					updatePossibilities(possibilities, x, y, board[i][j]); // call the helper funtion to update the possibel values matrix
				}

				else
				{
					boardStatus = NOT_FINISH; //updating board satatus to not finished
					if (possibilities[i][j]->size < minPosSize)//else: if cell has more than 1 possiblity
					{
						// #Note: incase of sevral minimal size values we take the first appearing
						minPosSize = possibilities[i][j]->size;
						tempX = i;
						tempY = j;
					}
				}
			}

		}
	}
	*x = tempX; //updating the X coordinate pointer
	*y = tempY; //updating the Y coordinate pointer

	switch (boardStatus) {
	case NOT_FINISH:
		printf("NOT_FINISH");
		return NOT_FINISH;
		
	case FINISH_SUCCESS:
		printf("FINISH_SUCCESS");
		return FINISH_SUCCESS;

	case FINISH_FAILURE:
		break; //todo
	}

}
