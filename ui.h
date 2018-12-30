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

#include "fileIO.h"

bool handleArgs(int argc, char** args);

void clearScreen(void);

void displayTransmitter(Transmitter* transmitter);

void displayStatus(Transmitter* head);

bool transmitFromUser(Transmitter* receiver);

bool editRumor(Stack* rumorEl);

#endif //PRI_PROJECT_3_UI_H
