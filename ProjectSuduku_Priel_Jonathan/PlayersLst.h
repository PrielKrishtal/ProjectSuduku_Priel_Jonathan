#pragma once
#include "standard_includes.h"
#include "Player.h"

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
void removePlayerFromList(PlayersList* lst, Player* player);
void freePlayersList(PlayersList* lst);
