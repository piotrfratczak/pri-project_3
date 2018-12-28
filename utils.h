//
// Created by pitf9 on 22.12.2018.
//

#ifndef PRI_PROJECT_3_UTILS_H
#define PRI_PROJECT_3_UTILS_H

#include <stdio.h>  //standard library
#include <stdlib.h> //standard library
#include <string.h> //char arrays handling
#include <time.h>   //random numbers generating

#define MAX_STRING 300
#define DEFAULT_TRANSMITTERS 10

typedef unsigned int uint;

//TODO implement safe malloc

void setGeneratorSeed(void);

int isTransmitted(double odds);

#endif //PRI_PROJECT_3_UTILS_H
