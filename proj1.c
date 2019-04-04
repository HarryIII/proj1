#include <stdio.h>
//rotation cipher test
char encryption(char *message);

int main() {
    int task; //Integer for storing selected task
    printf("Select a task: \n");
    printf("1. Encryption of a message with a rotation cipher given the message text and rotation amount.\n");
    printf("2. Decryption of a message encrypted with a rotation cipher given cipher text and rotation amount.\n");
    printf("3. Encryption of a message with a substitution cipher given message text and alphabet substitution.\n");
    printf("4. Decryption of a message encrypted with a substitution cipher given cipher text and substitutions.\n");
    printf("5. Decryption of a message encrypted with a rotation cipher given cipher text only.\n");
    printf("6. Decryption of a message encrypted with a substitution cipher given cipher text only.\n");
    scanf("%d", &task);
    char message[13] = {'H', 'E', 'L', 'L', 'O', ' ', 'W', 'O', 'R', 'L', 'D', '.', '\0'};
    
    switch(task)
    {
        case 1: message[13] = encryption(message); printf("    Encryption: %s", message);
        case 2: break;
        case 3: break; 
        case 4: break; 
        case 5: break; 
        case 6: break;
    }    
}

char encryption(char *message) {
    int shift = 6; //Initialising shift amount to 6 places.
    int index; //Initialising string index to zero (does not need to be initialised, only decalred).
    printf("Rotation Cipher:\n");
    printf("    Message: %s\n", message);
    printf("    Rotation key: %d.\n", shift);
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
