#include "HeaderForEX1.h"
#include "PlayersLst.h"
#include "PlayersTree.h"

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
	printf("******************************************************************************************************************************************************\n");
	printf("These are the options for cell (%d,%d): ", x, y);
	printArray(possibilities[x][y]->arr, possibilities[x][y]->size);
	printf("\n");
	printf("Enter one of the given options:");
	scanf("%d", &input);

	while (!CheckOptionValidity(input, possibilities[x][y]))
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
	int finish_status = OneStage(board, possibilities, &x,&y);

	if (!checkBoardValidity(board))// if its initailly wrong
	{
		printf("FAILED");
		return FINISH_FAILURE;
	}

	if (x == -1 && y == -1 )//if board is fully filled
	{
		if(checkBoardValidity(board) == true)
		{
			printf("FILLED\n");
			return finish_status;
		}

		printf("FAILED");
		return FINISH_FAILURE;
		
	}


	else //if the board isnt fully filled(correctly)
	{

		bool boardValidity;
		while (finish_status == NOT_FINISH) // iterating while the board hasnt been fully filled
		{
			if (possibilities[x][y]->size == 0) //if a cell has 0 options its a failure
			{
				printf("FAILED: cell[%d][%d] had 0 options!",x,y);
				return FINISH_FAILURE;
			}
			
			fillCellWithInput(board, possibilities, x, y); // call a helper function to deal with the input of the user
			boardValidity = checkBoardValidity(board); // call a helper function to check that the board is valid
			if (!boardValidity){//if its not valid: we stop
				printf("FAILED");
				return FINISH_FAILURE;
			}

			if (finish_status == FINISH_SUCCESS)
			{
				printf("FILLED\n");
				return FINISH_SUCCESS;
			}
				

			finish_status = OneStage(board, possibilities, &x, &y);
			printf("\n");
			printBoard(board); // Assumes printBoard function is defined to print the board state
			printf("\n");
		}
		
		
		return finish_status;
	}
	
}