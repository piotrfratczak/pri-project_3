#include "ui.h"

int main(int argc, char** argv){

    if(argc <=4){
        if(handleArgs(argc, argv)){
            return 0;
        }else{
            printf("Podano niepoprawne argumenty uruchomienia.");
            return 1;
        }
    }else{
        printf("Podano zbyt wiele parametrow uruchomienia.");
        return 1;
    }
}