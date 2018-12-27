//
// Created by pitf9 on 22.12.2018.
//

#include "transmitter.h"

Transmitter* createTransmitter(Transmitter* head){
    Transmitter* new = malloc(sizeof(Transmitter));
    new->id = countTransmitters(head)+1;
    //no rumors yet
    new->rumorCount = 0;
    new->prev = NULL;
    new->next = head;

    if(head){
        head->prev = new;
    }

    return new;
}

//returns *head
Transmitter* initTransmitters(int numberOfTransmitters){
    Transmitter* cur = NULL;
    for(int i=0 ; i<numberOfTransmitters ; ++i){
        cur = createTransmitter(cur);
    }

    return cur;
}

uint countTransmitters(Transmitter* head){
    uint count = 0;
    while(head){
        ++count;
        head = head->next;
    }

    return count;
}

void freeTransmitters(Transmitter* head){
    Transmitter* prev = NULL;
    while(head){
        prev = head;
        head = head->next;
        free(prev);
    }
}