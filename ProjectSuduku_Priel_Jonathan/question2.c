#include "SudokuUtilities.h"

// Function to remove a specific value from an array of possible values in a Sudoku cell
void checkAndRemoveVal(Array* arr, int valToCheck)
{
	// Check if the array is empty or not initialized
	if (arr->size <= 0 ) {
		freePos(arr);// Safely deallocate the array
		arr = NULL;  // Set the pointer to NULL to avoid issues
		return;
	}

	//Loop through the array to find the value to remove
	for (int i = 0; i < arr->size; i++) {
		if (arr->arr[i] == valToCheck) {  //Found the value to remove

			//Shift elements left to overwrite the value to be removed
			for (int j = i; j < arr->size - 1; j++) {
				arr->arr[j] = arr->arr[j + 1];
			}
			arr->size--; //Decrement the size as one element is removed
			break; //Exit the loop as the value has been removed
		}
	}

}


// Function to update possible values for Sudoku cells after placing a number on the board
void updatePossibilities(Array*** pos, int row, int col, int value, short board[][9])
{
	// Iterate over all cells in the same row and column
	for (int i = 0; i < SIZE; i++)
	{
		// Remove the placed value from the possibilities of cells in the same row 
		if (pos[row][i] != NULL)
		{
			checkAndRemoveVal(pos[row][i], value);
		}

		// Remove the placed value from the possibilities of cells in the same column
		if (pos[i][col] != NULL)
		{
			checkAndRemoveVal(pos[i][col], value);
		}
	}
	
	
	int CubeNum = CalWhichCube(row, col); // Calculate the 3x3 subgrid number based on the row and column

	// Calculate the starting row and column for the subgrid
	int row_offset = ROW_OFFSET(CubeNum);
	int col_offset = COL_OFFSET(CubeNum);

	// Iterate over the 3x3 subgrid cells
	for (int m = 0; m < 3; m++) {
		for (int j = 0; j < 3; j++) {

			int currentRow = row_offset + m;
			int currentCol = col_offset + j;


			// Ensure the current cell is within the grid bounds
			if (currentRow < SIZE && currentCol < SIZE) {
				if (pos[currentRow][currentCol] != NULL) {
					// Remove the placed value from the possibilities of the subgrid cells
					checkAndRemoveVal(pos[currentRow][currentCol], value);
				}
			}

			else {
				printf("ERROR: Attempted out of bounds access at [%d][%d]\n", currentRow, currentCol);
			}
		}
		
	}


}

//Helper function that frees the Array struct
void freePos(Array* array) 
{
	if (array) {
		free(array->arr); // Safely free the array
		array->arr = NULL;
		array->size = 0;
	}
}

//function that insures board validity
bool checkBoardValidity(short board[][9])
{
	bool used[SIZE+1]; // Array to track numbers 1-9 (index 0 is unused)

	// Check each row for duplicates
	for (int i = 0; i < SIZE; i++) {
		memset(used, 0, sizeof(used)); // Reset the tracking array for each new row
		for (int j = 0; j < SIZE; j++) {
			if (board[i][j] != -1) { // Check if the cell is filled
				if (used[board[i][j]]) {
					return false; // Return false if the number has already been used in the row
				}
				used[board[i][j]] = true; // Mark the number as used in this row
			}
		}
	}

	// Check each column for duplicates
	for (int j = 0; j < SIZE; j++) {
		memset(used, 0, sizeof(used)); // Reset the tracking array for each new column
		for (int i = 0; i < SIZE; i++) {
			if (board[i][j] != -1) { // Check if the cell is filled
				if (used[board[i][j]]) {
					return false; // Return false if the number has already been used in the column
				}
				used[board[i][j]] = true; // Mark the number as used in this column
			}
		}
	}

	// Check each 3x3 subgrid for duplicates
	for (int block = 0; block < SIZE; block++) {
		memset(used, 0, sizeof(used)); // Reset the tracking array for each new block
		int startRow = (block / 3) * 3; // Calculate the starting row index for the current block
		int startCol = (block % 3) * 3; // Calculate the starting column index for the current block

		for (int i = startRow; i < startRow + 3; i++) {
			for (int j = startCol; j < startCol + 3; j++) {
				if (board[i][j] != -1) { // Check if the cell is filled
					if (used[board[i][j]]) {
						return false; // Return false if the number has already been used in this 3x3 subgrid
					}
					used[board[i][j]] = true; // Mark the number as used in this 3x3 subgrid
				}
			}
		}
	}

	return true; // Return true if no duplicates are found, indicating the board is valid
}



/**
   OneStage function Attempts to fill a Sudoku board by checking each cell for a single possible digit and updates the board accordingly.
  Returns FINISH_SUCCESS if board is filled correctly, FINISH_FAILURE if the board is invalid, or NOT_FINISH if more moves are needed.
 */
int OneStage(short board[][9], Array*** possibilities, int* x, int* y)
{
	int boardStatus = FINISH_SUCCESS;
	int minPosSize = SIZE+1;//initializing as max value of size
	
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {

			if (board[i][j] == -1 && possibilities[i][j] != NULL)
			{
				if (possibilities[i][j]->size == 1) //check if the current position only has a single option
				{
					board[i][j] = possibilities[i][j]->arr[0];//update the suduko board with the singel value
					updatePossibilities(possibilities, i, j, board[i][j],board); // call the helper funtion to update the possibel values matrix
					freePos(possibilities[i][j]);
					possibilities[i][j] = NULL;

				}

				else // has more than 1 option in possibilities
				{
					boardStatus = NOT_FINISH; //updating board satatus to not finished
					if (possibilities[i][j]->size < minPosSize)//else: if cell has more than 1 possiblity
					{
						// #Note: incase of sevral minimal size values we take the first appearing
						minPosSize = possibilities[i][j]->size;
						*x = i; //updating the X coordinate pointer
						*y = j; //updating the Y coordinate pointer
					}
				}
			}

		}
	}

	// Check board validity and determine if the board is solved or failed
	if (boardStatus != FINISH_FAILURE)
	{
		if (!checkBoardValidity(board))
			boardStatus = FINISH_FAILURE;
	}
	

	switch (boardStatus)
	{
	case NOT_FINISH:
		
		return boardStatus;
		
	case FINISH_SUCCESS:
		
		return boardStatus;

	case FINISH_FAILURE:
		
		return boardStatus;
	}


}


