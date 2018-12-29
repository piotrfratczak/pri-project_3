//
// Created by pitf9 on 22.12.2018.
//

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
