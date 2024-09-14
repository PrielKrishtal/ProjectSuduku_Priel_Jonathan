#pragma once
#include "StandardIncludes.h"


// Struct to represent a position on the board
typedef struct CellNode {
    int row;                // Row position of the cell on the board
    int col;                // Column position of the cell on the board
    struct CellNode* next;  // Pointer to the next cell node in the list
} CellNode;


// struct which acts as a Linked list of CellNodes
typedef struct ListOfCells {
    CellNode* head;  // Head pointer to the start of the list
    CellNode* tail;  // Tail pointer to the end of the list
} ListOfCells;


// Function declarations for managing ListOfCells:
void makeEmptyListOfCells(ListOfCells * lst);
CellNode* createNewCellNode(int row, int col);
void appendToCellsList(ListOfCells * lst, int row, int col);
void freeListOfCells(ListOfCells * lst);
void printListOfCells(ListOfCells * lst);




