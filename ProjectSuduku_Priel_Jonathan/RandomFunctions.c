#include "functionsForMain.h"


// Function to fill a board with random values using ListOfCells
void createRandomBoard(short board[SIZE][SIZE])
{

    ListOfCells locationList;
    makeEmptyListOfCells(&locationList); // Initialize the list with head and tail set to NULL

    // Populate the list with all possible locations starting from [0,0] until [8,8]
    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            appendToCellsList(&locationList, r, c); //(just like insertDataToEndOfLst)
        }
    }

    int listSize = SIZE * SIZE; // Start with the maximum number of cells
    int cellsToFill = randomInt(1, 20);// Determine the number of cells to randomly fill (between 1 and 20)

    for (int i = 0; i < cellsToFill; i++)
    {
        int row, col;

        // Select a random location from the list to be deleted
        selectRandomLocation(&locationList, &listSize, &row, &col);


        int possibleValues[SIZE] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };  // Possible Sudoku Cell values


        board[row][col] = randomLegalValue(possibleValues, SIZE); // Assign a random valid value to the selected board cell
        //printf("value generated randomly for cell [%d][%d] is: %d\n", row, col, board[row][col]);

        //Print the board state after each assignment
        //printf("Current state of the board after updating [%d][%d]:\n", row, col);
        //printBoard(board);

    }

    //printf("List of randoms:\n");
    //printCellsList(&locationList, board);

    // Clean up the remaining nodes in the list
    freeListOfCells(&locationList);


}


// Function to generate a random number between min and max
 int randomInt(int min, int max) {
    return rand() % (max - min + 1) + min;
}


// Function to delete a node from the linked list based on row and column values
void deleteNode(ListOfCells* lst, int row, int col)
{
    if (lst->head == NULL) return;  // No node to delete if the list is empty

    CellNode* temp;

    // Special handling if the node to delete is the head of the list
    if (lst->head->row == row && lst->head->col == col) {
        temp = lst->head;
        lst->head = lst->head->next;  // Move the head pointer to the next node
        if (lst->head == NULL) {
            lst->tail = NULL;  // If the list becomes empty, tail must also be NULL
        }
    }
    else {
        // Traverse the list to find the node to delete
        CellNode* current = lst->head;
        while (current->next != NULL &&
            (current->next->row != row || current->next->col != col)) {
            current = current->next;  // Move to the next node
        }

        if (current->next == NULL) return;  // Node not found, nothing to delete

        temp = current->next;
        current->next = temp->next;  // Unlink the node from the list
        if (temp->next == NULL) {
            lst->tail = current;  // Update tail if the last node is deleted
        }
    }

    free(temp);  // Free the node that has been removed
}


// Function to check if a node with specific row and column exists in the list
bool nodeExists(ListOfCells* lst, int row, int col)
{
    CellNode* current = lst->head;  // Start from the head of the list
    while (current != NULL) {
        if (current->row == row && current->col == col) {
            return true;  // Node with matching row and column found
        }
        current = current->next;  // Move to the next node
    }
    return false;  // No matching node found
}


// Function to select a random position on the board by generating two random numbers
void selectRandomLocation(ListOfCells* lst, int* size, int* row, int* col)
{
    if (lst->head == NULL) {
        printf("Failed to select a random location. List is empty.\n");
        return;  // No positions to select from
    }

    // Generate random numbers for row and col separately
    do {
        *row = randomInt(0, SIZE - 1);  // Random row between 0 and SIZE-1
        *col = randomInt(0, SIZE - 1);  // Random col between 0 and SIZE-1
    } while (!nodeExists(lst, *row, *col));//Repeat until a valid node is found(Invalid case would be generating an index [row][col] of a node we have previously deleted before)

    CellNode* current = lst->head;

    // Traverse the list to find the matching node
    while (current != NULL) {
        if (current->row == *row && current->col == *col) { // Check if current node matches the random row and col generated
            deleteNode(lst, current->row, current->col);   // If a match is found, delete the node from the list
            (*size)--; // Decrement size after successfully deleting a node
            return; // Exit after finding and deleting the node
        }
        current = current->next; // Move to the next node in the list
    }

    // If we reach here, it means something went wrong
    printf("Failed to select a random location. No matching node found for (%d, %d).\n", *row, *col);
}


// Function to generate a valid random value for a cell
int randomLegalValue(int possibleValues[], int count) {
    int index = randomInt(0, count - 1);// Generate a random index between 0 and count-1
    return possibleValues[index];// Return the value located at the randomly generated index
}

