#include "HeaderForEX1.h"

// Function prototypes
/*
Node* createLocationList();
int randomInt(int min, int max);
Node* deleteNode(Node * head, int index);
Node* selectRandomLocation(Node * head, int size, int* row, int* col);
int randomLegalValue(int possibleValues[], int count);
Player* createPlayer(const char* name);
void addPlayerToList(PlayerNode * *head, Player * player);
void addPlayerToArray(Player * player, Player * array[], int* count);
PlayerTreeNode* insertPlayerTree(PlayerTreeNode * root, Player * player);
void freeList(Node * head);
void freePlayerList(PlayerNode * head);
void freePlayerTree(PlayerTreeNode * root);
void freePlayers(Player * head);
*/

void getNumActivePlayers(int* x)
{
    printf("Pls enter number of active players:");
    scanf("%d", &x);
    //todo: add validity number check
}




// Function to fill a board with random values
void createRandomBoard(int board[SIZE][SIZE]) {
    srand(time(NULL)); // Initialize random seed

    Node* locationList = createLocationList(); // Create a list of all board positions
    int listSize = SIZE * SIZE; // Start with the maximum number of cells

    // Determine the number of cells to randomly fill (between 1 and 20)
    int cellsToFill = randomInt(1, 20);

    for (int i = 0; i < cellsToFill; i++) {
        int row, col;
        // Select a random location from the list
        locationList = selectRandomLocation(locationList, listSize--, &row, &col);

        // Define possible values for a Sudoku cell (for simplification, using all values)
        int possibleValues[SIZE] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        // Assign a random valid value to the selected board cell
        board[row][col] = randomLegalValue(possibleValues, SIZE);
    }

    // Clean up the remaining nodes in the list
    Node* current = locationList;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}




//Funcion that creates a PlayersList and Fills it in using given info from the user
PlayersList create_And_Fill_ActivePlayersList(int numPlayers)
{
    PlayersList lst; // Declare the players list
    makeEmptyPlayersList(&lst); // Initialize the list to be empty

    for (int i = 0; i < numPlayers; i++) {
        char* playerName = (char*)malloc(MAX_NAME_LENGTH * sizeof(char)); // Allocate memory for the player name
        CHECK_ALLOCATION(playerName);

        printf("Enter player's name: ");
        scanf("%99s", playerName); // Read the name from user input, ensuring not to exceed the buffer size

        Player* newPlayer = createPlayer(playerName); // Create a new player with the given name
        createRandomBoard(newPlayer->board); // Fill the player's board with random values
        newPlayer->possibleDigits = PossibleDigits(newPlayer->board); // Initialize the possible digits array for the board

        insertPlayerToEndList(&lst, newPlayer); // Insert the player at the end of the list as a PlayerNode

        free(playerName); // Free the allocated memory for the name after it's copied in createPlayer
    }

    return lst; // Return the filled list
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

















void main() {
    srand(time(NULL));
    // Create the linked lists, array, and tree
    PlayersList winnerList; 
    PlayersList activePlayerList; 
    PlayersTree tree_Of_Players;
    Player* activePlayersArray[SIZE * SIZE];
    int activePlayersCount = 0;
    getNumActivePlayers(&activePlayersCount); //getting number of active players from user

    //create and fill the active players list based on the given size
    PlayersList activePlayerList = create_And_Fill_ActivePlayersList(&activePlayersCount);

    Player** playerPointersArray = createAndSortPlayerArray(&activePlayerList, &activePlayersCount);

    // Resize the player array and also update activePlayersCount value
    playerPointersArray = resizeArray(playerPointersArray, &activePlayersCount); // Resize the array directly
    
    
    tree_Of_Players.root = buildTreeFromArray(&playerPointersArray,0,&activePlayersCount); //using build treeFromArray as setting it as our's tree's root


    if (activePlayersCount > 0) //if we have at least 1 active player
    {
        inOrderProcess(tree_Of_Players.root, &activePlayerList, &winnerList);
        void printBoardToFile(FILE * file, int board[SIZE][SIZE]); // need to handle diffrently as if i get file(?)
        printWinnersToFile(&winnerList, const char* filename);
        
    }
    

   

    // Free allocated memory
    
    

    
}

// Function to create a linked list of all possible positions on the board
Node* createLocationList() {
    Node* head = NULL;
    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            Node* newNode = (Node*)malloc(sizeof(Node));
            if (!newNode) {
                fprintf(stderr, "Memory allocation failed\n");
                exit(1);
            }
            newNode->row = r;
            newNode->col = c;
            newNode->next = head;
            head = newNode;
        }
    }
    return head;
}

// Function to generate a random number between min and max
int randomInt(int min, int max) {
    return rand() % (max - min + 1) + min;
}

// Function to delete a node from the linked list at a specific index
Node* deleteNode(Node* head, int index) {
    if (index < 0) return head;

    if (index == 0) {
        Node* temp = head;
        head = head->next;
        free(temp);
        return head;
    }

    Node* current = head;
    for (int i = 0; i < index - 1 && current != NULL; i++) {
        current = current->next;
    }
    if (current != NULL && current->next != NULL) {
        Node* temp = current->next;
        current->next = temp->next;
        free(temp);
    }
    return head;
}

// Function to select a random position from the linked list
Node* selectRandomLocation(Node* head, int size, int* row, int* col) {
    if (size <= 0) return head;  // No positions to select from

    int k = randomInt(0, size - 1);
    Node* current = head;
    for (int i = 0; i < k && current != NULL; i++) {
        current = current->next;
    }
    if (current) {
        *row = current->row;
        *col = current->col;
        return deleteNode(head, k);
    }
    return head;
}

// Function to generate a valid random value for a cell
int randomLegalValue(int possibleValues[], int count) {
    int index = randomInt(0, count - 1);
    return possibleValues[index];
}

// Function to create a player
Player* createPlayer(const char* name) {
    Player* newPlayer = (Player*)malloc(sizeof(Player));
    if (!newPlayer) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    strncpy(newPlayer->name, name, MAX_NAME_LENGTH - 1);
    newPlayer->name[MAX_NAME_LENGTH - 1] = '\0';  // Ensure null-termination
    // Initialize board and possibleDigits if needed
    newPlayer->next = NULL;
    return newPlayer;
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

// Function to free the entire linked list of positions
void freeList(Node* head) {
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
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

// Function to free all Player objects
void freePlayers(Player* head) {
    while (head != NULL) {
        Player* temp = head;
        head = head->next;
        free(temp);
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



//Code for build tree from array :
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
    newPlayer->next = NULL;
    return newPlayer;
}


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
            removePlayerFromList(activePlayers, root->player);  // Remove player from active list
            root->player = NULL;  // Set player pointer to NULL in the tree
        }
        else if (status == FINISH_SUCCESS) {
            printf("%s has finished successfully and is moved to the winner's list.\n", root->player->name);
            movePlayerToWinnersList(activePlayers, winnerPlayers, root->player); // Move player to winners list
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
void printWinnersToFile(PlayerNode* winnerList, const char* filename)
{
    FILE* file = fopen(filename, "w");  // Open the file for writing
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
/*
void printSudoku(int board[SIZE][SIZE]) {
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
*/