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
	//printf("**********************************************************************\n");
	printf("These are the options for cell (%d,%d): ", x, y);
	printArray(possibilities[x][y]->arr, possibilities[x][y]->size);
	printf("\n");
	printf("Enter one of the given options:");
	//scanf("%d", &input);

	// Generate a random index to select a legal value automatically
	int index = randomInt(0, possibilities[x][y]->size - 1);
 input = possibilities[x][y]->arr[index];  // Get the randomly selected option

	printf("Automatically selecting option %d for cell (%d,%d) for debugging.\n", input, x, y);

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
		//printf("FAILED");
		return FINISH_FAILURE;
	}

	if (x == -1 && y == -1 )//if board is fully filled
	{
		if(checkBoardValidity(board) == true)
		{
			//printf("FILLED\n");
			return finish_status;
		}

		//printf("FAILED");
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

			// If there's only one option, fill it immediately
			if (possibilities[x][y]->size == 1)
			{
				board[x][y] = possibilities[x][y]->arr[0]; //filling the cell with the only option
				updatePossibilities(possibilities, x, y, board[x][y], board); //update possible values for surrounding cells
				freePos(possibilities[x][y]);
				possibilities[x][y] = NULL;
			}
			else {
				
				fillCellWithInput(board, possibilities, x, y);  // call a helper function to deal with the input of the user
			}

			

			
			
			boardValidity = checkBoardValidity(board); // Re-assess the board status after each input or auto-fill
			if (!boardValidity){//if its not valid: we stop
				//printf("FAILED");
				return FINISH_FAILURE;
			}

			if (finish_status == FINISH_SUCCESS)
			{
				//printf("FILLED\n");
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