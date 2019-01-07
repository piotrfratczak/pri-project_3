/*
 * PRI Project n3
 * Rumor Transmitter
 *
 * Created by Piotr Fratczak on 22.12.2018.
 * Warsaw University of Technology
 */

#include "utils.h"

void setGeneratorSeed(void){
    srand(time(NULL));
}

bool isTransmitted(double odds){
    double random = (double)rand() / RAND_MAX;

    return random <= odds;
}

void* safeMalloc(size_t size){
    void* memory = malloc(size);

    if(!memory){
        fputs("Failed to allocate memory.", stderr);
        exit(EXIT_FAILURE);
    }

    return memory;
}

bool getLine(char** string){
    clearInputBuffer();
    if((*string = fgets(*string, MAX_STRING, stdin))){
        clearInputBuffer();
        return true;
    }else{
        clearInputBuffer();
        return false;
    }
}

bool strIsEmpty(char* string){
    if(strcmp(string, "") == 0){
        return true;
    }else{
        return false;
    }
}

void clearInputBuffer(void){
    char c;
    while ((c = (char)getchar()) != '\n' && c != EOF);
}

int strToInt(char* number){
    int integer = 0;
    for(int i=0 ; i<strlen(number) ; ++i){
        integer = integer*10 + number[i] - '0';
    }

    return integer;
}

bool stringIsInt(char* string){
    for(int i=0 ; i<strlen(string) ; ++i){
        if(string[i] > '9' || string[i] < 0){
            return false;
        }
    }

    return true;
}
