//
// Created by pitf9 on 22.12.2018.
//

#ifndef PRI_PROJECT_3_STACK_H
#define PRI_PROJECT_3_STACK_H

#include "utils.h"

typedef struct Stack Stack;
struct Stack{
    uint id;
    char rumor[MAX_STRING];
    Stack *next;
};

#endif //PRI_PROJECT_3_STACK_H
