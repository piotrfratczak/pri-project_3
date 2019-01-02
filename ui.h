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

void showTransmitter(Transmitter* transmitter);

void showStatus(Transmitter* head);

void displayTransmitter(Transmitter* head);

void transmitScreen(Transmitter* head);

void delTransmitterScreen(Transmitter** head);

void addTransmitterScreen(Transmitter** head);

void moveTransmitterScreen(Transmitter** head);

void delRumorScreen(Transmitter* head);

void addRumorScreen(Transmitter* head);

void moveRumorScreen(Transmitter* head);

void editRumorScreen(Transmitter* head);

bool displayMainMenu(Transmitter** head);

void displayEditTransmittersMenu(Transmitter** head);

void displayEditRumorsMenu(Transmitter* head);

bool transmitFromUser(Transmitter* receiver);

bool editRumor(Stack* rumorEl);

int getChoice(int minChoice, int maxChoice);

Transmitter* getTransmitterByPosition(Transmitter *head);

Stack* getStackByPosition(Stack* stackHead);

#endif //PRI_PROJECT_3_UI_H
