//
// Created by pitf9 on 22.12.2018.
//

#include "fileIO.h"

void writeToFile(char* text){
    FILE* ptr = fopen("d.bin", "ab");
    if(!ptr){
        //TODO handle error
    }

    fwrite(text, sizeof(text), 1, ptr);

    fclose(ptr);
}

void readFromText(void){
    int buf;
    FILE* pointer = fopen("default.txt", "r");
    FILE* ptr = fopen("default.bin", "wb");

    for(int i=0;i<93;i++) {
        char str[10000] = "";
        int i = 0;

        buf = fgetc(pointer);
        while (buf != '\n') {
            str[i] = (char) buf;
            i++;
            buf = fgetc(pointer);
        }
        str[i] = '\n';
        i++;
        fwrite(str, i*sizeof(char), 1, ptr);
    }
    fclose(pointer);
    fclose(ptr);
}