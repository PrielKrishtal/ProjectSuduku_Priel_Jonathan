#include "HeaderForEX1.h"


// main for testing

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
    printf("\n");

    Array*** possibleDigits = PossibleDigits(sudokuBoard); // Initialize possible digits array
    printf("\n");
    printf("Initial possible digits for each cell:\n");
    printPossibleDigits(possibleDigits); // Print initial possibilities

    int x = 0, y = 0; // Variables to hold coordinates of the last modified cell

    // Call OneStage to process one solving step and print debug information

    printf("\n");
    printf("Question 2: Processing one stage...\n");
    printf(" __________________________\n");

    int status = OneStage(sudokuBoard, possibleDigits, &x, &y);//prints status and gives numeric info of status
    printf("\n");

    // Output results from the OneStage function
    printf("After OneStage, status: %d \n\n", status);
    printf("Cell with minimal posibilites is: [%d, %d]\n", x, y);
    printf(" ___________________________________________\n");
    printf("Updated Sudoku Board:\n");
    printBoard(sudokuBoard);

    printf("***********************************************************************************************\n\n\n");
    printf("CHEKING VALUES AFTER QUESTION 2:\n");
    // Optionally, print the updated possible digits
    printf("Updated possible digits for each cell after OneStage:\n");
    possibleDigits = PossibleDigits(sudokuBoard); // Initialize possible digits array
    printf("\n");
    printf("Initial possible digits for each cell:\n");
    printPossibleDigits(possibleDigits); // Print initial possibilities


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