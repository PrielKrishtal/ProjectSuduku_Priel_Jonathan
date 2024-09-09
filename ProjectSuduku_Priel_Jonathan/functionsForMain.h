#pragma once
#include "HeaderforEX1.h"
#include "PlayersLst.h"
#include "PlayersTree.h"
#include "functionsForMain.h"
#include "Player.h"


//functions declerations: 
Player* createPlayer(const char* name);
void bubbleSort(Player** players, int count);
void getNumActivePlayers(int* x);
void createRandomBoard(int board[SIZE][SIZE]);
void create_And_Fill_ActivePlayersList(PlayersList* lst, int numPlayers);
Player** createAndSortPlayerArray(PlayersList* list, int size);
int calculateNewSize(int currentSize);
Player** resizeArray(Player** players, int* currentSize);
Node* createLocationList();
int randomInt(int min, int max);
Node* deleteNode(Node* head, int index);
Node* selectRandomLocation(Node* head, int size, int* row, int* col);
int randomLegalValue(int possibleValues[], int count);
PlayerTreeNode* insertPlayerTree(PlayerTreeNode* root, Player* player);
void freePlayerTree(PlayerTreeNode* root);
void inOrderTraversal(PlayerTreeNode* root, void (*func)(Player*));
PlayerTreeNode* buildTreeFromArray(Player* array[], int start, int end);
void inOrderProcess(PlayerTreeNode* root, PlayersList* activePlayers, PlayersList* winnerPlayers);
void printBoardToFile(FILE* file, int board[SIZE][SIZE]);
void printWinnersToFile(PlayerNode* winnerList);
void printSudoku(int board[SIZE][SIZE]);
void freePlayerArray(Player** array, int size);
char* readInput();


