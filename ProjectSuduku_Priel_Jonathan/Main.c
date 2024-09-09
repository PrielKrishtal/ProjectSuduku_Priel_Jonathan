#include "HeaderForEX1.h"
#include "PlayersLst.h"
#include "PlayersTree.h"
#include "functionsForMain.h"
#include "Player.h"

// main for testing

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
    
    

    Player** playerPointersArray = createAndSortPlayerArray(&activePlayerList, &activePlayersCount);

    // Resize the player array and also update activePlayersCount value
    playerPointersArray = resizeArray(playerPointersArray, &activePlayersCount); // Resize the array directly


    tree_Of_Players.root = buildTreeFromArray(&playerPointersArray, 0, &activePlayersCount); //using build treeFromArray as setting it as our's tree's root


    if (activePlayersCount > 0) //if we have at least 1 active player
    {
        inOrderProcess(tree_Of_Players.root, &activePlayerList, &winnerList);
        void printBoardToFile(FILE * file, int board[SIZE][SIZE]); // need to handle diffrently as if i get file(?)
        printWinnersToFile(&winnerList, FILE_NAME);

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
