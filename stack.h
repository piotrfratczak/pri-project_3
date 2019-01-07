/*
 * PRI Project n3
 * Rumor Transmitter
 *
 * Created by Piotr Fratczak on 22.12.2018.
 * Warsaw University of Technology
 */

#ifndef PRI_PROJECT_3_STACK_H
#define PRI_PROJECT_3_STACK_H

#include "utils.h"

typedef struct Stack Stack;
struct Stack{
    uint id;
    uint position;
    char rumor[MAX_STRING];
    Stack *next;
};

Stack* createRumor(char* rumor, uint id, Stack* head);

Stack* delRumor(Stack* obsolete, Stack* head);

Stack* removeStackHead(Stack* head);

Stack* moveRumor(Stack* mover, Stack* head, uint newLocationId);

char* getRumor(Stack* rumorPtr);

uint stackSize(Stack* head);

void updateRumorPositions(Stack* head);

Stack* findRumorById(uint id, Stack* head);

uint findStackIdByPosition(uint position, Stack *head);

void freeStack(Stack* head);

#endif //PRI_PROJECT_3_STACK_H
