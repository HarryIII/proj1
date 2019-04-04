#include <stdio.h>
//rotation cipher test
int main() {
    int shift = 6; //Initialising shift amount to 6 places.
    int index = 0; //Initialising string index to zero (does not need to be initialised, only decalred).
    char message[13] = {'H', 'E', 'L', 'L', 'O', ' ', 'W', 'O', 'R', 'L', 'D', '.', '\0'};
    printf("Message: %s\n", message);
    printf("Rotation key: %d.\n", shift);
    for(index = 0; index < 13; index++) {
        if(message[index] < 65 || message[index] > 90) {
            message[index] = message[index];
        }
        else if (message[index] + shift > 90) {
            int difference = 90 - message[index];
            message[index] = 64 + difference;
        }
        else {
            message[index] = message[index] + shift;
        }

    }
    printf("Encryption: %s", message);
}    