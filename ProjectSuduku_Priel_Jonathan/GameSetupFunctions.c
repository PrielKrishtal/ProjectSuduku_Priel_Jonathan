#include "GameSetup.h"

//Function that initalizes the board cells to -1 (aka empty cell)
void initializeBoard(short board[SIZE][SIZE]) 
{
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = -1;
        }
    }
}


// Function to create a Player(getting his name,generating Board, possibilities board etc)
Player* createPlayer()
{
    char buffer[MAX_NAME_LENGTH]; //insure the name is 100 char len max
    printf("Enter Player's name: ");
    scanf("%s", buffer);

    Player* newPlayer = (Player*)malloc(sizeof(Player));

    newPlayer->name = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
    CHECK_ALLOCATION(newPlayer->name);

    strncpy(newPlayer->name, buffer, strlen(buffer) + 1); // +1 to include the null terminator

    initializeBoard(newPlayer->board);
    createRandomBoard(newPlayer->board); // Fill the player's board with random values
    newPlayer->possibleDigits = PossibleDigits(newPlayer->board); // Initialize the possible digits array for the board



    return newPlayer;
}

// Function that gets the number of active players
void getNumActivePlayers(int* x)
{
    int input;
    printf("Pls enter number of active players:");
    scanf("%d", &input);

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


//Funcion that creates the active players list (PlayersList type) and Fills it using given info from the user
void create_And_Fill_ActivePlayersList(PlayersList* lst, int numPlayers)
{
    makeEmptyPlayersList(lst); // Initialize the list to be empty
    Player* newPlayer;

    for (int i = 0; i < numPlayers; i++) {
        
         newPlayer = createPlayer(); // Create a new player

        insertPlayerToEndList(lst, newPlayer); // Insert the player at the end of the list as a PlayerNode(Parallel to InsertDataToEndOfLst)
    }
   
}

// Function that counts filled cells in a Sudoku board
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



// Function that creates and sort an array of PlayerNode pointers 
PlayerNode** createAndSortPlayerArray(PlayersList* list,int size)
{
    // Allocate an array of player node pointers of the right size
    PlayerNode** playerNodePointerArray = (PlayerNode**)malloc(size * sizeof(PlayerNode*));
    CHECK_ALLOCATION(playerNodePointerArray);  // Use the macro to check allocation and handle any failure


    // Fill the array with pointers to the players
    PlayerNode* current = list->head;  // set current pointer to the head of the list
    for (int index = 0; index < size && current != NULL; index++) {
        playerNodePointerArray[index] = current; // Assign the player node pointer to the array
        current = current->next;  // Move to the next node
    }

    // Now sort the array using the modified bubble sort function
    bubbleSort(playerNodePointerArray, size);  // Sort the array based on the sorting criteria defined in bubbleSort



    return playerNodePointerArray;  // Return the sorted array of player pointers
}


// Function that sorts an array of PlayerNode pointers based on filled cells and names
void bubbleSort(PlayerNode** playerNodes, int count)

{
    // Outer loop: iterate through each player node in the array except the last one
    for (int i = 0; i < count - 1; i++) {
        // Inner loop: go through the player nodes up to the part of the array that's still unsorted
        for (int j = 0; j < count - i - 1; j++) {

            int filledCellsCurrent = CountFilledCells(playerNodes[j]->player->board); // Get filled cells count for the current player
            int filledCellsNext = CountFilledCells(playerNodes[j + 1]->player->board); // Get filled cells count for the next player

            // Check if the current player node should swap places with the next one based on filled cells
            if (filledCellsCurrent < filledCellsNext) {
                // Swap the current player node with the next one
                PlayerNode* temp = playerNodes[j];
                playerNodes[j] = playerNodes[j + 1];
                playerNodes[j + 1] = temp;
            }

            // If the filled cell count is the same, then compare names
            else if (filledCellsCurrent == filledCellsNext && strcmp(playerNodes[j]->player->name, playerNodes[j + 1]->player->name) > 0) {
                // Swap the current player node with the next one based on name comparison
                PlayerNode* temp = playerNodes[j];
                playerNodes[j] = playerNodes[j + 1];
                playerNodes[j + 1] = temp;
            }
        }
    }
}



// Helper function to resize the array of PlayerNode pointers
PlayerNode** resizeArray(PlayerNode** playerNodes, int* currentSize)

{
    int newSize = CALCULATE_NEW_SIZE(*currentSize); // Calculate new size using the formula defined as a macro

    // Reallocate the existing array to the new size
    PlayerNode** newPlayerNodes = (PlayerNode**)realloc(playerNodes, newSize * sizeof(PlayerNode*));
    CHECK_ALLOCATION(newPlayerNodes); // Check if memory allocation is successful

    // Initialize any new cells to NULL
    for (int i = *currentSize; i < newSize; i++) {
        newPlayerNodes[i] = NULL;
    }

    *currentSize = newSize; // Update the current size to the new size
    return newPlayerNodes; // Return the reallocated array
}



// Function to insert a player node pointer (pointing to a cell in the array) into a binary search tree
PlayerTreeNode* insertPlayerTree(PlayerTreeNode* root, PlayerNode** playerNodePtr) {
    if (root == NULL) {
        // Create a new tree node
        PlayerTreeNode* newNode = (PlayerTreeNode*)malloc(sizeof(PlayerTreeNode));
        CHECK_ALLOCATION(newNode); // Use macro to check memory allocation

        newNode->playerNodePtr = playerNodePtr;  // Store the pointer to the cell in the array
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }

    // Compare based on the player's name pointed to by playerNodePtr
    if (strcmp((*playerNodePtr)->player->name, (*root->playerNodePtr)->player->name) < 0) {
        root->left = insertPlayerTree(root->left, playerNodePtr); // Insert in the left subtree
    }
    else {
        root->right = insertPlayerTree(root->right, playerNodePtr); // Insert in the right subtree
    }

    return root;
}




// Function to free the entire binary tree
void freePlayerTree(PlayerTreeNode* root)
{
    if (root != NULL) {
        freePlayerTree(root->left);   // Recursively free the left subtree
        freePlayerTree(root->right);  // Recursively free the right subtree
        
        free(root);  // Free the current tree node

    }
}






// Code for building a binary tree from a sorted array of PlayerNode pointers
PlayerTreeNode* buildTreeFromArray(PlayerNode** array, int start, int end)
{
    if (start > end) return NULL;  // Base case: no elements to include in the tree

    int mid = start + (end - start) / 2;  // Calculate middle index

    // Allocate memory for a new tree node
    PlayerTreeNode* node = (PlayerTreeNode*)malloc(sizeof(PlayerTreeNode));
    CHECK_ALLOCATION(node);  // Check if memory allocation was successful

    // Assign the middle element of the array to the tree node
    node->playerNodePtr = &array[mid];  // Assign the pointer to the PlayerNode

    // Recursively build the left subtree
    node->left = buildTreeFromArray(array, start, mid - 1);

    // Recursively build the right subtree
    node->right = buildTreeFromArray(array, mid + 1, end);

    return node;  // Return the newly created tree node
}



// Function to perform in-order traversal and process each player
void inOrderProcess(PlayerTreeNode* root, PlayersList* activePlayers, PlayersList* winnerPlayers)
{
    if (root == NULL)
        return;

    // Traverse left subtree
    inOrderProcess(root->left, activePlayers, winnerPlayers);

    // Process current player
    if (root->playerNodePtr != NULL && *root->playerNodePtr != NULL && (*root->playerNodePtr)->player != NULL)  // Check if node, playerNode, and player are not NULL
    {
        Player* currentPlayer = (*root->playerNodePtr)->player;  // Access the player from the PlayerNode pointer stored in the tree node
        printf("\n");
        printf("Currently Playing: %s\n", currentPlayer->name);
        printf("_____________________________________\n\n");
        printf("%s's Initial Board:\n\n", currentPlayer->name); // Printing for user's interface
        printBoard(currentPlayer->board);
        printf("\n");

        int status = FillBoard(currentPlayer->board, currentPlayer->possibleDigits); // Use FillBoard to process the player's board

        if (status == FINISH_FAILURE) {
            printf("%s's result: finished with failure and is out of the game.\n\n", currentPlayer->name);
            removePlayerFromList(activePlayers, currentPlayer); // Remove player from active list
            (*root->playerNodePtr)->player = NULL;  // Nullify the player pointer in the PlayerNode
        }
        else if (status == FINISH_SUCCESS) {
            printf("%s's result: finished successfully and is moved to the winner's list.\n\n", currentPlayer->name);
            insertPlayerToEndList(winnerPlayers, currentPlayer); // Move player to winners list
            (*root->playerNodePtr)->player = NULL;  // Nullify the player pointer in the PlayerNode
        }
        else if (status == NOT_FINISH) {
            // This branch might be redundant depending on how FillBoard handles NOT_FINISH statuses
            printf("%s's result: has not finished yet and may need further actions.\n\n", currentPlayer->name);
        }
    }

    // Traverse right subtree
    inOrderProcess(root->right, activePlayers, winnerPlayers);
}



// Function to print the Sudoku board to a file
void printBoardToFile(FILE* file, short board[SIZE][SIZE])
{
    if (!file)
    {
        fprintf(stderr, "Invalid file pointer.\n");
        return;
    }

    // Print the header for columns
    fprintf(file, "   | ");
    for (int col = 0; col < SIZE; col++) {
        fprintf(file, "%d ", col);  // Print the column headers
        if ((col + 1) % 3 == 0 && col < SIZE - 1) {
            fprintf(file, " | ");  // Print vertical separators for columns
        }
    }
    fprintf(file, "\n");

    // Print a separator line before the board starts
    fprintf(file, "-----------------------------\n");

    for (int i = 0; i < SIZE; i++) {
        fprintf(file, "%d | ", i);  // Print the row number followed by a vertical line
        for (int j = 0; j < SIZE; j++) {
            fprintf(file, "%2d", board[i][j]);  // Print the value with correct spacing
            if ((j + 1) % 3 == 0 && j < SIZE - 1) {
                fprintf(file, " | ");  // Print vertical separators within the row
            }
        }
        fprintf(file, "\n");
        if ((i + 1) % 3 == 0 && i < SIZE - 1) {
            fprintf(file, "-----------------------------\n");  // Print horizontal separators after every 3 rows
        }
    }

    // Print a separator line at the bottom of the board
    fprintf(file, "-----------------------------\n");
}


// Function to print the list of winners and their boards to a text file
void printWinnersToFile(PlayersList* winnerList) {
    FILE* file = fopen(FILE_NAME, "w");  // Open the file for writing
    if (file == NULL) {
        fprintf(stderr, "Error opening file for writing\n");
        return;
    }

    

    PlayerNode* current = winnerList->head;
    while (current != NULL) {
        if (current->player != NULL) { // Check if the player has not been set to NULL after removal
            fprintf(file, "Winner: %s\n", current->player->name);
            fprintf(file, "Board:\n");
            if (current->player->board != NULL) {
                printBoardToFile(file, current->player->board);
            }
            else {
                fprintf(file, "No board data available.\n");
            }
            fprintf(file, "\n");
        }
        current = current->next;
    }

    fclose(file);  // Close the file
}






// Function to free an array of PlayerNode pointers
void freePlayerNodeArray(PlayerNode** playerPointersArray, int size)
{
    if (playerPointersArray == NULL) return; // Safety check

    // Loop through each PlayerNode* in the array and free the PlayerNode and the Player
    for (int i = 0; i < size; i++) {
        if (playerPointersArray[i] != NULL) {
            if (playerPointersArray[i]->player != NULL) {
                free(playerPointersArray[i]->player); // Free the Player struct inside the PlayerNode
                playerPointersArray[i]->player = NULL; // Set the pointer to NULL after freeing
            }
             
            playerPointersArray[i] = NULL; // Set the pointer to NULL after freeing
        }
    }

    // After all PlayerNode objects are freed, free the array itself
    free(playerPointersArray);
}




// Function to count the number of players in a linked list
int countPlayersInList(PlayersList* winnerList)
{
    int count = 0;
    PlayerNode* current = winnerList->head;  // Start with the head of the list

    // Traverse the linked list and count each node
    while (current != NULL) {
        count++;  // Increment count for each player found
        current = current->next;  // Move to the next node in the list
    }

    return count;  // Return the total number of players in the list
}