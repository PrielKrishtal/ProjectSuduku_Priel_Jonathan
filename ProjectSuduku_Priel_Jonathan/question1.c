#include "HeaderForEX1.h"

// Function to print the Sudoku board
// Function to print the Sudoku board with visual separators for 3x3 grids
void printBoard(short sudokuBoard[][SIZE]) {
    printf("  | ");
    for (int col = 0; col < SIZE; col++) {
        printf("%d ", col);  // Print the column headers
        if ((col + 1) % 3 == 0 && col < SIZE - 1) {
            printf("| ");  // Print vertical separators for columns
        }
    }
    printf("\n");

    // Print a separator line before the board starts
    printf("-------------------------\n");

    for (int i = 0; i < SIZE; i++) {
        printf("%d |", i);  // Print the row number followed by a vertical line
        for (int j = 0; j < SIZE; j++) {
            if (sudokuBoard[i][j] == -1) {  // Check if the cell is empty
                printf("%2d", sudokuBoard[i][j]);  // Print -1 for empty cells
            }
            else {
                printf("%2d", sudokuBoard[i][j]);  // Print the value with correct spacing
            }
            if ((j + 1) % 3 == 0 && j < SIZE - 1) {
                printf(" |");  // Print vertical separators within the row
            }
        }
        printf(" \n");
        if ((i + 1) % 3 == 0 && i < SIZE - 1) {
            printf("-------------------------\n");  // Print horizontal separators after every 3 rows
        }
    }

    // Print a separator line at the bottom of the board
    printf("-------------------------\n");
}


// Function to print the possible digits
void printPossibleDigits(Array*** allPossibleVal)
{
    printf("Possible Digits for Each Cell:\n");
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (allPossibleVal[i][j] != NULL)
            {
                printf("Cell (%d, %d): ", i, j);
                for (int k = 0; k < allPossibleVal[i][j]->size; k++)
                {
                    printf("%d ", allPossibleVal[i][j]->arr[k]);
                }
                printf("\n");
            }
            else
            {
                printf("Cell (%d, %d): NULL\n", i, j);
            }
        }
    }
}

// Function to print an array of short values
void printArray(short* arr, int size)
{
    printf("[ ");
    for (int i = 0; i < size; i++)
    {
        printf("%d  ", arr[i]);
    }
    printf("]\n");
}


// Function to calculate possible digits for each cell
Array*** PossibleDigits(short sudokuBoard[][SIZE])
{
    Array*** allPossibleVal = (Array***)malloc(SIZE * sizeof(Array**));
    CHECK_ALLOCATION(allPossibleVal);

    for (int i = 0; i < SIZE; i++)
    {
        allPossibleVal[i] = (Array**)malloc(SIZE * sizeof(Array*));
        CHECK_ALLOCATION(allPossibleVal[i]);
    }

    // Create a single temporary array to store for compartion: row, column, or cube values
    short* temp = (short*)malloc(sizeof(short) * SIZE);
    CHECK_ALLOCATION(temp);

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            printf("\n");
            if (sudokuBoard[i][j] == -1)
            {
                bool numPresent[9] = { false }; //initalize a boolean array in order to mark values that arent available

                // Get row values and update numPresent
                checkRowVal(sudokuBoard, i, temp);
                //****************************** NEEDS TO BE REMOVED ***************************
                printf("Checking cell (%d, %d):\n", i, j);
                printf("__________________________\n");
                printf("Row values: ");
                printArray(temp, SIZE);
                markNumbers(numPresent, temp, SIZE);

                // Get column values and update numPresent
                checkColVal(sudokuBoard, j, temp);
                printf("Column values: ");
                printArray(temp, SIZE);
                markNumbers(numPresent, temp, SIZE);


                // Get cube values and update numPresent
                checkCubeVal(sudokuBoard, i, j, temp);
                printf("Cube values: ");
                printArray(temp, SIZE);
                markNumbers(numPresent, temp, 9);
 

                // Find missing numbers and store them
                short* missingNumbers;
                int missingCount;
                findMissingNumbers(numPresent, &missingNumbers, &missingCount);

                printf("Possible digits for cell (%d, %d): ", i, j);
                printArray(missingNumbers, missingCount);
                

                allPossibleVal[i][j] = (Array*)malloc(sizeof(Array));
                CHECK_ALLOCATION(allPossibleVal[i][j]);
                allPossibleVal[i][j]->arr = missingNumbers;
                allPossibleVal[i][j]->size = missingCount;
            }
            else
            {
                allPossibleVal[i][j] = NULL;
            }
        }
    }

    // Free the temporary array after the loop
    free(temp);

    return allPossibleVal;
}



// Function to mark numbers from the array
void markNumbers(bool* numPresent, short arr[], int size)
{
    for (int i = 0; i < size; i++) {
        if (arr[i] >= 1 && arr[i] <= 9) {
            numPresent[arr[i] - 1] = true;
        }
    }
}

// Function to get missing numbers
void findMissingNumbers(bool* numPresent, short** missingNumbers, int* missingCount)
{
    *missingCount = 0;
    // First pass to count missing numbers
    for (int i = 0; i < 9; i++)
    {
        if (!numPresent[i])
        {
            (*missingCount)++;
        }
    }

    // Allocate memory for missing numbers array
    *missingNumbers = (short*)malloc(*missingCount * sizeof(short));
    CHECK_ALLOCATION(*missingNumbers);

    // Second pass to fill missing numbers
    int index = 0;
    for (int i = 0; i < 9; i++)
    {
        if (!numPresent[i]) {
            (*missingNumbers)[index++] = i + 1;
        }
    }
}

// Function to get row values
void checkRowVal(short sudokuBoard[][SIZE], int row, short* tempArr)
{
    for (int i = 0; i < SIZE; i++)
        tempArr[i] = sudokuBoard[row][i];
}

// Function to get column values into temp array
void checkColVal(short sudokuBoard[][SIZE], int col, short* tempArr)
{
    for (int i = 0; i < SIZE; i++)
        tempArr[i] = sudokuBoard[i][col];
}

// Function to get values in a specific 3x3 cube into temp array
void checkCubeVal(short sudokuBoard[][SIZE], int row, int col, short* tempArr)
{
    int CubeNum = CalWhichCube(row, col);
    int row_offset = ROW_OFFSET(CubeNum);
    int col_offset = COL_OFFSET(CubeNum);

    int CubeIndex = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            tempArr[CubeIndex++] = sudokuBoard[row_offset + i][col_offset + j];
        }
    }
}


