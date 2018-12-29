//
// Created by pitf9 on 22.12.2018.
//

#include "ui.h"

void clearScreen(void){
    system(CONSOLE_CLEAR_CMD);
}

void displayStatus(Transmitter* head){
    Transmitter* current = head;
    //clearScreen();
    printf("Liczba przekaznikow: %d\n", countTransmitters(current));
    while(current){
        printf("-----------------------\n");
        printf("Przekaznik nr: %d\n", current->id);
        printf("Plotki:\n");
        Stack* currentStack = current->stackHead;
        while(currentStack){
            printf("%s\n", currentStack->rumor);
            currentStack = currentStack->next;
        }
        current = current->next;
    }
}

//TODO implement showResult()
