#pragma once
#include "standard_includes.h"

#define SIZE 9
#define MAX_NAME_LENGTH 100
///Macro for getting cube number  (1+ to match the cube numbers)
#define CalWhichCube(row, col) (3 * (row / 3) + (col / 3) ) 

#define ROW_OFFSET(cubeNum) ((CubeNum / 3) * 3)
#define COL_OFFSET(cubeNum) ((CubeNum % 3) * 3)

//Board status indices:
#define NOT_FINISH 0
#define FINISH_SUCCESS 1
#define FINISH_FAILURE -1

#define FILE_NAME "winnersList.txt"

/// Macro for checking allocations
#define CHECK_ALLOCATION(ptr) \
    do { \
        if ((ptr) == NULL) { \
            fprintf(stderr, "Memory allocation failed\n"); \
            exit(EXIT_FAILURE); \
        } \
    } while (0)


typedef struct _Array
{
    short* arr;
    unsigned short size;
} Array;



/*
  Functions declerations(includes declerations for Question 1,2,3):
*************************************************************************************************/
Array*** PossibleDigits(short sudokuBoard[][SIZE]);
void printBoard(short sudokuBoard[][SIZE]);
void markNumbers(bool* numPresent, short arr[], int size);
void findMissingNumbers(bool* numPresent, short** missingNumbers, int* missingCount);
void checkRowVal(short sudokuBoard[][SIZE], int row, short* tempArr);
void checkColVal(short sudokuBoard[][SIZE], int col, short* tempArr);
void checkCubeVal(short sudokuBoard[][SIZE], int row, int col, short* tempArr);
void checkAndRemoveVal(Array* arr, int valToCheck);
void freePos(Array* array);
bool checkBoardValidity(short board[][9]);
void updatePossibilities(Array*** pos, int row, int col, int value, short board[][9]);
void printArray(short* arr, int size);
int OneStage(short board[][9], Array*** possibilities, int* x, int* y);
int FillBoard(short board[][9], Array*** possibilities); 
bool CheckOptionValidity(int input, Array* cellOptions);
void fillCellWithInput(short board[][9], Array*** possibilities, int x, int y);
int FillBoard(short board[][9], Array*** possibilities);
void freePos(Array* array);



