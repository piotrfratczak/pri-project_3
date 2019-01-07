/*
 * PRI Project n3
 * Rumor Transmitter
 *
 * Created by Piotr Fratczak on 22.12.2018.
 * Warsaw University of Technology
 */

#ifndef PRI_PROJECT_3_FILEINPUT_H
#define PRI_PROJECT_3_FILEINPUT_H

#include "transmitter.h"

bool transmitFromFile(char* filename, Transmitter* head);

bool saveData(Transmitter* head);

Transmitter* loadData(void);

bool rewriteToBin(void);

#endif //PRI_PROJECT_3_FILEINPUT_H
