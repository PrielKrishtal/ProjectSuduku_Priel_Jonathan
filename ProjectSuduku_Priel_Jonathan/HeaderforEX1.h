#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

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


typedef struct _Array
{
    short* arr;
    unsigned short size;
} Array;


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
    Array*** possibleDigits;  // Example possible digits
    struct Player* next;  // Pointer for linked list
} Player;












/*
  Functions declerations:
**********************/

Array*** PossibleDigits(short sudokuBoard[][9]);//QUESTION 1

void markNumbers(bool* numPresent, short arr[], int size);
void findMissingNumbers(bool* numPresent, short** missingNumbers, int* missingCount);
void checkRowVal(short sudokuBoard[][SIZE], int row, short* tempArr);
void checkColVal(short sudokuBoard[][SIZE], int col, short* tempArr);
void checkCubeVal(short sudokuBoard[][SIZE], int row, int col, short* tempArr);
void checkAndRemoveVal(Array* arr, int valToCheck);
void freePos(Array* array);
bool checkBoardValidity(short board[][9]);
void updatePossibilities(Array*** pos, int* row, int* col, int value, short board[][9]);


int OneStage(short board[][9], Array*** possibilities, int* x, int* y);//QUESTION 2


int FillBoard(short board[][9], Array*** possibilities); //QUESTION 3







bool CheckOptionValidity(int input, Array* cellOptions);
void fillCellWithInput(short board[][9], Array*** possibilities, int x, int y);
int FillBoard(short board[][9], Array*** possibilities);



// Function prototypes
Node* createLocationList();
int randomInt(int min, int max);
Node* deleteNode(Node* head, int index);
Node* selectRandomLocation(Node* head, int size, int* row, int* col);
int randomLegalValue(int possibleValues[], int count);
Player* createPlayer(const char* name);
void addPlayerToArray(Player* player, Player* array[], int* count);

void freeList(Node* head);
//void freePlayerList(PlayerNode* head);

void freePlayers(Player* head);
