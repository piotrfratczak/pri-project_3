//
// Created by pitf9 on 22.12.2018.
//

#include "transmitter.h"

//returns new *head
Transmitter* createTransmitter(Transmitter* head){
    Transmitter* new = malloc(sizeof(Transmitter));
    new->id = countTransmitters(head)+1;
    //no rumors yet
    new->stackHead = NULL;
    new->prev = NULL;
    new->next = head;

    if(head){
        head->prev = new;
    }

    return new;
}

//returns *head
Transmitter* initTransmitters(int numberOfTransmitters){
    Transmitter* current = NULL;
    for(int i=0 ; i<numberOfTransmitters ; ++i){
        current = createTransmitter(current);
    }

    return current;
}

char* fetchHeadRumor(Transmitter* transmitter){
    char* rumor = malloc(MAX_STRING* sizeof(char));
    strcpy(rumor, getRumor(transmitter->stackHead));
    transmitter->stackHead = removeStackHead(transmitter->stackHead);

    return rumor;
}

void transmitRumor(char* rumor, Transmitter* receiver){
    //return if receiver is NULL
    if(!receiver){
        return;
    }

    //run the test only if there is next Transmitter
    // with a stack of rumors
    if(receiver->next && receiver->stackHead){
        while(isTransmitted(0.27)){
            transmitRumor(fetchHeadRumor(receiver), receiver->next);
        }
    }

    //run the test only if there is next Transmitter
    if(receiver->next && isTransmitted(0.42)){
        transmitRumor(rumor, receiver->next);
    }else{
        //add rumor to the stack
        receiver->stackHead = addRumor(rumor, receiver->stackHead);
    }
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

        freeStack(prev->stackHead);
        free(prev);
    }
}