//
// Created by pitf9 on 22.12.2018.
//

#ifndef PRI_PROJECT_3_UI_H
#define PRI_PROJECT_3_UI_H

#ifdef _WIN32
#define CONSOLE_CLEAR_CMD "cls"
#elif __linux__
#define CONSOLE_CLEAR_CMD "clear"
#else
#define CONSOLE_CLEAR_CMD ""
#endif

#include "transmitter.h"

void clearScreen(void);

//TODO implement this
void displayStatus(Transmitter* head);

#endif //PRI_PROJECT_3_UI_H
