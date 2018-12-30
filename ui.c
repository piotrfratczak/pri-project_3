//
// Created by pitf9 on 22.12.2018.
//

#include "ui.h"

bool handleArgs(int argc, char** args){
    if(argc <= 3) {
        setGeneratorSeed();

        Transmitter* head = initTransmitters(DEFAULT_TRANSMITTERS);
        transmitFromFile("default.bin", head);
        //displayStatus(head);

        displayTransmitter(head);

        displayTransmitter(head);

        freeAll(head);

        return true;
    }else{
        printf("Podano zbyt wiele parametrow");
        return false;
    }
}

void clearScreen(void){
    system(CONSOLE_CLEAR_CMD);
}

void displayTransmitter(Transmitter* transmitter){
    if(!transmitter){
        return;
    }

    printf("Przekaznik nr %d\n", transmitter->id);
    Stack* currentRumor = transmitter->stackHead;
    if(!currentRumor){
        printf("Brak plotek\n");
    }else{
        printf("Plotki:\n");
    }
    while(currentRumor){
        printf("%d. %s\n",currentRumor->id , currentRumor->rumor);
        currentRumor = currentRumor->next;
    }
}

//TODO polish displayStatus()
void displayStatus(Transmitter* head){
    Transmitter* current = head;
    //clearScreen();
    printf("Liczba przekaznikow: %d\n", countTransmitters(current));
    while(current){
        printf("---------- Pozycja %d. ----------\n", current->position);
        displayTransmitter(current);

        current = current->next;
    }
}

bool transmitFromUser(Transmitter* receiver){
    char* rumor = safeMalloc(MAX_STRING*sizeof(char));
    if(!getLine(&rumor)){
        return false;
    }

    transmitRumor(rumor, receiver);
    return true;
}

bool editRumor(Stack* rumorEl){
    char* newRumor = safeMalloc(MAX_STRING*sizeof(char));
    if(!getLine(&newRumor) ||
            !strncpy(rumorEl->rumor, newRumor, MAX_STRING)){
        return false;
    }
    free(newRumor);
    return true;
}

//TODO implement showResult()
