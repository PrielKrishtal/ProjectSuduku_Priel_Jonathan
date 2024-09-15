#include "Player.h"




void freePlayer(Player* player)
{
    if (player == NULL) return; // Safety check to ensure the player is not NULL

    // Free the possibleDigits 3D array if it exists
    if (player->possibleDigits != NULL) {
        for (int i = 0; i < SIZE; i++) {
            if (player->possibleDigits[i] != NULL) {
                for (int j = 0; j < SIZE; j++) {
                    // Use freePos to free each individual Array structure
                    freePos(player->possibleDigits[i][j]); // Frees and sets to NULL
                }
                free(player->possibleDigits[i]); // Free the 2D array inside the 3D array
                player->possibleDigits[i] = NULL;
            }
        }
        free(player->possibleDigits); // Finally, free the top-level array
        player->possibleDigits = NULL;
    }

    // Free the player's name if it was dynamically allocated
    if (player->name != NULL) {
        free(player->name);
        player->name = NULL;
    }

    // Finally, free the player struct itself
    free(player);
}


