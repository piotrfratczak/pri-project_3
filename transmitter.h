//
// Created by pitf9 on 22.12.2018.
//

#ifndef PRI_PROJECT_3_TRANSMITTER_H
#define PRI_PROJECT_3_TRANSMITTER_H

#include "stack.h"

typedef struct Transmitter Transmitter;
struct Transmitter{
    uint id;
    uint rumorCount;
    Stack rumors;
    Transmitter *next, *prev;
};

Transmitter* createTransmitter(Transmitter* head);

Transmitter* initTransmitters(int numberOfTransmitters);

uint countTransmitters(Transmitter* head);

void freeTransmitters(Transmitter* head);

#endif //PRI_PROJECT_3_TRANSMITTER_H
