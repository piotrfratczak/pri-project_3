//
// Created by pitf9 on 22.12.2018.
//

#include "stack.h"

//returns new *head
Stack* createRumor(char* rumor, uint id, Stack* head){
    Stack* new = (Stack*)safeMalloc(sizeof(Stack));
    new->id = id;
    new->position = stackSize(head) + 1;
    new->next = head;
    strcpy(new->rumor, rumor);

    return new;
}

//returns *head in case it changes
Stack* delRumor(Stack* obsolete, Stack* head){
    if(!obsolete || !head){
        return NULL;
    }
    if(obsolete == head){
        return removeStackHead(obsolete);
    }

    while(head->next != obsolete){
        head = head->next;
    }
    head->next = obsolete->next;
    free(obsolete);
    updateRumorPositions(head);

    return head;
}

//returns new *head
Stack* removeStackHead(Stack* head){
    Stack* newHead = head->next;
    free(head);

    return newHead;
}

//returns *head in case it changes
Stack* moveRumor(Stack* mover, Stack* head, uint newLocationId){
    //return NULL if mover or head is NULL
    if(!mover || !head){
        return NULL;
    }
    //rumor that has to be moved to make room
    Stack* moveIt = findRumorById(newLocationId, head);
    if(!moveIt){
        //if given location does not exist
        return NULL;
    }

    if(mover == moveIt){
        return head;
    }

    if(mover != head){
        Stack* beforeMover = head;
        while(beforeMover->next != mover){
            beforeMover = beforeMover->next;
        }
        beforeMover->next = mover->next;
    }else{
        head = mover->next;
    }

    if(mover->id > newLocationId){
        mover->next = moveIt->next;
        moveIt->next = mover;

    }else{
        if(moveIt != head){
            Stack *beforeMoveIt = head;
            while (beforeMoveIt->next != moveIt) {
                beforeMoveIt = beforeMoveIt->next;
            }
            beforeMoveIt->next = mover;
        }else{
            head = mover;
        }
        mover->next = moveIt;
    }
    updateRumorPositions(head);

    return head;
}


char* getRumor(Stack* rumorPtr){
    return rumorPtr->rumor;
}

uint stackSize(Stack* head){
    uint count = 0;
    Stack* current = head;
    while(current){
        ++count;
        current = current->next;
    }

    return count;
}

void updateRumorPositions(Stack* head){
    uint position = stackSize(head);
    Stack* current = head;
    while(current){
        current->position = position;
        current = current->next;
        --position;
    }
}

Stack* findRumorById(uint id, Stack* head){
    Stack* current = head;
    while(current){
        if(current->id == id){
            break;
        }
        current = current->next;
    }
    return current;
}

uint findStackIdByPosition(uint position, Stack *head){
    if(position > stackSize(head) || !head){
        return 0;
    }
    Stack* current = head;
    while(current->position != position){
        current = current->next;
    }

    return current->id;
}

void freeStack(Stack* head){
    Stack* prev = NULL;
    while(head){
        prev = head;
        head = head->next;
        free(prev);
    }
}