﻿#include "functionsForMain.h"


void initializeBoard(short board[SIZE][SIZE]) 
{
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = -1;
        }
    }
}


// Function to create a player
Player* createPlayer()
{
    char buffer[MAX_NAME_LENGTH]; //insure the name is 100 char len max
    printf("Enter player's name: ");
    scanf("%s", buffer);

    Player* newPlayer = (Player*)malloc(sizeof(Player));

    newPlayer->name = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
    CHECK_ALLOCATION(newPlayer->name);

    strncpy(newPlayer->name, buffer, strlen(buffer) + 1); // +1 to include the null terminator

    initializeBoard(newPlayer->board);
    createRandomBoard(newPlayer->board); // Fill the player's board with random values
    /*
    printf("Player's board:\n\n");
    printBoard(newPlayer->board);
    printf("\n");
    printf("\n**********************\n");*/
    newPlayer->possibleDigits = PossibleDigits(newPlayer->board); // Initialize the possible digits array for the board



    return newPlayer;
}


void getNumActivePlayers(int* x)
{
    int input;
    printf("Pls enter number of active players:");
    scanf("%d", &input);
    //todo: add validity number check on input

    *x = input;
}

// Function to print all integers in the linked list of cells
void printCellsList(ListOfCells* lst, int board[SIZE][SIZE]) 
{
    if (lst == NULL) {
        printf("The list is empty.\n");
        return;
    }

    CellNode* current = lst->head; // Start with the head of the list
    while (current != NULL) { // Traverse until the end of the list
        printf("Cell[%d][%d]: %d\n", current->row, current->col, board[current->row][current->col]); // Print the data of the current node
        current = current->next; // Move to the next node
    }
    printf("\n"); // Print a newline at the end for better formatting
}


//Funcion that creates a PlayersList and Fills it in using given info from the user
void create_And_Fill_ActivePlayersList(PlayersList* lst, int numPlayers)
{
    makeEmptyPlayersList(lst); // Initialize the list to be empty
    Player* newPlayer;

    for (int i = 0; i < numPlayers; i++) {
        
         newPlayer = createPlayer(); // Create a new player with the given name

        insertPlayerToEndList(lst, newPlayer); // Insert the player at the end of the list as a PlayerNode

      
    }
   
}

// Function to count filled cells in a Sudoku board
int CountFilledCells(short(*board)[SIZE])
{
    int unfilledCount = 0; // Counter for unfilled cells

    // Loop over each cell in the board
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            // Check if the current cell is unfilled (-1)
            if (board[row][col] == -1) {
                unfilledCount++; // Increment unfilled count
            }
        }
    }

    // Return the number of filled cells
    return (SIZE * SIZE) - unfilledCount;
}



// Function to create and sort an array of player pointers from a linked list of players
Player** createAndSortPlayerArray(PlayersList* list,int size) 
{
    // Allocate an array of player pointers of the right size
    Player** playerPointerArray = (Player**)malloc(size * sizeof(Player*));
    CHECK_ALLOCATION(playerPointerArray);  // Use the macro to check allocation and handle any failure

    // Fill the array with pointers to the players
    PlayerNode* current = list->head;  // set current pointer to the head of the list
    for (int index = 0; index < size && current != NULL; index++) {
        playerPointerArray[index] = current->player;  // Assign the player pointer to the array
        current = current->next;  // Move to the next node
    }

    // Now sort the array using the modified bubble sort function
    bubbleSort(playerPointerArray, size);  // Sort the array based on the sorting criteria defined in bubbleSort



    return playerPointerArray;  // Return the sorted array of player pointers
}


// Function that sorts an array of Player pointers based on filled cells and names
void bubbleSort(Player** players, int count) 
{
    // Outer loop: iterate through each player in the array except the last one
    for (int i = 0; i < count - 1; i++) {
        // Inner loop: go through the players up to the part of the array that's still unsorted
        for (int j = 0; j < count - i - 1; j++) {

            int filledCellsCurrent = CountFilledCells(players[j]->board);
            int filledCellsNext = CountFilledCells(players[j + 1]->board);

            // Check if the current player should swap places with the next one based on filled cells
            if (filledCellsCurrent < filledCellsNext) {
                // Swap the current player with the next one
                Player* temp = players[j];
                players[j] = players[j + 1];
                players[j + 1] = temp;
            }
            // If the filled cell count is the same, then compare names
            else if (filledCellsCurrent == filledCellsNext && strcmp(players[j]->name, players[j + 1]->name) > 0) {
                // Swap the current player with the next one based on name comparison
                Player* temp = players[j];
                players[j] = players[j + 1];
                players[j + 1] = temp;
            }
        }
    }
}




// Helper function to resize the array of pointers
Player** resizeArray(Player** players, int* currentSize)
{
    int newSize = CALCULATE_NEW_SIZE(*currentSize); // Calculate new size using the formula defined as a  macro

    // Reallocate the existing array to the new size
    Player** newPlayers = (Player**)realloc(players, newSize * sizeof(Player*));
    CHECK_ALLOCATION(newPlayers); // Check if memory allocation is successful

    // Initialize any new cells to NULL
    for (int i = *currentSize; i < newSize; i++) {
        newPlayers[i] = NULL;
    }

    *currentSize = newSize; // Update the current size to the new size
    return newPlayers; // Return the reallocated array
}






// Function to insert a player into a binary search tree
PlayerTreeNode* insertPlayerTree(PlayerTreeNode* root, Player* player) {
    if (root == NULL) {
        PlayerTreeNode* newNode = (PlayerTreeNode*)malloc(sizeof(PlayerTreeNode));
        if (!newNode) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }
        newNode->player = player;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }
    if (strcmp(player->name, root->player->name) < 0) {
        root->left = insertPlayerTree(root->left, player);
    }
    else {
        root->right = insertPlayerTree(root->right, player);
    }
    return root;
}




// Function to free the entire binary search tree of players
void freePlayerTree(PlayerTreeNode* root)
{
    if (root != NULL) {
        freePlayerTree(root->left);
        freePlayerTree(root->right);
        free(root);
    }
}


//Traversal by order
void inOrderTraversal(PlayerTreeNode* root, void (*func)(Player*))
{
    if (root != NULL)
    {
        inOrderTraversal(root->left, func);
        func(root->player);
        inOrderTraversal(root->right, func);
    }
}



//Code for build tree from array 
PlayerTreeNode* buildTreeFromArray(Player* array[], int start, int end) {
    if (start > end) return NULL;

    int mid = start + (end - start) / 2;

    PlayerTreeNode* node = (PlayerTreeNode*)malloc(sizeof(PlayerTreeNode));
    CHECK_ALLOCATION(node);

    // Copy the Player struct from the array to the tree node
    node->player = (array[mid]);  // Use dereferencing to copy the player struct

    node->left = buildTreeFromArray(array, start, mid - 1);
    node->right = buildTreeFromArray(array, mid + 1, end);
    return node;
}








/*
//code for create new player :
Player* createPlayer(const char* name)
{
    Player* newPlayer = (Player*)malloc(sizeof(Player));
    if (!newPlayer) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    strncpy(newPlayer->name, name, MAX_NAME_LENGTH - 1);
    newPlayer->name[MAX_NAME_LENGTH - 1] = '\0';  // Ensure null-termination
    newPlayer->possibleDigits = 0;  // Initialize with 0 filled cells
    memset(newPlayer->board, 0, sizeof(newPlayer->board));
    //newPlayer->next = NULL;
    return newPlayer;
}
*/

// Function to perform in-order traversal and process each player
void inOrderProcess(PlayerTreeNode* root, PlayersList* activePlayers, PlayersList* winnerPlayers,int* numOfActivePlayers)
{
    if (root == NULL)
        return;

    // Traverse left subtree
    inOrderProcess(root->left, activePlayers, winnerPlayers, numOfActivePlayers);

    // Process current player
    if (root->player != NULL) 
    {
        int x = 0, y = 0; // Coordinates for the cell with minimal possibilities
        int status = OneStage(root->player->board, root->player->possibleDigits, &x, &y);

        if (status == FINISH_FAILURE) {
            printf("%s has finished with failure and is out of the game.\n", root->player->name);
            removePlayerFromList(activePlayers, root->player);// Remove player from active list
            root->player = NULL;  // Set player pointer to NULL in the tree
            *numOfActivePlayers--;
        }
        else if (status == FINISH_SUCCESS) {
            printf("%s has finished successfully and is moved to the winner's list.\n", root->player->name);
            removePlayerFromList(activePlayers, root->player);// Remove player from active list
            insertPlayerToEndList(winnerPlayers, root->player); // Move player to winners list
            root->player = NULL;  // Set player pointer to NULL in the tree
            *numOfActivePlayers--;
        }
        else if (status == NOT_FINISH) {
            // Allow player to choose an option for the cell with minimal possibilities
            printf("Player %s hasnt finished and needs to face a selcetion of cell value:\n", root->player->name);
            fillCellWithInput(root->player->board, root->player->possibleDigits, x, y);
        }
    }

    // Traverse right subtree
    inOrderProcess(root->right, activePlayers, winnerPlayers, numOfActivePlayers);
}




// Function to print each player's board
// Function to print the Sudoku board to a file
void printBoardToFile(FILE* file, int board[SIZE][SIZE])
{
    if (!file) 
    {
        fprintf(stderr, "Invalid file pointer.\n");
        return;
    }

    // Print the header for columns
    fprintf(file, "   ");
    for (int col = 0; col < SIZE; col++)
    {
        fprintf(file, "%d ", col);
        if (col == 2 || col == 5) {
            fprintf(file, "| ");
        }
    }
    fprintf(file, "\n");

    // Print the top border
    fprintf(file, "  ");
    for (int col = 0; col < SIZE * 2 + 3; col++) 
    {
        fprintf(file, "-");
    }
    fprintf(file, "\n");

    // Print each row of the board
    for (int row = 0; row < SIZE; row++) {
        // Print the row index
        fprintf(file, "%d |", row);

        // Print each cell in the row
        for (int col = 0; col < SIZE; col++) {
            fprintf(file, "%d ", board[row][col]);
            if (col == 2 || col == 5) {
                fprintf(file, "| "); // Vertical separator for 3x3 subgrids
            }
        }

        // Print a new line after each row
        fprintf(file, "\n");

        // Print horizontal separators after each 3x3 subgrid
        if (row == 2 || row == 5) {
            fprintf(file, "  ");
            for (int col = 0; col < SIZE * 2 + 3; col++) {
                fprintf(file, "-");
            }
            fprintf(file, "\n");
        }
    }
}

// Function to print the list of winners and their boards to a text file
void printWinnersToFile(PlayersList* winnerList)
{
    FILE* file = fopen(FILE_NAME, "w");  // Open the file for writing
    if (file == NULL) {
        fprintf(stderr, "Error opening file for writing\n");
        return;
    }

    // Iterate through the list of winners
    PlayerNode* current = winnerList;
    while (current != NULL) {
        // Print each winner's name and their board
        fprintf(file, "Winner: %s\n", current->player->name);
        fprintf(file, "Board:\n");
        printBoardToFile(file, current->player->board);  // Print the board
        fprintf(file, "\n");  // Add a newline for separation between entries
        current = current->next;
    }

    fclose(file);  // Close the file
}




void freePlayerArray(Player** array, int size) {
    if (array == NULL) return; // Safety check

    // Loop through each Player* in the array and free the Player
    for (int i = 0; i < size; i++) {
        if (array[i] != NULL) {
            freePlayer(array[i]); // Free each individual Player
            array[i] = NULL; // Set the pointer to NULL after freeing
        }
    }

    // After all Player objects are freed, free the array itself
    free(array);
}
