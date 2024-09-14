#include "PlayersLst.h"

void makeEmptyPlayersList(PlayersList* lst)
{
    lst->head = lst->tail = NULL;
}

bool isEmptyPlayersList(PlayersList* lst) {
    return lst->head == NULL;
}

PlayerNode* getPlayerNode(PlayersList* lst, int index) {
    PlayerNode* current = lst->head;
    int count = 0;
    while (current != NULL && count < index) {
        current = current->next;
        count++;
    }
    return current;
}

PlayerNode* createNewPlayerNode(Player* player, PlayerNode* next) {
    PlayerNode* node = (PlayerNode*)malloc(sizeof(PlayerNode));
    CHECK_ALLOCATION(node);
    node->player = player;
    node->next = next;
    return node;
}

void insertPlayerToStartList(PlayersList* lst, Player* player) {
    PlayerNode* node = createNewPlayerNode(player, lst->head);
    lst->head = node;
    if (lst->tail == NULL) {
        lst->tail = node;
    }
}

void insertPlayerNodeToStartList(PlayersList* lst, PlayerNode* node) {
    node->next = lst->head;
    lst->head = node;
    if (lst->tail == NULL) {
        lst->tail = node;
    }
}

void insertPlayerToEndList(PlayersList* lst, Player* player) {
    PlayerNode* node = createNewPlayerNode(player, NULL);
    if (lst->tail == NULL) {
        lst->head = lst->tail = node;
    }
    else {
        lst->tail->next = node;
        lst->tail = node;
    }
}

void insertPlayerNodeToEndList(PlayersList* lst, PlayerNode* node) {
    node->next = NULL;
    if (lst->tail == NULL) {
        lst->head = lst->tail = node;
    }
    else {
        lst->tail->next = node;
        lst->tail = node;
    }
}

bool insertPlayerToPlaceInList(PlayersList* lst, Player* player, int index) {
    if (index == 0) {
        insertPlayerToStartList(lst, player);
        return true;
    }
    PlayerNode* prev = getPlayerNode(lst, index - 1);
    if (prev == NULL) {
        return false;
    }
    PlayerNode* node = createNewPlayerNode(player, prev->next);
    prev->next = node;
    if (node->next == NULL) {
        lst->tail = node;
    }
    return true;
}

bool insertPlayerNodeToPlaceInList(PlayersList* lst, PlayerNode* node, int index) {
    if (index == 0) {
        insertPlayerNodeToStartList(lst, node);
        return true;
    }
    PlayerNode* prev = getPlayerNode(lst, index - 1);
    if (prev == NULL) {
        return false;
    }
    node->next = prev->next;
    prev->next = node;
    if (node->next == NULL) {
        lst->tail = node;
    }
    return true;
}

void removePlayerFromList(PlayersList* lst, Player* player)
{
    PlayerNode* current = lst->head;
    PlayerNode* previous = NULL;

    while (current != NULL) {
        if (current->player == player) {
            if (previous == NULL) { // Player is at the head
                lst->head = current->next;
                if (current->next == NULL) { // It was the only node, so update tail as well
                    lst->tail = NULL;
                }
            }
            else {
                previous->next = current->next;
                if (current->next == NULL) { // Player is at the tail
                    lst->tail = previous;
                }
            }
            free(current);  // Free the node, assuming player data is handled elsewhere
            return;  // Exit after removal
        }
        previous = current;
        current = current->next;
    }
}


void freePlayersList(PlayersList* lst) 
{
    if (lst == NULL) return; // Safety check to ensure the list is not NULL

    PlayerNode* current = lst->head;
    while (current != NULL) {
        PlayerNode* next = current->next; // Save reference to the next node

        freePlayer(current->player); // Free the player data using the freePlayer function
        free(current); // Free the node itself

        current = next; // Move to the next node
    }

    // Reset the list pointers after the list is completely freed
    lst->head = NULL;
    lst->tail = NULL;
}
