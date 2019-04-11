#include <stdio.h>
//rotation cipher test
char RotationEncryption(char *message, char *rotationEncryptionMessage);
char RotationDecryption(char *rotationEncryptionMessage, char *rotationDecryptionMessage);

int main() {
    int task; //Integer for storing selected task
  /*printf("Select a task: \n");
    printf("1. Encryption of a message with a rotation cipher given the message text and rotation amount.\n");
    printf("2. Decryption of a message encrypted with a rotation cipher given cipher text and rotation amount.\n");
    printf("3. Encryption of a message with a substitution cipher given message text and alphabet substitution.\n");
    printf("4. Decryption of a message encrypted with a substitution cipher given cipher text and substitutions.\n");
    printf("5. Decryption of a message encrypted with a rotation cipher given cipher text only.\n");
    printf("6. Decryption of a message encrypted with a substitution cipher given cipher text only.\n");
    scanf("%d", &task);*/
    task = 2; //manually setting task to bypasa input for now.
    char message[13] = {'H', 'E', 'L', 'L', 'O', ' ', 'W', 'O', 'R', 'L', 'D', '.', '\0'};
    char rotationEncryptionMessage[13] = {'N', 'K', 'R', 'R', 'U', ' ', 'C', 'U', 'X', 'R', 'J', '.', '\0'};
    //printf("    Encrypted Message: %s.\n", rotationEncryptionMessage);
   // printf("%s\n", rotationEncryptionMessage);
    char rotationDecryptionMessage[13] = {};
    switch(task)
    {
        case 1: rotationEncryptionMessage[13] = RotationEncryption(message, rotationEncryptionMessage); 
            printf("    Encryption: %s\n", rotationEncryptionMessage); break;
        case 2: rotationDecryptionMessage[13] = RotationDecryption(rotationEncryptionMessage, rotationDecryptionMessage); 
            printf("    Decryption: %s\n", rotationDecryptionMessage); break;
        case 3: break; 
        case 4: break; 
        case 5: break; 
        case 6: break;
    }
}

//RotationEncryption takes a string and shifts each character in that string by a roation amount (e.g. 6), ignoring non characters that...
//...are not letters.

char RotationEncryption(char *message, char *rotationEncryptionMessage) {
    int shift = 6; //Initialising shift amount to 6 places.
    int index; //Declaring string index.
    printf("Rotation Cipher Encryption:\n");
    printf("    Message: %s\n", message);
    printf("    Rotation key: %d.\n", shift);
    for(index = 0; index < 13; index++) {
        if(message[index] < 65 || message[index] > 90) {    //If the letter is not between A-Z, keep its value
            rotationEncryptionMessage[index] = message[index];           
        }
        else if (message[index] + shift > 90) {             //If the new value goes past Z, finish rotation from A
            int difference = 90 - message[index];
            rotationEncryptionMessage[index] = 64 + difference;
        }
        else {                                              //Add the shift value to rotate each other letter.
            rotationEncryptionMessage[index] = message[index] + shift;
        }

    }
    return *rotationEncryptionMessage;
}   

//RotationDecrption takes the encrypted message from RotationEncryption and shifts each letter back to it's original value.


char RotationDecryption(char *rotationEncryptionMessage, char *rotationDecryptionMessage) {
    int shift = 6;
    int index;
    printf("Rotation Cipher Decryption:\n");
    printf("    Encrypted Message: %s\n", rotationEncryptionMessage);
    printf("    Rotation key: %d.\n", shift);
    for(index = 0; index < 13; index++) {
        if(rotationEncryptionMessage[index] < 65 || rotationEncryptionMessage[index] > 90) {    //If the letter is not between A-Z, keep its value
            rotationDecryptionMessage[index] = rotationEncryptionMessage[index];           
        }
        else if (rotationEncryptionMessage[index] - shift < 65) {             //If the new value is before a A, finish rotation from Z.
            int difference = 64 - rotationEncryptionMessage[index];
            rotationDecryptionMessage[index] = 90 + difference;
        }
        else {                                              //Add the shift value to rotate each other letter.
            rotationDecryptionMessage[index] = rotationEncryptionMessage[index] - shift;
        }

    }
    return *rotationDecryptionMessage;
}
