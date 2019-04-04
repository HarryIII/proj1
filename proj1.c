#include <stdio.h>
//rotation cipher test
char encryption(char *message);

int main() {
    char message[13] = {'H', 'E', 'L', 'L', 'O', ' ', 'W', 'O', 'R', 'L', 'D', '.', '\0'};
    message[13] = encryption(message);
    printf("Encryption: %s", message);
}

char encryption(char *message) {
    int shift = 6; //Initialising shift amount to 6 places.
    int index; //Initialising string index to zero (does not need to be initialised, only decalred).
    printf("Message: %s\n", message);
    printf("Rotation key: %d.\n", shift);
    for(index = 0; index < 13; index++) {
        if(message[index] < 65 || message[index] > 90) {    //If the letter is not between A-Z, keep its value
            message[index] = message[index];           
        }
        else if (message[index] + shift > 90) {             //If the new value goes past Z, finish rotation from A
            int difference = 90 - message[index];
            message[index] = 64 + difference;
        }
        else {                                              //Add the shift value to rotate each other letter.
            message[index] = message[index] + shift;
        }

    }
    return *message;
}    