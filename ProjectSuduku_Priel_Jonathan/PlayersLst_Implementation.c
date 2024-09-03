#include "HeaderforEX1.h"


void makeEmptyPlayersList(PlayersList* lst) {
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

