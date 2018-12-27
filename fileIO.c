//
// Created by pitf9 on 22.12.2018.
//

#include "fileIO.h"

char* readLine(void){
    FILE* ptr = fopen("default.bin", "rb");
    if(!ptr){
        //TODO handle error
        return NULL;
    }

    char line[MAX_STRING];
    char* strToReturn = malloc(MAX_STRING*sizeof(char));

    fgets(line, MAX_STRING, ptr);
    strcpy(strToReturn, line);

    return strToReturn;
}

void writeToFile(char* text){
    FILE* ptr = fopen("d.bin", "ab");
    if(!ptr){
        //TODO handle error
    }

    fwrite(text, sizeof(text), 1, ptr);

    fclose(ptr);
}

void rewriteToBin(void){
    FILE* readPtr = fopen("default.txt", "r");
    FILE* writePtr = fopen("default.bin", "wb");

    for(int i=0 ; i<93 ; i++) {
        char line[MAX_STRING];
        fgets(line, MAX_STRING, readPtr);
        fwrite(line, strlen(line), 1, writePtr);
    }
    fclose(readPtr);
    fclose(writePtr);
}