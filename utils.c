//
// Created by pitf9 on 22.12.2018.
//

#include "utils.h"

void setGeneratorSeed(void){
    srand(time(NULL));
}

//TODO make it bool
int isTransmitted(double odds){
    double random = (double)rand() / RAND_MAX;

    return random <= odds;
}
