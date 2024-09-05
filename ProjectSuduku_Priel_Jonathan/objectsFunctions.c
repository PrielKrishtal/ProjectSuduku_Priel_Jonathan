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
int main() {
    srand(time(NULL));

    // Create the linked lists, array, and tree
    PlayerNode* winnerList = NULL;
    PlayerNode* activePlayerList = NULL;
    PlayerTreeNode* playerTree = NULL;
    Player* activePlayersArray[SIZE * SIZE];
    int activePlayersCount = 0;

    // Example: Adding players
    Player* player1 = createPlayer("Alice");
    Player* player2 = createPlayer("Bob");

    // Add players to lists
    addPlayerToList(&activePlayerList, player1);
    addPlayerToList(&activePlayerList, player2);

    addPlayerToArray(player1, activePlayersArray, &activePlayersCount);
    addPlayerToArray(player2, activePlayersArray, &activePlayersCount);

    playerTree = insertPlayerTree(playerTree, player1);
    playerTree = insertPlayerTree(playerTree, player2);

    // Create a linked list of all possible locations
    Node* locationList = createLocationList();
    int size = SIZE * SIZE;  // 81 cells on the board

    // Generate N, the number of cells to be filled (between 1 and 20)
    int N = randomInt(1, 20);

    // Select N random positions and fill them with random values
    for (int i = 0; i < N; i++) {
        int row, col;
        locationList = selectRandomLocation(locationList, size, &row, &col);
        size--;  // Reduce the size of the list after removing a position

        // Generate a random value for the selected position
        int possibleValues[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };  // Example set of possible values
        int value = randomLegalValue(possibleValues, 9);
        printf("Location: (%d, %d) - Value: %d\n", row, col, value);
    }

    // Free allocated memory
    freeList(locationList);
    freePlayerList(activePlayerList);
    freePlayerTree(playerTree);
    freePlayers(player1); // Freeing all players, assuming no further references

    return 0;
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
        Node* temp =    current->next;
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

// Function to add a player to a linked list
void addPlayerToList(PlayerNode** head, Player* player) {
    PlayerNode* newNode = (PlayerNode*)malloc(sizeof(PlayerNode));
    if (!newNode) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    newNode->player = player;
    newNode->next = *head;
    *head = newNode;
}

// Function to add a player to an array
void addPlayerToArray(Player* player, Player* array[], int* count) {
    if (*count < SIZE * SIZE) {
        array[*count] = player;
        (*count)++;
    }
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

// Function to free the entire linked list of players
void freePlayerList(PlayerNode* head) {
    while (head != NULL) {
        PlayerNode* temp = head;
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






///Traversal by order
void inOrderTraversal(PlayerTreeNode* root, void (func)(Player))
{
    if (root != NULL)
    {
        inOrderTraversal(root->left, func);
        func(root->player);
        inOrderTraversal(root->right, func);
    }
}



///Code for build tree from array :

PlayerTreeNode* buildTreeFromArray(Player* array[], int start, int end) {
    if (start > end) return NULL;

    int mid = start + (end - start) / 2;
    PlayerTreeNode* node = (PlayerTreeNode*)malloc(sizeof(PlayerTreeNode));
    if (!node) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    node->player = array[mid];
    node->left = buildTreeFromArray(array, start, mid - 1);
    node->right = buildTreeFromArray(array, mid + 1, end);
    return node;
}




////code for sort players :

void bubbleSort(Player* players[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (players[j]->filledCells > players[j + 1]->filledCells ||
                (players[j]->filledCells == players[j + 1]->filledCells &&
                    strcmp(players[j]->name, players[j + 1]->name) > 0)) {
                // Swap
                Player* temp = players[j];
                players[j] = players[j + 1];
                players[j + 1] = temp;
            }
        }
    }
}




////code for create new player :


Player* createPlayer(const char* name) {
    Player* newPlayer = (Player*)malloc(sizeof(Player));
    if (!newPlayer) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    strncpy(newPlayer->name, name, MAX_NAME_LENGTH - 1);
    newPlayer->name[MAX_NAME_LENGTH - 1] = '\0';  // Ensure null-termination
    newPlayer->filledCells = 0;  // Initialize with 0 filled cells
    memset(newPlayer->board, 0, sizeof(newPlayer->board));
    newPlayer->next = NULL;
    return newPlayer;
}