//
// Created by pitf9 on 22.12.2018.
//

#ifndef PRI_PROJECT_3_STACK_H
#define PRI_PROJECT_3_STACK_H

#include "fileIO.h"

typedef struct Stack Stack;
struct Stack{
    uint id;
    char rumor[MAX_STRING];
    Stack *next;
};

Stack* createStack(char* rumor, Stack* head);

uint countRumors(Stack* head);

void freeStack(Stack* head);

#endif //PRI_PROJECT_3_STACK_H
