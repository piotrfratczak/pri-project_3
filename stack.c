//
// Created by pitf9 on 22.12.2018.
//

#include "stack.h"

Stack* createStack(char* rumor, Stack* head){
    Stack* new = malloc(sizeof(Stack));
    new->id = countRumors(head)+1;
    new->next = head;

    strcpy(new->rumor, rumor);
    free(rumor);

    return new;
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