#include "SudokuUtilities.h"
#include "PlayersLst.h"
#include "PlayersTree.h"
#include "GameSetup.h"
#include "Player.h"


void main() {

    printf("=======================================================================\n");
    printf("||                        Sudoku Board Game                          ||\n");
    printf("=======================================================================\n\n");
    srand(time(NULL));

    // Create the linked lists, array, and tree:
    PlayersList winnerList, activePlayerList; //creating 2 players lists: 1 for active playes and the second one for winners
    PlayersTree tree_Of_Players; //creating tree of players
    
    makeEmptyPlayersList(&winnerList);//initalizing the winner's payers list

    int activePlayersCount = 0;
    getNumActivePlayers(&activePlayersCount); //getting the number of active players from user
    printf("\n");
    
    create_And_Fill_ActivePlayersList(&activePlayerList, activePlayersCount);//create and fill the active players list based on the given size
    printf("\n");
   
    
    PlayerNode** playerPointersArray = createAndSortPlayerArray(&activePlayerList, activePlayersCount);// cearting and sorting the array of pointers to Player's nodes

    
    playerPointersArray = resizeArray(playerPointersArray, &activePlayersCount);// Resize the player array and also update activePlayersCount value


    tree_Of_Players.root = buildTreeFromArray(playerPointersArray, 0, (activePlayersCount-1)); //generating a Player's tree using treeFromArray


    if (activePlayersCount > 0) //if we have at least 1 active player
    {
        
        inOrderProcess(tree_Of_Players.root, &activePlayerList, &winnerList);

        int numWinners = countPlayersInList(&winnerList);//using a helper function to count the amount of winners(aka size of winnersList)
       
        printf("--------------------------------------------------\n");
        printf("Game Result : We have %d winners\n", numWinners);
        printf("--------------------------------------------------\n");
        if (numWinners > 0) //making sure there is at least 1 winner
        {
            printWinnersToFile(&winnerList, FILE_NAME); //printing winners detailes(Name,Board) to a file
        }
    }




    // Free allocated memory
    freePlayerNodeArray(playerPointersArray, activePlayersCount);
    freePlayersList(&activePlayerList);
    freePlayersList(&winnerList);
    freePlayerTree(tree_Of_Players.root);
}
