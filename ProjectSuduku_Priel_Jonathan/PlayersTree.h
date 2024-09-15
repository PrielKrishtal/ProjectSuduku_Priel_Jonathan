#pragma once
#include "StandardIncludes.h"
#include "SudokuUtilities.h"


typedef struct PlayerTreeNode {
    PlayerNode** playerNodePtr;  // Pointer to a cell in the sorted array
    struct PlayerTreeNode* left;
    struct PlayerTreeNode* right;
} PlayerTreeNode;



typedef struct PlayersTree {
    PlayerTreeNode* root;
}PlayersTree;



//Functions declerations:

PlayerTreeNode* insertPlayerTree(PlayerTreeNode* root, PlayerNode** playerNodePtr);
void freePlayerTree(PlayerTreeNode* root);
PlayerTreeNode* buildTreeFromArray(PlayerNode** array, int start, int end);