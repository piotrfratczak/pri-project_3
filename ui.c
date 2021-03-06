/*
 * PRI Project n3
 * Rumor Transmitter
 *
 * Created by Piotr Fratczak on 22.12.2018.
 * Warsaw University of Technology
 */

#include "ui.h"

bool handleArgs(int argc, char** args){
    setGeneratorSeed();
    Transmitter* head;

    if(1 == argc){
        head = initTransmitters(DEFAULT_TRANSMITTERS);
        if(!transmitFromFile("default.bin", head)){
            return false;
        }
    }else if(2 == argc){

        if(0 == strcmp(args[1], "start")){
            head = initTransmitters(DEFAULT_TRANSMITTERS);
            if(!transmitFromFile("default.bin", head)){
                return false;
            }
        }else if(0 == strcmp(args[1], "resume")){
            head = loadData();
        }else{
            return false;
        }

    }else if(3 == argc){

        if(stringIsInt(args[2])){
            //file + number
            if(strToInt(args[2]) > 30){
                return false;
            }
            head = initTransmitters(strToInt(args[2]));
            if(!transmitFromFile(args[1], head)){
                return false;
            }
        }else if(0 == strcmp(args[2], "resume")){
            //file + resume
            head = loadData();
            if(!transmitFromFile(args[1], head)){
                return false;
            }
        }else{
            return false;
        }

    }else if(4 == argc && stringIsInt(args[3])){

        if(strToInt(args[3]) > 30){
            return false;
        }

        if(0 == strcmp(args[2], "start")){
            head = initTransmitters(strToInt(args[3]));
            if(!transmitFromFile(args[1], head)){
                return false;
            }
        }else if(0 == strcmp(args[2], "resume")){
            head = loadData();
            int desiredCount = strToInt(args[3]);
            //delete if too many
            while(desiredCount < countTransmitters(head)){
                head = delTransmitter(head);
            }
            //add if too few
            while(desiredCount > countTransmitters(head)){
                head = createTransmitter(head);
            }

            if(!transmitFromFile(args[1], head)){
                return false;
            }
        }else{
            return false;
        }

    }else{
        return false;
    }

    clearScreen();
    while(displayMainMenu(&head)){}
    saveData(head);
    freeAll(head);
    return true;
}

void clearScreen(void){
    system(CONSOLE_CLEAR_CMD);
}

void showTransmitter(Transmitter *transmitter){
    if(!transmitter){
        return;
    }

    printf("Przekaznik nr %d\n", transmitter->id);
    Stack* currentRumor = transmitter->stackHead;
    if(!currentRumor){
        printf("Brak plotek\n\n");
    }else{
        printf("Plotki:\n");
    }
    while(currentRumor){
        printf("%d. nr:%d %s\n", currentRumor->position, currentRumor->id, currentRumor->rumor);
        currentRumor = currentRumor->next;
    }
}

void showStatus(Transmitter* head){
    Transmitter* current = head;
    clearScreen();
    printf("Liczba przekaznikow: %d\n\n", countTransmitters(current));
    while(current){
        printf("---------- Pozycja %d. ----------\n", current->position);
        showTransmitter(current);

        current = current->next;
    }
}

void showResult(Transmitter* head){
    clearScreen();
    if(!head){
        printf("Brak przekaznikow do wyswietlania.\n\n");
        return;
    }

    Transmitter* transmitter = findTransmitterById(findTranIdByPosition(1, head), head);
    Stack* currentRumor = transmitter->stackHead;
    if(!currentRumor){
        printf("Brak plotek\n\n");
    }else{
        printf("Plotki:\n");
    }
    while(currentRumor){
        printf("%d. %s\n", currentRumor->position, currentRumor->rumor);
        currentRumor = currentRumor->next;
    }
}

void displayTransmitter(Transmitter* head){
    clearScreen();
    if(!head){
        printf("Brak przekaznikow do wyswietlania.\n\n");
        return;
    }

    showTransmitter(getTransmitterByPosition(head));
}

void transmitScreen(Transmitter* head){
    clearScreen();
    if(!head){
        printf("Brak przekaznikow. Nie mozna przekazac plotki.\n\n");
        return;
    }

    printf("Tresc plotki do przekazania: ");
    transmitFromUser(head);
}

void delTransmitterScreen(Transmitter** head){
    clearScreen();
    Transmitter* transmitter = getTransmitterByPosition(*head);
    uint id = transmitter->id;
    *head = delTransmitter(transmitter);
    clearScreen();
    printf("\nUsunieto przekaznik nr %d\n\n", id);
}

void addTransmitterScreen(Transmitter** head){
    clearScreen();

    int choice;
    if(*head){
        printf("0 - dodaj na koniec\n"
               "1 - dodaj w srodku kolejki\n");

        choice = getChoice(0,1);
    }else{
        choice = 0;
    }

    switch(choice){
        case 0:
            clearScreen();
            *head = createTransmitter(*head);
            break;
        case 1:
            clearScreen();
            uint position = (uint)getChoice(1, countTransmitters(*head));
            uint id = findTranIdByPosition(position, *head);
            addTransmitter(id, *head);
            break;
        default:
            printf("Nie ma takiego wyboru");
            addTransmitterScreen(head);
    }
}

void moveTransmitterScreen(Transmitter** head){
    clearScreen();
    Transmitter* transmitter = getTransmitterByPosition(*head);
    printf("Wybierz nowa pozycje: ");
    uint id = (uint)getChoice(1, countTransmitters(*head));
    *head = moveTransmitter(transmitter, id);
}

void editOddsScreen(Transmitter** head){
    clearScreen();
    Transmitter* transmitter = getTransmitterByPosition(*head);

    printf("0 - zmien wartosc q\n"
           "1 - zmien wartosc p\n");

    int choice = getChoice(0,1);
    switch(choice){
        case 0:
            clearScreen();
            transmitter->q = getFloat(0.0, transmitter->p);
            break;
        case 1:
            clearScreen();
            transmitter->p = getFloat(transmitter->q, 0.5);
            break;
        default:
            printf("Nie ma takiego wyboru.\n");
            editOddsScreen(head);
            break;
    }
}

void delRumorScreen(Transmitter* head){
    clearScreen();
    Transmitter* transmitter = getTransmitterByPosition(head);

    if(!transmitter->stackHead){
        printf("Brak plotek do usuniecia.\n"
               "0 - Anuluj\n"
               "1 - Usun plotke z innego przekaznika.");
        int choice = getChoice(0,1);
        switch(choice){
            case 0:
                return;
            case 1:
                delRumorScreen(head);
                return;
            default:
                return;
        }
    }

    Stack* obsolete = getStackByPosition(transmitter->stackHead);
    transmitter->stackHead = delRumor(obsolete, transmitter->stackHead);
}

void addRumorScreen(Transmitter* head){
    clearScreen();
    Transmitter* transmitter = getTransmitterByPosition(head);
    printf("Wprowadz tresc plotki:\n");
    char* rumor = safeMalloc(MAX_STRING*sizeof(char));
    getLine(&rumor);
    clearScreen();

    int choice;
    if(transmitter->stackHead){
        printf("0 - dodaj na koniec\n"
               "1 - dodaj w srodku kolejki\n");
        choice = getChoice(0,1);
    }else{
        choice = 0;
    }

    switch(choice){
        case 0:
            clearScreen();
            addRumorOnTop(rumor, transmitter);
            break;
        case 1:
            clearScreen();
            printf("Podaj pozycje nowej plotki: ");
            uint position = (uint)getChoice(1, stackSize(transmitter->stackHead));
            uint id = findStackIdByPosition(position, transmitter->stackHead);
            addRumorOnGivenPosition(rumor, id, transmitter);
            break;
        default:
            printf("Nie ma takiego wyboru");
            addRumorScreen(head);
    }
}

void moveRumorScreen(Transmitter* head){
    clearScreen();
    Transmitter* transmitter = getTransmitterByPosition(head);

    if(!transmitter->stackHead){
        printf("Brak plotek do przeniesienia.\n"
               "0 - Anuluj\n"
               "1 - Przenies plotke z innego przekaznika.");
        int choice = getChoice(0,1);
        switch(choice){
            case 0:
                return;
            case 1:
                moveRumorScreen(head);
                return;
            default:
                return;
        }
    }

    Stack* stack = getStackByPosition(transmitter->stackHead);
    printf("0 - przenies w obrebie przekaznika\n"
           "1 - przenies do innego przekaznika\n\n");
    int choice = getChoice(0,1);
    switch(choice){
        case 0:
            clearScreen();
            printf("Podaj nowa pozycje plotki: ");
            uint position = (uint)getChoice(1, stackSize(transmitter->stackHead));
            uint id = findStackIdByPosition(position, transmitter->stackHead);
            transmitter->stackHead = moveRumor(stack, transmitter->stackHead, id);
            break;
        case 1:
            clearScreen();
            Transmitter* newTransmitter = getTransmitterByPosition(head);
            if(!newTransmitter->stackHead){
                addRumorOnTop(fetchHeadRumor(transmitter), newTransmitter);
                break;
            }

            printf("Podaj nowa pozycje plotki: ");
            uint newPosition = (uint)getChoice(1, stackSize(newTransmitter->stackHead));
            uint idNewPosition = findStackIdByPosition(newPosition, newTransmitter->stackHead);
            //moves rumor to the top
            transmitter->stackHead = moveRumor(stack, transmitter->stackHead, transmitter->stackHead->id);
            addRumorOnGivenPosition(fetchHeadRumor(transmitter), idNewPosition, newTransmitter);
            break;
        default:
            printf("Nie ma takiego wyboru");
            moveRumorScreen(head);
    }
}

void editRumorScreen(Transmitter* head){
    clearScreen();
    Transmitter* transmitter = getTransmitterByPosition(head);

    if(!transmitter->stackHead){
        printf("Brak plotek do edytowania.\n"
               "0 - Anuluj\n"
               "1 - Edytuj plotke z innego przekaznika.");
        int choice = getChoice(0,1);
        switch(choice){
            case 0:
                return;
            case 1:
                editRumorScreen(head);
                return;
            default:
                return;
        }
    }

    Stack* stack = getStackByPosition(transmitter->stackHead);
    printf("Wprowadz nowa tresc plotki:\n");
    editRumor(stack);
}

bool displayMainMenu(Transmitter** head){
    bool isRunning = true;

    printf("MENU GLOWNE\n"
           "____________________________________\n"
           "0 - Zakoncz program\n"
           "1 - Pokaz rezultat\n"
           "2 - Przekaz plotke do kolejki\n"
           "3 - Edytuj struktury\n");

    printf("____________________________________\n");


    switch(getChoice(0,3)){
        case 0:
            isRunning = false;
            clearScreen();
            break;
        case 1:
            showResult(*head);
            break;
        case 2:
            transmitScreen(*head);
            break;
        case 3:
            displayEditStructuresMenu(head);
            break;
        default:
            clearScreen();
            printf("Nie ma takiego wyboru, sprobuj jeszcze raz\n");
            break;
    }

    return isRunning;
}

void displayEditStructuresMenu(Transmitter** head){
    clearScreen();

    printf("MENU EDYCJI STRUKTUR\n"
           "____________________________________\n"
           "0 - Menu glowne\n"
           "1 - Pokaz wszystkie przekazniki\n"
           "2 - Pokaz wybrany przekaznik\n");
    if(*head){
        printf("3 - Edytuj przekazniki\n");
    }else{
        printf("3 - Dodaj przekaznik\n");
    }
    printf("____________________________________\n");


    switch(getChoice(0,3)){
        case 0:
            clearScreen();
            break;
        case 1:
            showStatus(*head);
            break;
        case 2:
            displayTransmitter(*head);
            break;
        case 3:
            clearScreen();
            if(*head){
                displayEditTransmittersMenu(head);
            }else{
                addTransmitterScreen(head);
            }

            break;
        default:
            clearScreen();
            printf("Nie ma takiego wyboru, sprobuj jeszcze raz\n");
            break;
    }
}

void displayEditTransmittersMenu(Transmitter** head){
    clearScreen();

    printf("MENU EDYCJI PRZEKAZNIKOW\n"
           "____________________________________\n"
           "0 - Menu Glowne\n"
           "1 - Usun przekaznik\n"
           "2 - Dodaj przekaznik\n"
           "3 - Przenies przekaznik\n"
           "4 - Zmien prawdopodobienstwa\n"
           "5 - Edytuj plotki\n"
           "____________________________________\n");


    switch(getChoice(0,5)){
        case 0:
            clearScreen();
            break;
        case 1:
            delTransmitterScreen(head);
            break;
        case 2:
            addTransmitterScreen(head);
            break;
        case 3:
            moveTransmitterScreen(head);
            break;
        case 4:
            editOddsScreen(head);
            break;
        case 5:
            clearScreen();
            displayEditRumorsMenu(*head);
            break;
        default:
            printf("Nie ma takiego wyboru, sprobuj jeszcze raz\n");
            displayEditTransmittersMenu(head);
            break;
    }
}

void displayEditRumorsMenu(Transmitter* head){
    clearScreen();
    printf("MENU EDYCJI PLOTEK\n"
           "____________________________________\n"
           "0 - Menu Glowne\n"
           "1 - Usun plotke\n"
           "2 - Dodaj plotke\n"
           "3 - Przenies plotke\n"
           "4 - Edytuj plotke\n"
           "____________________________________\n");

    switch(getChoice(0,4)){
        case 0:
            clearScreen();
            break;
        case 1:
            delRumorScreen(head);
            break;
        case 2:
            addRumorScreen(head);
            break;
        case 3:
            moveRumorScreen(head);
            break;
        case 4:
            editRumorScreen(head);
            break;
        default:
            printf("Nie ma takiego wyboru, sprobuj jeszcze raz\n");
            displayEditRumorsMenu(head);
            break;
    }
}

bool transmitFromUser(Transmitter* receiver){
    char* rumor = safeMalloc(MAX_STRING*sizeof(char));
    if(!getLine(&rumor)){
        return false;
    }

    uint rumorId = newRumorId(findHead(receiver));
    transmitRumor(rumor, rumorId, receiver);

    return true;
}

bool editRumor(Stack* rumorEl){
    char* newRumor = safeMalloc(MAX_STRING*sizeof(char));
    if(!getLine(&newRumor) || !strncpy(rumorEl->rumor, newRumor, MAX_STRING)){

        return false;
    }
    free(newRumor);

    return true;
}

float getFloat(float min, float max){
    float input = 0;

    while(input <= min || input >= max){
        printf("Podaj wartosc od %.3f do %.3f: ", min, max);
        scanf("%4f", &input);
    }
    clearInputBuffer();

    return input;
}

int getChoice(int minChoice, int maxChoice){
    int choice;
    while(1 != scanf("%d", &choice) || choice < minChoice || choice > maxChoice){
        clearInputBuffer();
        printf("Nie ma takiego wyboru\n"
               "Prosze podac cyfre %d - %d\n", minChoice, maxChoice);
    }
    return choice;
}

Transmitter* getTransmitterByPosition(Transmitter *head){
    uint maxPosition = countTransmitters(head);
    uint position;
    if(maxPosition != 1){
        printf("Podaj pozycje przekaznika(1 - %d): ",maxPosition);
        position = (uint)getChoice(1, maxPosition);
    }else{
        position = 1;
    }

    Transmitter* current = head;
    while(current){
        if(current->position == position){
            return current;
        }
        current = current->next;
    }

    //if there is no transmitter on given position
    return NULL;
}

Stack* getStackByPosition(Stack* stackHead){
    uint maxPosition = stackSize(stackHead);
    printf("Podaj pozycje plotki(1 - %d): ", maxPosition);
    uint position = (uint)getChoice(1, maxPosition);

    Stack* current = stackHead;
    while(current){
        if(current->position == position){
            return current;
        }
        current = current->next;
    }

    //if there is no rumor on given position
    return NULL;
}
