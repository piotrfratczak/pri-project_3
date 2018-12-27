#include "ui.h"

//TODO implement args handling
int main(void){

    //srand(time(NULL));

    //displayStatus();

    Transmitter* head = initTransmitters(DEFAULT_TRANSMITTERS);

    printf("%d", head->id);

    freeTransmitters(head);

    return 0;
}