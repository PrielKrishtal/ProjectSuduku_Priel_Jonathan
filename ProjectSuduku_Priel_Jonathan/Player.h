#pragma once
#include "HeaderforEX1.h"
#include "standard_includes.h"

// Struct to represent a player
typedef struct Player {
    char* name; // we will track that max is 100 while scanf
    short board[SIZE][SIZE];  // Example board representation
    Array*** possibleDigits;  // Example possible digits

} Player;



//functions declerations
void initializeBoard(short board[SIZE][SIZE]);
void freePlayer(Player* player);
void addPlayerToArray(Player* player, Player* array[], int* count);