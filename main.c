#include "ui.h"

//TODO implement args handling
int main(void){
    setGeneratorSeed();

    //displayStatus();

    Transmitter* head = initTransmitters(DEFAULT_TRANSMITTERS);
    char a[9] = "Hello00.";
    for(int i=1 ; i<=20 ; i++){


        a[5] = '0' + (i/10);
        a[6] = '0' + (i%10);
        printf("%d. %s\n", i+1, a);

        transmitRumor(a, head);
        displayStatus(head);

    }

    freeTransmitters(head);

    return 0;
}