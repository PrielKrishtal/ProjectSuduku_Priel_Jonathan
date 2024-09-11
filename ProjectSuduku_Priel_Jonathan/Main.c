#include "HeaderForEX1.h"
#include "PlayersLst.h"
#include "PlayersTree.h"
#include "functionsForMain.h"
#include "Player.h"

// main for testing

void printAllPlayerBoards(PlayersList* list)
{
    PlayerNode* current = list->head;  // Start with the head of the list
    int playerNumber = 1;  // To keep track of player numbers for easier readability

    while (current != NULL) {  // Traverse until the end of the list
        printf("Player #%d - %s: board:\n", playerNumber++,current->player->name);
        printBoard(current->player->board);  // Assuming printBoard is defined to handle the board printing
        printf("\n");  // Print a newline for better formatting between boards

        current = current->next;  // Move to the next node in the list
    }
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


void main() {
    srand(time(NULL));
    // Create the linked lists, array, and tree
    PlayersList winnerList, activePlayerList;
    PlayersTree tree_Of_Players;

    makeEmptyPlayersList(&winnerList);

    int activePlayersCount = 0;
    getNumActivePlayers(&activePlayersCount); //getting number of active players from user

    //create and fill the active players list based on the given size
    create_And_Fill_ActivePlayersList(&activePlayerList, activePlayersCount);
    printf("\n");
    printAllPlayerBoards(&activePlayerList);
    
    Player** playerPointersArray = createAndSortPlayerArray(&activePlayerList, activePlayersCount);

    // Resize the player array and also update activePlayersCount value
    playerPointersArray = resizeArray(playerPointersArray, &activePlayersCount); // Resize the array directly


    tree_Of_Players.root = buildTreeFromArray(playerPointersArray, 0, (activePlayersCount-1)); //using build treeFromArray as setting it as our's tree's root


    if (activePlayersCount > 0) //if we have at least 1 active player
    {
        printf("Before: %d players\n", activePlayersCount);
        inOrderProcess(tree_Of_Players.root, &activePlayerList, &winnerList);
        int numWinners = countPlayersInList(&winnerList);
        if (numWinners > 0)
        {
           
            printWinnersToFile(&winnerList, FILE_NAME);
        }
        printf("We have %d winners\n", numWinners);
          
        

    }




    // Free allocated memory
    freePlayersList(&activePlayerList);
    freePlayersList(&winnerList);
    freePlayerArray(playerPointersArray, activePlayersCount);
    freePlayerTree(tree_Of_Players.root);



}






/* 
void main() {
    short sudokuBoard[9][9] = {
        { 5,-1, 4,-1, 7,-1,-1, 1,-1},
        { 6,-1, 2, 1,-1,-1, 3,-1,-1},
        { 1,-1, 8,-1, 4,-1,-1, 6,-1},
        {-1, 5,-1,-1, 6,-1,-1, 2,-1},
        {-1, 2,-1, 8,-1, 3,-1,-1,-1},
        {-1,-1,-1,-1,-1, 4,-1, 5, 6},
        {-1, 6, 1, 5, 3, 7, 2, 8, 4},
        {-1, 8, 7,-1, 1, 9,-1, 3,-1},
        {-1,-1,-1, 2, 8,-1,-1,-1, 9 }
    };

    printf("Initial Sudoku Board:\n");
    printBoard(sudokuBoard); // Assumes printBoard function is defined to print the board state
    printf("\n");

    Array*** possibleDigits = PossibleDigits(sudokuBoard); // Initialize possible digits array

    // Display initial possibilities for debugging or user information
    printf("Initial possible digits for each cell:\n");
    printPossibleDigits(possibleDigits);
    printf("\n");

    // Call FillBoard to process the entire board with user inputs and solving logic
    int finalStatus = FillBoard(sudokuBoard, possibleDigits);
    printf("Final Board Status: %s\n", finalStatus == FINISH_SUCCESS ? "Solved" : "Not Solved");

    }
    free(possibleDigits); // Free the top-level pointer



}

*/
