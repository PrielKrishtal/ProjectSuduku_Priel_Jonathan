#pragma once
#include "standard_includes.h"
#include "HeaderforEX1.h"
#include "PlayersLst.h"
#include "PlayersTree.h"
#include "functionsForMain.h"
#include "Player.h"
#include "BoardCells.h"


#define CALCULATE_NEW_SIZE(currentSize)  (int)pow(2, ceil(log2(currentSize + 1))) - 1;



//functions declerations: 
Player* createPlayer();
void bubbleSort(Player** players, int count);
void getNumActivePlayers(int* x);
void create_And_Fill_ActivePlayersList(PlayersList* lst, int numPlayers);
Player** createAndSortPlayerArray(PlayersList* list, int size);
int calculateNewSize(int currentSize);
Player** resizeArray(Player** players, int* currentSize);
PlayerTreeNode* insertPlayerTree(PlayerTreeNode* root, Player* player);
void freePlayerTree(PlayerTreeNode* root);
void inOrderTraversal(PlayerTreeNode* root, void (*func)(Player*));
PlayerTreeNode* buildTreeFromArray(Player* array[], int start, int end);
void inOrderProcess(PlayerTreeNode* root, PlayersList* activePlayers, PlayersList* winnerPlayers);
void printBoardToFile(FILE* file, int board[SIZE][SIZE]);
void printWinnersToFile(PlayerNode* winnerList);
void printSudoku(int board[SIZE][SIZE]);
void freePlayerArray(Player** array, int size);




/*
    Declerations of the functions that produce the random cell's indices and their randomly generated values:
    (implementation for these function in "RandomFunctions.c"
    **********************************************************************************************************************/
void createRandomBoard(int board[SIZE][SIZE]);
int randomInt(int min, int max);
int randomLegalValue(int possibleValues[], int count);
void selectRandomLocation(ListOfCells* lst, int* row, int* col);
void deleteNode(ListOfCells* lst, int row, int col);