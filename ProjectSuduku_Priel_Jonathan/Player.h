#pragma once
#include "HeaderforEX1.h"

// Struct to represent a player
typedef struct Player {
    char* name; // we will track that max is 100 while scanf
    int board[SIZE][SIZE];  // Example board representation
    Array*** possibleDigits;  // Example possible digits

} Player;



//functions declerations

void freePlayer(Player* player);
Player* createPlayer(const char* name);
void addPlayerToArray(Player* player, Player* array[], int* count);