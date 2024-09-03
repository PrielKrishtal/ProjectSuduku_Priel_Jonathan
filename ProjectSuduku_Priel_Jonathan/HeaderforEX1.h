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

// Struct to represent a player node in a linked list
typedef struct PlayerNode {
    Player* player;
    struct PlayerNode* next;
} PlayerNode;

//struct to represnt a players linked list
typedef struct PlayersList
{
    PlayerNode* head;
    PlayerNode* tail;
}PlayersList;




// Struct to represent a player node in a binary search tree
typedef struct PlayerTreeNode {
    Player* player;
    struct PlayerTreeNode* left;
    struct PlayerTreeNode* right;
} PlayerTreeNode;








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



/*prototype for Linked list of Players: 
*/

void makeEmptyPlayersList(PlayersList* lst);
bool isEmptyPlayersList(PlayersList* lst);
PlayerNode* getPlayerNode(PlayersList* lst, int index);
PlayerNode* createNewPlayerNode(Player* player, PlayerNode* next);
void insertPlayerToStartList(PlayersList* lst, Player* player);
void insertPlayerNodeToStartList(PlayersList* lst, PlayerNode* node);
void insertPlayerToEndList(PlayersList* lst, Player* player);
void insertPlayerNodeToEndList(PlayersList* lst, PlayerNode* node);
bool insertPlayerToPlaceInList(PlayersList* lst, Player* player, int index);
bool insertPlayerNodeToPlaceInList(PlayersList* lst, PlayerNode* node, int index);









// Function prototypes
Node* createLocationList();
int randomInt(int min, int max);
Node* deleteNode(Node* head, int index);
Node* selectRandomLocation(Node* head, int size, int* row, int* col);
int randomLegalValue(int possibleValues[], int count);
Player* createPlayer(const char* name);
void addPlayerToArray(Player* player, Player* array[], int* count);
PlayerTreeNode* insertPlayerTree(PlayerTreeNode* root, Player* player);
void freeList(Node* head);
void freePlayerList(PlayerNode* head);
void freePlayerTree(PlayerTreeNode* root);
void freePlayers(Player* head);
