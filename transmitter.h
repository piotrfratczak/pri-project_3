/*
 * PRI Project n3
 * Rumor Transmitter
 *
 * Created by Piotr Fratczak on 22.12.2018.
 * Warsaw University of Technology
 */

#ifndef PRI_PROJECT_3_TRANSMITTER_H
#define PRI_PROJECT_3_TRANSMITTER_H

#include "stack.h"

typedef struct Transmitter Transmitter;
struct Transmitter{
    uint id;
    uint position;
    float q;
    float p;
    Stack *stackHead;
    Transmitter *next, *prev;
};

Transmitter* createTransmitter(Transmitter* head);

Transmitter* delTransmitter(Transmitter* transmitter);

Transmitter* moveTransmitter(Transmitter* mover, uint newLocationId);

Transmitter* addTransmitter(uint locationId, Transmitter* head);

void addRumorOnTop(char* rumor, Transmitter* transmitter);

void addRumorOnGivenPosition(char* rumor, uint stackId, Transmitter* transmitter);

Transmitter* initTransmitters(int numberOfTransmitters);

char* fetchHeadRumor(Transmitter* transmitter);

void transmitRumor(char* rumor, uint rumorId, Transmitter* receiver);

uint countTransmitters(Transmitter* head);

uint transmitterPosition(Transmitter* transmitter);

void updatePositions(Transmitter* head);

uint newTransmitterId(Transmitter* head);

uint newRumorId(Transmitter* head);

Transmitter* findTransmitterById(uint id, Transmitter* head);

Transmitter* findHead(Transmitter* any);

uint findTranIdByPosition(uint position, Transmitter *head);

void freeAll(Transmitter* head);

#endif //PRI_PROJECT_3_TRANSMITTER_H
