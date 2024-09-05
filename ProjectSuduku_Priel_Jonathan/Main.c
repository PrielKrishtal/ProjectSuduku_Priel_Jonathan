#include "HeaderForEX1.h"
    

// main for testing
/*
void main() {
    short sudokuBoard[9][9] = {
        { 5,-1, 4,-1, 7,-1,-1, 1,-1},
        { 6,-1, 2, 1,-1,-1, 3,-1,-1},
        { 1,-1, 8,-1, 4,-1,-1, 6,-1},
        {-1, 5,-1,-1, 6,-1,-1, 2,-1},
        {-1, 2,-1, 8,-1, 3,-1,-1,-1},
        {-1,-1,-1,-1,-1, 4,-1, 5, 6},
        {-1, 6, 1, 5, 3, 7, 2, 8, 4},
        {-1, 8, 7,-1, 1, 9,-1, 3,-1},
        {-1,-1,-1, 2, 8,-1,-1,-1, 9 }
    };

    printf("Initial Sudoku Board:\n");
    printBoard(sudokuBoard); // Assumes printBoard function is defined to print the board state
    printf("\n");

    Array*** possibleDigits = PossibleDigits(sudokuBoard); // Initialize possible digits array

    // Display initial possibilities for debugging or user information
    printf("Initial possible digits for each cell:\n");
    printPossibleDigits(possibleDigits);
    printf("\n");

    // Call FillBoard to process the entire board with user inputs and solving logic
    int finalStatus = FillBoard(sudokuBoard, possibleDigits);
    printf("Final Board Status: %s\n", finalStatus == FINISH_SUCCESS ? "Solved" : "Not Solved");

    // Free memory for possibleDigits
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (possibleDigits[i][j] != NULL) {
                free(possibleDigits[i][j]->arr); // Free the array inside the structure
                free(possibleDigits[i][j]); // Free the structure itself
            }
        }
        free(possibleDigits[i]); // Free the row of pointers
    }
    free(possibleDigits); // Free the top-level pointer



}
*/


void main()

{

    short board[9][9] =

    { 5,-1, 4,-1, 7,-1,-1, 1,-1,

     6,-1, 2, 1,-1,-1, 3,-1,-1,

     1,-1, 8,-1, 4,-1,-1, 6,-1,

    -1, 5,-1,-1, 6,-1,-1, 2,-1,

    -1, 2,-1, 8,-1, 3,-1,-1,-1,

    -1,-1,-1,-1,-1, 4,-1, 5, 6,

    -1, 6, 1, 5, 3, 7, 2, 8, 4,

    -1, 8, 7,-1, 1, 9,-1, 3,-1,

    -1,-1,-1, 2, 8,-1,-1,-1, 9 };



    Array*** possible_solutions;



    printf("Initial board\n");

    sudokoPrintBoard(board);



    printf("Press enter to start playing...\n");

    getchar();

    possible_solutions = PossibleDigits(board);



    if (FillBoard(board, possible_solutions) == -1)

        printf("User's selections led to duplications\n");

    else

    {

        sudokoPrintBoard(board);

        printf("Board filled successfully\n");

    }



    // Don't forget to free memory!

}






