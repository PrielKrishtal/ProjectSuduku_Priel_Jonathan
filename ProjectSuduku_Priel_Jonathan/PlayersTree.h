#pragma once
#include "HeaderforEX1.h"


// Struct to represent a player node in a binary search tree
typedef struct PlayerTreeNode {
    Player* player;
    struct PlayerTreeNode* left;
    struct PlayerTreeNode* right;
} PlayerTreeNode;



typedef struct PlayersTree {
    PlayerTreeNode* root;
}PlayersTree;



//Functions declerations:

PlayerTreeNode* insertPlayerTree(PlayerTreeNode* root, Player* player);
void freePlayerTree(PlayerTreeNode* root);