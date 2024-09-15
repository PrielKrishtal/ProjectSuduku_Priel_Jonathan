#include "SudokuUtilities.h"
#include "PlayersLst.h"
#include "PlayersTree.h"

//function that checks the user's option validity
bool CheckOptionValidity(int input, Array* cellOptions)
{
	// Iterate through the array elements
	for (int i = 0; i < cellOptions->size; i++) {
		if (cellOptions->arr[i] == input)  // Check if the current element matches the input
			return true; // Return true if a match is found
		
	}
	return false; // Return false if no match is found
}


/**
  funtion that lets the user select a valid input for a specified Sudoku cell and updates the board and possibilities accordingly.
  the functin also Prints the updated board state after filling the cell.
 */
void fillCellWithInput(short board[][9],Array*** possibilities, int x, int y)
{
	int input;
	printf("These are several options for cell (%d,%d): ", x, y);
	printArray(possibilities[x][y]->arr, possibilities[x][y]->size);
	printf("\n");
	printf("Enter one of the given options:");
	//scanf("%d", &input);

	
	
	int index = randomInt(0, possibilities[x][y]->size - 1);
	input = possibilities[x][y]->arr[index]; 
	

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

	//printing for user's interface
	printf("\n");
	printf("This is how the board looks currently after filling cell (%d,%d) with the chosen value(%d):\n ", x, y, input); 
	printBoard(board);
	printf("\n");
}



/*
  FillBoard function continuously attempts to fill a Sudoku board using possibilities for each cell until the board is either fully solved, detected as unsolvable, or requires further input.
  it returns FINISH_SUCCESS if the board is fully solved, FINISH_FAILURE if unsolvable, and NOT_FINISH if not yet fully solved but still valid.
 */
int FillBoard(short board[][9], Array*** possibilities)
{
	int x = -1, y = -1; //setting those values aas indicators to see if there has been a change
	int finish_status = OneStage(board, possibilities, &x,&y);

	if (!checkBoardValidity(board))// if its initailly wrong
	{
		
		return FINISH_FAILURE;
	}

	if (x == -1 && y == -1 )//if board is fully filled
	{
		if(checkBoardValidity(board) == true)
		{
			
			return finish_status;
		}

		
		return FINISH_FAILURE;
		
	}


	else //if the board isn't fully filled(correctly)
	{

		bool boardValidity;
		while (finish_status == NOT_FINISH) // iterating while the board hasnt been fully filled
		{
			if (possibilities[x][y]->size == 0) //if a cell has 0 options its a failure
			{
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
				return FINISH_FAILURE;
			}

			if (finish_status == FINISH_SUCCESS)
			{
				return FINISH_SUCCESS;
			}
				

			finish_status = OneStage(board, possibilities, &x, &y);
			
		}
		
		
		return finish_status;
	}
	
}