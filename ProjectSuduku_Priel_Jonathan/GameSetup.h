#pragma once
#include "StandardIncludes.h"
#include "SudokuUtilities.h"
#include "PlayersLst.h"
#include "PlayersTree.h"
#include "Player.h"
#include "BoardCells.h"


#define CALCULATE_NEW_SIZE(currentSize)  (int)pow(2, ceil(log2(currentSize + 1))) - 1;



//functions declerations: 
Player* createPlayer();
void getNumActivePlayers(int* x);
void create_And_Fill_ActivePlayersList(PlayersList* lst, int numPlayers);
PlayerNode** createAndSortPlayerArray(PlayersList* list, int size);
void bubbleSort(PlayerNode** playerNodes, int count);
PlayerNode** resizeArray(PlayerNode** playerNodes, int* currentSize);
int calculateNewSize(int currentSize);
PlayerNode** resizeArray(PlayerNode** playerNodes, int* currentSize);
void printBoardToFile(FILE* file, int board[SIZE][SIZE]);
void printWinnersToFile(PlayerNode* winnerList);
void printSudoku(int board[SIZE][SIZE]);
void freePlayerArray(Player** array, int size);
void inOrderProcess(PlayerTreeNode* root, PlayersList* activePlayers, PlayersList* winnerPlayers);
void freePlayerNodeArray(PlayerNode** playerPointersArray, int size);
// Function to count the number of players in a linked list
int countPlayersInList(PlayersList* winnerList);


/*
    Declerations of the functions that produce the random cell's indices and their randomly generated values:
    (implementation for these function in "RandomFunctions.c"
    **********************************************************************************************************************/
void createRandomBoard(int board[SIZE][SIZE]);
int randomInt(int min, int max);
int randomLegalValue(int possibleValues[], int count);
void selectRandomLocation(ListOfCells* lst, int* row, int* col);
void deleteNode(ListOfCells* lst, int row, int col);