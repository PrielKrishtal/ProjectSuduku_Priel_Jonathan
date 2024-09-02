#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>


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

/// Macro for checking allocations
#define CHECK_ALLOCATION(ptr) \
    do { \
        if ((ptr) == NULL) { \
            fprintf(stderr, "Memory allocation failed\n"); \
            exit(EXIT_FAILURE); \
        } \
    } while (0)


// Struct to represent a position on the board
typedef struct Node {
    int row;
    int col;
    struct Node* next;
} Node;

// Struct to represent a player
typedef struct Player {
    char name[MAX_NAME_LENGTH];
    int board[SIZE][SIZE];  // Example board representation
    int possibleDigits[SIZE];  // Example possible digits
    struct Player* next;  // Pointer for linked list
} Player;

// Struct to represent a player node in a linked list
typedef struct PlayerNode {
    Player* player;
    struct PlayerNode* next;
} PlayerNode;

// Struct to represent a player node in a binary search tree
typedef struct PlayerTreeNode {
    Player* player;
    struct PlayerTreeNode* left;
    struct PlayerTreeNode* right;
} PlayerTreeNode;



typedef struct _Array
{
    short* arr;
    unsigned short size;
} Array;




/*
  Functions declerations:
**********************/

Array*** PossibleDigits(short sudokuBoard[][9]);

void markNumbers(bool* numPresent, short arr[], int size);
void findMissingNumbers(bool* numPresent, short** missingNumbers, int* missingCount);
void checkRowVal(short sudokuBoard[][SIZE], int row, short* tempArr);
void checkColVal(short sudokuBoard[][SIZE], int col, short* tempArr);
void checkCubeVal(short sudokuBoard[][SIZE], int row, int col, short* tempArr);
void checkAndRemoveVal(Array* arr, int valToCheck);
void freePos(Array* array);
bool checkBoardValidity(short board[][9]);
void updatePossibilities(Array*** pos, int* row, int* col, int value, short board[][9]);
int OneStage(short board[][9], Array*** possibilities, int* x, int* y);
int FillBoard(short board[][9], Array*** possibilities);
