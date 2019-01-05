//
// Created by pitf9 on 22.12.2018.
//

#ifndef PRI_PROJECT_3_FILEINPUT_H
#define PRI_PROJECT_3_FILEINPUT_H

#include "transmitter.h"

bool transmitFromFile(char* filename, Transmitter* head);

bool saveData(Transmitter* head);

Transmitter* loadData(void);

bool writeToFile(char *text);

bool rewriteToBin(void);

#endif //PRI_PROJECT_3_FILEINPUT_H
