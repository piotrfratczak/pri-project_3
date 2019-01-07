/*
 * PRI Project n3
 * Rumor Transmitter
 *
 * Created by Piotr Fratczak on 22.12.2018.
 * Warsaw University of Technology
 */

#include "ui.h"

int main(int argc, char** argv){

    if(argc <=4){
        if(handleArgs(argc, argv)){
            return 0;
        }else{
            puts("Podano niepoprawne argumenty uruchomienia.");
            return 1;
        }
    }else{
        puts("Podano zbyt wiele parametrow uruchomienia.");
        return 1;
    }
}