//
// Created by pitf9 on 22.12.2018.
//

#include "stack.h"

Stack* addRumor(char* rumor, Stack* head){
    Stack* new = (Stack*)malloc(sizeof(Stack));
    new->id = countRumors(head)+1;
    new->next = head;
    strcpy(new->rumor, rumor);

    return new;
}

//returns new *head
Stack* removeStackHead(Stack* head){
    Stack* newHead = head->next;
    free(head);

    return newHead;
}

char* getRumor(Stack* rumorPtr){
    return rumorPtr->rumor;
}

uint countRumors(Stack* head){
    uint count = 0;
    while(head){
        ++count;
        head = head->next;
    }

    return count;
}

void freeStack(Stack* head){
    Stack* prev = NULL;
    while(head){
        prev = head;
        head = head->next;
        free(prev);
    }
}