//
// Created by pitf9 on 22.12.2018.
//

#ifndef PRI_PROJECT_3_TRANSMITTER_H
#define PRI_PROJECT_3_TRANSMITTER_H

#include "stack.h"

typedef struct Transmitter Transmitter;
struct Transmitter{
    uint id;
    Stack rumors;
    Transmitter *next, *prev;
};

#endif //PRI_PROJECT_3_TRANSMITTER_H
