#include "functionsForMain.h"


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
    printf("Player's board:\n\n");
    printBoard(newPlayer->board);
    printf("\n");
    printf("\n**********************\n");
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
        printf("value generated randomly for cell [%d][%d] is: %d\n", row, col, board[row][col]);
        
        // Print the board state after each assignment
        printf("Current state of the board after updating [%d][%d]:\n", row, col);
        printBoard(board);

    }

    printf("List of randoms:\n");
    printCellsList(&locationList, board);

    // Clean up the remaining nodes in the list
    freeListOfCells(&locationList);

   
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




// Function to create and sort an array of player pointers from a linked list of players
Player** createAndSortPlayerArray(PlayersList* list,int size) {
    
    

    // Allocate an array of player pointers of the right size
    Player** playerArray = (Player**)malloc(size * sizeof(Player*));
    CHECK_ALLOCATION(playerArray);  // Use the macro to check allocation and handle any failure

    // Fill the array with pointers to the players
    PlayerNode* current = list->head;  // set current pointer to the head of the list
    for (int i = 0; i < size; i++) {
        if (current != NULL) {
            playerArray[i] = current->player;  // Assign the player pointer to the array
            current = current->next;  // Move to the next node
        }
    }

    // Now sort the array using the modified bubble sort function
    bubbleSort(playerArray, size);  // Sort the array based on the sorting criteria defined in bubbleSort

    return playerArray;  // Return the sorted array of player pointers
}



// Function to calculate the next size based on the formula
int calculateNewSize(int currentSize)
{
    int x = currentSize + 1; // x is current size + 1
    int newSize = (int)pow(2, ceil(log2(x))) - 1; // Calculate the new size using the formula
    return newSize;
}

// Helper function to resize the array of pointers
Player** resizeArray(Player** players, int* currentSize)
{
    int newSize = calculateNewSize(*currentSize); // Calculate new size using the formula

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




//Function that does the sorts the pointers of the PlayerNode's in ActivePlayers
void bubbleSort(Player** players, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (players[j]->possibleDigits > players[j + 1]->possibleDigits ||
                (players[j]->possibleDigits == players[j + 1]->possibleDigits &&
                    strcmp(players[j]->name, players[j + 1]->name) > 0)) {
                // Swap
                Player* temp = players[j];
                players[j] = players[j + 1];
                players[j + 1] = temp;
            }
        }
    }
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
void inOrderProcess(PlayerTreeNode* root, PlayersList* activePlayers, PlayersList* winnerPlayers)
{
    if (root == NULL)
        return;

    // Traverse left subtree
    inOrderProcess(root->left, activePlayers, winnerPlayers);

    // Process current player
    if (root->player != NULL) 
    {
        int x = 0, y = 0; // Coordinates for the cell with minimal possibilities
        int status = OneStage(root->player->board, root->player->possibleDigits, &x, &y);

        if (status == FINISH_FAILURE) {
            printf("%s has finished with failure and is out of the game.\n", root->player->name);
            removePlayerFromList(activePlayers, root->player);// Remove player from active list
            root->player = NULL;  // Set player pointer to NULL in the tree
        }
        else if (status == FINISH_SUCCESS) {
            printf("%s has finished successfully and is moved to the winner's list.\n", root->player->name);
            insertPlayerToEndList(winnerPlayers, root->player); // Move player to winners list
            root->player = NULL;  // Set player pointer to NULL in the tree
        }
        else if (status == NOT_FINISH) {
            // Allow player to choose an option for the cell with minimal possibilities
            fillCellWithInput(root->player->board, root->player->possibleDigits, x, y);
        }
    }

    // Traverse right subtree
    inOrderProcess(root->right, activePlayers, winnerPlayers);
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
void printWinnersToFile(PlayerNode* winnerList)
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


//helper function to view suduko board printed as needed
void printSudoku(int board[SIZE][SIZE]) 
{
    // Print the header for columns
    printf("   ");
    for (int col = 0; col < SIZE; col++) {
        printf("%d ", col);
        if (col == 2 || col == 5) {
            printf("| ");
        }
    }
    printf("\n");

    // Print the top border
    printf("  ");
    for (int col = 0; col < SIZE * 2 + 3; col++) {
        printf("-");
    }
    printf("\n");

    // Print each row of the board
    for (int row = 0; row < SIZE; row++) {
        // Print the row index
        printf("%d |", row);

        // Print each cell in the row
        for (int col = 0; col < SIZE; col++) {
            printf("%d ", board[row][col]);
            if (col == 2 || col == 5) {
                printf("| "); // Vertical separator for 3x3 subgrids
            }
        }

        // Print a new line after each row
        printf("\n");

        // Print horizontal separators after each 3x3 subgrid
        if (row == 2 || row == 5) {
            printf("  ");
            for (int col = 0; col < SIZE * 2 + 3; col++) {
                printf("-");
            }
            printf("\n");
        }
    }
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
