#include "Player.h"




void freePlayer(Player* player)
{
    if (player == NULL) return; // Safety check to ensure the player is not NULL

    // Free the possibleDigits 3D array if it exists
    if (player->possibleDigits != NULL) {
        for (int i = 0; i < SIZE; i++) { // Assuming SIZE is the dimension of the board
            if (player->possibleDigits[i] != NULL) {
                for (int j = 0; j < SIZE; j++) {
                    free(player->possibleDigits[i][j]); // Free each 1D array inside the 2D arrays
                }
                free(player->possibleDigits[i]); // Free the 2D array inside the 3D array
            }
        }
        free(player->possibleDigits); // Finally, free the top-level array
        player->possibleDigits = NULL;
    }

    // No need to free 'name' and 'board' as they are not dynamically allocated
}
