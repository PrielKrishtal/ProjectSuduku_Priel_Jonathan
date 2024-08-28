#include "HeaderForEX1.h"

// Function to print the Sudoku board
void printBoard(short sudokuBoard[][SIZE])
{
    printf("Sudoku Board:\n");
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            printf("%2d ", sudokuBoard[i][j]);
        }
        printf("\n");
    }
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
        printf("%d ", arr[i]);
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

    // Create a single temporary array to store row, column, or cube values
    short* temp = (short*)malloc(sizeof(short) * SIZE);
    CHECK_ALLOCATION(temp);

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (sudokuBoard[i][j] == -1)
            {
                bool numPresent[9] = { false };

                // Get row values and update numPresent
                checkRowVal(sudokuBoard, i, temp);
                printf("Checking cell (%d, %d)\n", i, j);
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
    int row_offset = (CubeNum / 3) * 3;
    int col_offset = (CubeNum % 3) * 3;

    int CubeIndex = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            tempArr[CubeIndex++] = sudokuBoard[row_offset + i][col_offset + j];
        }
    }
}


// Example usage
void main()
{
    short sudokuBoard[9][9] =

    { 5,-1, 4,-1, 7,-1,-1, 1,-1,

     6,-1, 2, 1,-1,-1, 3,-1,-1,

     1,-1, 8,-1, 4,-1,-1, 6,-1,

    -1, 5,-1,-1, 6,-1,-1, 2,-1,

    -1, 2,-1, 8,-1, 3,-1,-1,-1,

    -1,-1,-1,-1,-1, 4,-1, 5, 6,

    -1, 6, 1, 5, 3, 7, 2, 8, 4,

    -1, 8, 7,-1, 1, 9,-1, 3,-1,

    -1,-1,-1, 2, 8,-1,-1,-1, 9 };


    printBoard(sudokuBoard);
    Array*** possibleDigits = PossibleDigits(sudokuBoard);
    printPossibleDigits(possibleDigits);

    // Free memory for possibleDigits here...


}
