#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

char Alphabet(char *alphabet);
char RotationEncryption(char *message, char *rotationEncryptionMessage);
char RotationDecryption(char *rotationEncryptionMessage, char *rotationDecryptionMessage);
char SubstitutionAlphabet(char *substitutionAlphabet);
char SubstitutionEncryption(char *message, char *substitutionAlphabet, char *substitutionEncryptionMessage, char *alphabet);



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
    task = 3; //manually setting task to bypass input for now.
    char alphabet[27] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '\0'};
    char message[13] = {'H', 'E', 'L', 'L', 'O', ' ', 'W', 'O', 'R', 'L', 'D', '.', '\0'};
    char rotationEncryptionMessage[13] = {'N', 'K', 'R', 'R', 'U', ' ', 'C', 'U', 'X', 'R', 'J', '.', '\0'};
    char substitutionAlphabet[27] = {0};
    
    char substitutionEncryptionMessage[1023] = {}; 
    char rotationDecryptionMessage[1023] = {};
    
    switch(task)
    {
        case 1: rotationEncryptionMessage[13] = RotationEncryption(message, rotationEncryptionMessage); 
            printf("    Encryption: %s\n", rotationEncryptionMessage); break;
        case 2: rotationDecryptionMessage[13] = RotationDecryption(rotationEncryptionMessage, rotationDecryptionMessage); 
            printf("    Decryption: %s\n", rotationDecryptionMessage); break;
        case 3: substitutionAlphabet[27] = SubstitutionAlphabet(substitutionAlphabet);
            printf("Substitution Alphabet: %s\n", substitutionAlphabet);
            printf("             Alphabet: %s\n", alphabet);
            substitutionEncryptionMessage[1023] = SubstitutionEncryption(message, substitutionAlphabet, substitutionEncryptionMessage, alphabet); 
            printf("Substitution Encryption: %s\n", substitutionEncryptionMessage); break; 
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


//Generates a random alphabet subsitution.

char SubstitutionAlphabet(char *substitutionAlphabet) {
    int n=26, i, k;
    bool arr[100]={0};
    srand(time(NULL));
    for(i=0; i<n; ++i) {
        int rNum = rand() % (90 + 1 - 65) + 65;
    if(!arr[rNum]) {
      substitutionAlphabet[i] = rNum;
    }
    else {
      i--;
    }
    arr[rNum]=1;    
  }
    return *substitutionAlphabet;
}


//

char SubstitutionEncryption(char *message, char *substitutionAlphabet, char *substitutionEncryptionMessage, char *alphabet) {
    int msgIndex, abIndex;
    for(msgIndex = 0; msgIndex < 25; msgIndex++) {
        for(abIndex = 0; abIndex < 25; abIndex++) {
            if(message[msgIndex] < 65 || message[msgIndex] > 90) {
                substitutionEncryptionMessage[msgIndex] = message[msgIndex];
            }
            else if(message[msgIndex] == alphabet[abIndex]) {
                substitutionEncryptionMessage[msgIndex] = substitutionAlphabet[abIndex];
            }
        }   
    }
    return *substitutionEncryptionMessage;
}   
