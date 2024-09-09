#include "BoardCells.h"

// Initialize the list of cells to be empty
void makeEmptyListOfCells(ListOfCells* lst) {
    lst->head = lst->tail = NULL;
}

// Create a new CellNode
CellNode* createNewCellNode(int row, int col) {
    CellNode* node = (CellNode*)malloc(sizeof(CellNode));
    if (!node) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->row = row;
    node->col = col;
    node->next = NULL;
    return node;
}

// Append a new cell node to the end of the list
void appendToCellsList(ListOfCells* lst, int row, int col) {
    CellNode* newNode = createNewCellNode(row, col);
    if (lst->tail == NULL) { // If the list is empty
        lst->head = lst->tail = newNode; // New node is both head and tail
    }
    else {
        lst->tail->next = newNode; // Append new node at the end
        lst->tail = newNode; // Update tail to the new node
    }
}

// Free the entire list
void freeListOfCells(ListOfCells* lst) {
    CellNode* current = lst->head;
    while (current != NULL) {
        CellNode* next = current->next;
        free(current);
        current = next;
    }
    lst->head = lst->tail = NULL;
}

// Print all cells in the list
void printListOfCells(ListOfCells* lst) {
    CellNode* current = lst->head;
    printf("Cells in the list:\n");
    while (current != NULL) {
        printf("(%d, %d) -> ", current->row, current->col);
        current = current->next;
    }
    printf("NULL\n");
}
