//
// Created by pitf9 on 22.12.2018.
//

#include "fileIO.h"

bool transmitFromFile(char* filename, Transmitter* head){
    if(!head || !filename || strIsEmpty(filename)){
        return false;
    }

    FILE* infile = fopen(filename, "rb");
    if(!infile){
        printf("Nie mozna otworzyc pliku: %s\n", filename);
        return false;
    }

    char line[MAX_STRING];

    while(fgets(line, MAX_STRING, infile)){
        uint rumorId = newRumorId(head);
        transmitRumor(line, rumorId, head);
    }
    fclose(infile);

    return true;
}

bool saveData(Transmitter* head){
    FILE* outfile = fopen("data.bin", "wb");
    if(!outfile){
        printf("Nie udalo sie zapisac stanu programu.\n");
        return false;
    }

    Transmitter* current = head;
    while(current){
        fwrite(current, sizeof(Transmitter), 1, outfile);
        Stack* curStack = current->stackHead;
        while(curStack){
            fwrite(curStack, sizeof(Stack), 1, outfile);
            curStack = curStack->next;
        }
        current = current->next;
    }
    fclose(outfile);

    return true;
}

//returns *head
Transmitter* loadData(void){
    FILE* infile = fopen("data.bin", "rb");
    if(!infile){
        printf("Nie udalo sie zapisac stanu programu.\n");
        return NULL;
    }

    Transmitter* current = safeMalloc(sizeof(Transmitter));
    fread(current, sizeof(Transmitter), 1, infile);
    if(!current){
        return NULL;
    }
    Transmitter* head = current;
    while(current->next){
        Transmitter* next = safeMalloc(sizeof(Transmitter));
        fread(next, sizeof(Transmitter), 1, infile);
        current->next = next;
        next->prev = current;

        //stack
        if(current->stackHead){
            Stack* curStack = safeMalloc(sizeof(Stack));
            fread(curStack, sizeof(Stack), 1, infile);
            current->stackHead = curStack;
            while(curStack->next){
                Stack* nextStack = safeMalloc(sizeof(Stack));
                fread(nextStack, sizeof(Stack), 1, infile);
                curStack->next = nextStack;
                //go to the next stack element
                curStack = curStack->next;
            }
        }

        current = current->next;
    }
    fclose(infile);

    return head;
}

bool writeToFile(char* text){
    FILE* ptr = fopen("data.bin", "wb");
    if(!ptr){
        printf("Nie udalo sie zapisac.\n");
        return false;
    }

    fwrite(text, sizeof(text), 1, ptr);
    fclose(ptr);

    return true;
}

bool rewriteToBin(void){
    FILE* readPtr = fopen("default.txt", "r");
    FILE* writePtr = fopen("default.bin", "wb");
    if(!readPtr || !writePtr){
        puts("Blad");
        return false;
    }

    for(int i=0 ; i<93 ; i++) {
        char line[MAX_STRING];
        fgets(line, MAX_STRING, readPtr);
        fwrite(line, strlen(line), 1, writePtr);
    }
    fclose(readPtr);
    fclose(writePtr);

    return true;
}