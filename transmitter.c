/*
 * PRI Project n3
 * Rumor Transmitter
 *
 * Created by Piotr Fratczak on 22.12.2018.
 * Warsaw University of Technology
 */

#include "transmitter.h"

//returns new *head
Transmitter* createTransmitter(Transmitter* head){
    Transmitter* new = (Transmitter*)safeMalloc(sizeof(Transmitter));
    new->id = newTransmitterId(head);
    new->position = countTransmitters(head) + 1;
    new->q = Q;
    new->p = P;
    //no rumors yet
    new->stackHead = NULL;
    new->prev = NULL;
    new->next = head;

    if(head){
        head->prev = new;
    }

    return new;
}

//returns *head in case it changes
Transmitter* delTransmitter(Transmitter* transmitter){
    if(!transmitter){
        return NULL;
    }

    Transmitter* head;
    //if transmitter has previous element then it is not the head
    if(transmitter->prev){
        head = findHead(transmitter);
        transmitter->prev->next = transmitter->next;
    }else{
        head = transmitter->next;
    }

    if(transmitter->next){
        transmitter->next->prev = transmitter->prev;
    }

    freeStack(transmitter->stackHead);
    free(transmitter);

    updatePositions(head);

    return head;
}

//returns *head in case it changes
Transmitter* moveTransmitter(Transmitter* mover, uint newLocationId){
    //return NULL if mover or newLocation does not exist
    if(!mover ){
        return NULL;
    }
    //the transmitter on the desired position,
    // that has to be moved to make room for the mover
    Transmitter* moveIt = findTransmitterById(newLocationId, findHead(mover));
    if(!moveIt){
        return NULL;
    }

    if(mover->id == newLocationId){
        return findHead(mover);
    }

    //fix pointers around moved Transmitter
    if(mover->prev){
        mover->prev->next = mover->next;
    }
    if(mover->next){
        mover->next->prev = mover->prev;
    }

    if(mover->position > transmitterPosition(moveIt)){

        mover->next = moveIt->next;
        if(moveIt->next){
            moveIt->next->prev = mover;
        }
        moveIt->next = mover;
        mover->prev = moveIt;

    }else if(mover->position < transmitterPosition(moveIt)){

        mover->prev = moveIt->prev;
        if(moveIt->prev){
            moveIt->prev->next = mover;
        }
        moveIt->prev = mover;
        mover->next = moveIt;
    }

    updatePositions(findHead(mover));

    return findHead(mover);
}

//returns new *head
Transmitter* addTransmitter(uint locationId, Transmitter* head){
    if(!findTransmitterById(locationId, head)){
        return NULL;
    }

    Transmitter* newHead = createTransmitter(head);
    newHead = moveTransmitter(newHead, locationId);

    updatePositions(newHead);

    return newHead;
}

void addRumorOnTop(char* rumor, Transmitter* transmitter){
    uint rumorId = newRumorId(findHead(transmitter));
    transmitter->stackHead = createRumor(rumor, rumorId, transmitter->stackHead);
}

void addRumorOnGivenPosition(char* rumor, uint stackId, Transmitter* transmitter){
    uint rumorId = newRumorId(findHead(transmitter));
    transmitter->stackHead = createRumor(rumor, rumorId, transmitter->stackHead);
    transmitter->stackHead = moveRumor(transmitter->stackHead, transmitter->stackHead, stackId);
    updateRumorPositions(transmitter->stackHead);
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
    char* rumor = safeMalloc(MAX_STRING*sizeof(char));
    strcpy(rumor, getRumor(transmitter->stackHead));
    transmitter->stackHead = removeStackHead(transmitter->stackHead);

    return rumor;
}

void transmitRumor(char* rumor, uint rumorId, Transmitter* receiver){
    //return if receiver or rumor is NULL or rumor is empty
    if(!receiver || !rumor || strIsEmpty(rumor)){
        return;
    }

    //run the test only if there is next Transmitter
    if(receiver->next){
        while(receiver->stackHead && isTransmitted(receiver->q)){
            uint fetchedRumorId = receiver->stackHead->id;
            transmitRumor(fetchHeadRumor(receiver), fetchedRumorId, receiver->next);
        }
    }

    //run the test only if there is next Transmitter
    if(receiver->next && isTransmitted(receiver->p)){
        transmitRumor(rumor, rumorId, receiver->next);
    }else{
        //add rumor to the stack
        receiver->stackHead = createRumor(rumor, rumorId, receiver->stackHead);
    }
}

uint countTransmitters(Transmitter* head){
    uint count = 0;
    Transmitter* current = head;
    while(current){
        ++count;
        current = current->next;
    }

    return count;
}

uint transmitterPosition(Transmitter* transmitter){
    Transmitter* current = findHead(transmitter);
    uint position = countTransmitters(current);
    while(current != transmitter){
        current = current->next;
        --position;
    }

    return position;
}

void updatePositions(Transmitter* head){
    uint position = countTransmitters(head);
    Transmitter* current = head;
    while(current){
        current->position = position;
        current = current->next;
        --position;
    }
}

uint newTransmitterId(Transmitter* head){
    uint newId = 1;
    Transmitter* current = head;
    while(current){
        if(current->id >= newId){
            newId = current->id + 1;
        }
        current = current->next;
    }

    return newId;
}

uint newRumorId(Transmitter* head){
    uint newId = 1;
    Transmitter* current = head;
    while(current){
        Stack* stackHead = current->stackHead;
        while(stackHead){
            if(stackHead->id >= newId){
                newId = stackHead->id + 1;
            }
            stackHead = stackHead->next;
        }
        current = current->next;
    }

    return newId;
}

Transmitter* findTransmitterById(uint id, Transmitter* head){
    //newTransmitterId is always 1 int higher than
    //the highest existing Transmitter id
    if(id >= newTransmitterId(head)){
        return NULL;
    }

    Transmitter* current = head;
    while(current){
        if(current->id == id){
            return current;
        }
        current = current->next;
    }

    //if there is no transmitter with given id
    return NULL;
}

Transmitter* findHead(Transmitter* any){
    Transmitter* head = any;
    while(head->prev){
        head = head->prev;
    }
    return head;
}

uint findTranIdByPosition(uint position, Transmitter *head){
    if(position > countTransmitters(head) || !head){
        return 0;
    }
    Transmitter* current = head;
    while(current->position != position){
        current = current->next;
    }

    return current->id;
}

void freeAll(Transmitter* head){
    Transmitter* prev = NULL;
    while(head){
        prev = head;
        head = head->next;

        freeStack(prev->stackHead);
        free(prev);
    }
}