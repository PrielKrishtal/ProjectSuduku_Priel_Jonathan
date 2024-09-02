#include "HeaderForEX1.h"


bool CheckOptionValidity(int input, Array* cellOptions)
{
	// Iterate through the array elements
	for (int i = 0; i < cellOptions->size; i++) {
		if (cellOptions->arr[i] == input)  // Check if the current element matches the input
			return true; // Return true if a match is found
		
	}
	return false; // Return false if no match is found
}





void fillCellWithInput(short board[][9],Array*** possibilities, int x, int y)
{
	int input;
	printf("These are the options for cell (%d,%d): ", x, y);
	printArray(possibilities[x][y]->arr, possibilities[x][y]->size);
	printf("\n");
	printf("Enter one of the given options:");
	scanf("%d", &input);

	while (CheckOptionValidity(input, possibilities[x][y]) == false)
	{
		printf("Error: %d is not a valid option. Try again: ", input);
		printf("These are the options for cell (%d,%d): ",x, y);
		printArray(possibilities[x][y]->arr, possibilities[x][y]->size);
		printf("\n");
		printf("Enter one of the given options:");
		scanf("%d", &input);
	}



	
    //since the input is fine we: fill it in the board, update the surrounding's cell possibilities ,free this cell possibilities struct
	board[x][y] = input;
	updatePossibilities(possibilities, x, y, board[x][y], board);
	freePos(possibilities[x][y]);
	possibilities[x][y] = NULL;
}


int FillBoard(short board[][9], Array*** possibilities)
{
	int x = -1, y = -1;
	int status = OneStage(board, possibilities, &x,&y);

	if (x == -1 && y == -1 ) // X and Y's initialized values havent been changes thus there is no cell with more than 1 option 
	{
		printf("FILLED\n");
		return status;
	}


	else 
	{
		bool boardValidity;
		while (status == NOT_FINISH) // iterating while the board hasnt been fully filled
		{
			fillCellWithInput(board, possibilities, x, y); // call a helper function to deal with the input of the user
			boardValidity = checkBoardValidity(board); // call a helper function to check that the board is valid
			if (!boardValidity){//if its not valid: we stop
				printf("FILLED");
				return FINISH_FAILURE;
			}
			status = OneStage(board, possibilities, &x, &y);

		}
		if (status == FINISH_SUCCESS) 
			printf("FILLED\n");
		
		return status;
	}
	
}