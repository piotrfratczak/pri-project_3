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

    int separator = 1;
    int terminator = -1;
    Transmitter* current = head;
    while(current){
        fwrite(&separator, sizeof(int), 1, outfile);
        fwrite(current, sizeof(Transmitter), 1, outfile);
        //stack
        Stack* curStack = current->stackHead;
        while(curStack){
            fwrite(&separator, sizeof(int), 1, outfile);
            fwrite(curStack, sizeof(Stack), 1,outfile);

            curStack = curStack->next;
        }
        fwrite(&terminator, sizeof(int), 1, outfile);

        current = current->next;
    }
    fwrite(&terminator, sizeof(int), 1, outfile);
    fclose(outfile);

    return true;
}

//returns *head
Transmitter* loadData(void){
    FILE* infile = fopen("data.bin", "rb");
    if(!infile){
        printf("Nie udalo sie wczytac stanu programu.\n");
        return NULL;
    }

    int buf;
    Transmitter* current = safeMalloc(sizeof(Transmitter));
    Transmitter* prev = NULL;
    fread(&buf, sizeof(int), 1, infile);
    if(1 != buf){
        return NULL;
    }
    while(1 == buf){
        fread(current, sizeof(Transmitter), 1, infile);
        current->prev = prev;

        //stack
        current->stackHead = safeMalloc(sizeof(Stack));
        Stack* curStack = current->stackHead;
        fread(&buf, sizeof(int), 1, infile);
        while(1 == buf){
            fread(curStack, sizeof(Stack), 1, infile);
            fread(&buf, sizeof(int), 1, infile);
            if(1 == buf){
                curStack->next = safeMalloc(sizeof(Stack));
                curStack = curStack->next;
            }else{
                curStack->next = NULL;
            }
        }

current->next = NULL;
        current->next = safeMalloc(sizeof(Transmitter));
        prev = current;
        current = current->next;
        fread(&buf, sizeof(int), 1, infile);
    }
    if(prev){
        prev->next = NULL;
    }
    fclose(infile);

    return findHead(prev);
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