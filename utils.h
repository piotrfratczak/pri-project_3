//
// Created by pitf9 on 22.12.2018.
//

#ifndef PRI_PROJECT_3_UTILS_H
#define PRI_PROJECT_3_UTILS_H

#include <stdio.h>  //standard library
#include <stdlib.h> //standard library
#include <string.h> //char arrays handling
#include <time.h>   //random numbers generating
#include <stdbool.h>//boolean values

#define DEFAULT_TRANSMITTERS 10
#define MAX_STRING 300

typedef unsigned int uint;

void setGeneratorSeed(void);

bool isTransmitted(double odds);

void* safeMalloc(size_t size);

bool getLine(char** string);

bool strIsEmpty(char* string);

void clearInputBuffer(void);

#endif //PRI_PROJECT_3_UTILS_H
