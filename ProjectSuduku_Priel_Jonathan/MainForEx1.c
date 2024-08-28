/*
#include "HeaderForEX1.h"

// Function to calculate possible digits for each cell
Array*** PossibleDigits(short sudokuBoard[][SIZE])
{
    Array*** allPossibleVal = (Array***)malloc(SIZE * SIZE * sizeof(Array**));
    CHECK_ALLOCATION(allPossibleVal);

    for (int i = 0; i < SIZE; i++)
    {
        allPossibleVal[i] = (Array**)malloc(SIZE * sizeof(Array*));
        CHECK_ALLOCATION(allPossibleVal[i]);
    }

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (sudokuBoard[i][j] == -1)
            {
                bool numPresent[9] = { false };
                short* tempRow = checkRowVal(sudokuBoard, i);
                short* tempCol = checkColVal(sudokuBoard, j);
                short* tempCube = checkCubeVal(sudokuBoard, i, j);

                markNumbers(numPresent, tempRow, SIZE);
                markNumbers(numPresent, tempCol, SIZE);
                markNumbers(numPresent, tempCube, SIZE);

                short* missingNumbers;
                int missingCount;
                findMissingNumbers(numPresent, &missingNumbers, &missingCount);

                allPossibleVal[i][j] = (Array*)malloc(sizeof(Array));
                CHECK_ALLOCATION(allPossibleVal[i][j]);
                allPossibleVal[i][j]->arr = missingNumbers;
                allPossibleVal[i][j]->size = missingCount;

                free(tempRow);
                free(tempCol);
                free(tempCube);
            }
            else
            {
                allPossibleVal[i][j] = NULL;
            }
        }
    }

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
short* checkRowVal(short sudokuBoard[][SIZE], int row)
{
    short* tempArr = (short*)malloc(sizeof(short) * SIZE);
    CHECK_ALLOCATION(tempArr);
    for (int i = 0; i < SIZE; i++)
        tempArr[i] = sudokuBoard[row][i];
    return tempArr;
}

// Function to get column values
short* checkColVal(short sudokuBoard[][SIZE], int col)
{
    short* tempArr = (short*)malloc(sizeof(short) * SIZE);
    CHECK_ALLOCATION(tempArr);
    for (int i = 0; i < SIZE; i++)
        tempArr[i] = sudokuBoard[i][col];
    return tempArr;
}

// Function to get values in a specific 3x3 cube
short* checkCubeVal(short sudokuBoard[][SIZE], int row, int col)
{
    short* tempCubeArr = (short*)malloc(sizeof(short) * 9);
    CHECK_ALLOCATION(tempCubeArr);
    int CubeNum = CalWhichCube(row, col);
    int row_offset = (CubeNum / 3) * 3;
    int col_offset = (CubeNum % 3) * 3;

    int CubeIndex = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            tempCubeArr[CubeIndex++] = sudokuBoard[row_offset + i][col_offset + j];
        }
    }
    return tempCubeArr;
}

*/



/// true version