#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

char Alphabet(char *alphabet);
char RotationEncryption(char *msg, char *rotEncMsg);
char RotationDecryption(char *rotEncMsg, char *rotDecMsg);
char SubstitutionAlphabet(char *subAB);
char SubstitutionEncryption(char *msg, char *subAB, char *subEncMsg, char *alphabet);
char SubstitutionDecryption(char *subEncMsg,  char *subAB, char *subDecMsg, char *alphabet);
char RotationDecryptionKeyless(char *rotEncMsg, char *rotDecMsgKl, char *alphabet);



int main() {
    int task; //Integer for storing selected task
  /*printf("Select a task: \n");
    printf("1. Encryption of a message with a rotation cipher given the msg text and rotation amount.\n");
    printf("2. Decryption of a message encrypted with a rotation cipher given cipher text and rotation amount.\n");
    printf("3. Encryption of a message with a substitution cipher given msg text and alphabet substitution.\n");
    printf("4. Decryption of a message encrypted with a substitution cipher given cipher text and substitutions.\n");
    printf("5. Decryption of a message encrypted with a rotation cipher given cipher text only.\n");
    printf("6. Decryption of a message encrypted with a substitution cipher given cipher text only.\n");
    scanf("%d", &task);*/
    task = 4; //manually setting task to bypass input for now.
    char alphabet[27] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '\0'};
    char msg[13] = {'H', 'E', 'L', 'L', 'O', ' ', 'W', 'O', 'R', 'L', 'D', '.', '\0'};
    char rotEncMsg[13] = {'N', 'K', 'R', 'R', 'U', ' ', 'C', 'U', 'X', 'R', 'J', '.', '\0'};
    char subAB[27] = {0};
    
    char subEncMsg[13] = {}; 
    char subDecMsg[13] = {};
    char subDecMsgKl[13] = {};
    char rotDecMsg[13] = {};
    char rotDecMsgKl[13] = {};
    
    switch(task)
    {
        case 1: rotEncMsg[13] = RotationEncryption(msg, rotEncMsg); 
            printf("    Encryption: %s\n", rotEncMsg); break;
        case 2: rotDecMsg[13] = RotationDecryption(rotEncMsg, rotDecMsg); 
            printf("    Decryption: %s\n", rotDecMsg); break;
        case 3: subAB[27] = SubstitutionAlphabet(subAB);
            printf("Substitution Alphabet: %s\n", subAB);
            printf("             Alphabet: %s\n", alphabet);
            subEncMsg[1023] = SubstitutionEncryption(msg, subAB, subEncMsg, alphabet); 
            printf("Substitution Encryption: %s\n", subEncMsg); 
            subDecMsg[1023] = SubstitutionDecryption(subEncMsg, subAB, subDecMsg, alphabet);
            printf("Substitution Decryption: %s\n", subDecMsg); break;
            
        case 4: rotEncMsg[13] = RotationEncryption(msg, rotEncMsg); 
            printf("    Encryption: %s\n", rotEncMsg);        
            rotDecMsg[13] = RotationDecryptionKeyless(rotEncMsg, rotDecMsgKl, alphabet); 
            printf("    Decryption: %s\n", rotDecMsgKl); break;
        case 5: break; 
        case 6: break;
    }
}


//RotationEncryption takes a string and shifts each character in that string by a roation amount (e.g. 6), ignoring non characters that...
//...are not letters.

char RotationEncryption(char *msg, char *rotEncMsg) {
    int shift = 6; //Initialising shift amount to 6 places.
    int index; //Declaring string index.
    printf("Rotation Cipher Encryption:\n");
    printf("    Message: %s\n", msg);
    printf("    Rotation key: %d.\n", shift);
    for(index = 0; index < 13; index++) {
        if(msg[index] < 65 || msg[index] > 90) {    //If the letter is not between A-Z, keep its value
            rotEncMsg[index] = msg[index];           
        }
        else if (msg[index] + shift > 90) {             //If the new value goes past Z, finish rotation from A
            int difference = 90 - msg[index];
            rotEncMsg[index] = 64 + difference;
        }
        else {                                              //Add the shift value to rotate each other letter.
            rotEncMsg[index] = msg[index] + shift;
        }

    }
    return *rotEncMsg;
}   


//RotationDecrption takes the encrypted msg from RotationEncryption and shifts each letter back to it's original value.

char RotationDecryption(char *rotEncMsg, char *rotDecMsg) {
    int shift = 6;
    int index;
    printf("Rotation Cipher Decryption:\n");
    printf("    Encrypted msg: %s\n", rotEncMsg);
    printf("    Rotation key: %d.\n", shift);
    for(index = 0; index < 13; index++) {
        if(rotEncMsg[index] < 65 || rotEncMsg[index] > 90) {    //If the letter is not between A-Z, keep its value
            rotDecMsg[index] = rotEncMsg[index];           
        }
        else if (rotEncMsg[index] - shift < 65) {             //If the new value is before a A, finish rotation from Z.
            int difference = 64 - rotEncMsg[index];
            rotDecMsg[index] = 90 + difference;
        }
        else {                                              //Add the shift value to rotate each other letter.
            rotDecMsg[index] = rotEncMsg[index] - shift;
        }

    }
    return *rotDecMsg;
}


//Generates a random alphabet subsitution.

char SubstitutionAlphabet(char *subAB) {
    int n=26, i, k;
    bool arr[100]={0};
    srand(time(NULL));
    for(i=0; i<n; ++i) {
        int rNum = rand() % (90 + 1 - 65) + 65;
    if(!arr[rNum]) {
      subAB[i] = rNum;
    }
    else {
      i--;
    }
    arr[rNum]=1;    
  }
    return *subAB;
}


//

char SubstitutionEncryption(char *msg, char *subAB, char *subEncMsg, char *alphabet) {
    int msgIndex, abIndex;
    for(msgIndex = 0; msgIndex < 25; msgIndex++) {
        for(abIndex = 0; abIndex < 25; abIndex++) {
            if(msg[msgIndex] < 65 || msg[msgIndex] > 90) {
                subEncMsg[msgIndex] = msg[msgIndex];
            }
            else if(msg[msgIndex] == alphabet[abIndex]) {
                subEncMsg[msgIndex] = subAB[abIndex];
            }
        }   
    }
    return *subEncMsg;
}   


//

char SubstitutionDecryption(char *subEncMsg,  char *subAB, char *subDecMsg, char *alphabet) {
    int SubEncMsgIndex, subABIndex;
        for(SubEncMsgIndex = 0; SubEncMsgIndex < 25; SubEncMsgIndex++) {
            for(subABIndex = 0; subABIndex < 25; subABIndex++) {
                if(subEncMsg[SubEncMsgIndex] < 65 || subEncMsg[SubEncMsgIndex] > 90) {
                    subDecMsg[SubEncMsgIndex] = subEncMsg[SubEncMsgIndex];
                }
                else if(subEncMsg[SubEncMsgIndex] == subAB[subABIndex]) {
                    subDecMsg[SubEncMsgIndex] = alphabet[subABIndex];
                }
            }   
        }
        return *subDecMsg;
    }
    
//
    
char RotationDecryptionKeyless(char *rotEncMsg, char *rotDecMsgKl, char *alphabet) {
    char rotAlphabet[26] = {};
    int ABIndex, REMIndex, rotABIndex, rotABIndexM1;
    char greatest;
    int msgLen = sizeof(rotEncMsg);
    for(REMIndex = 0; REMIndex < msgLen; REMIndex++) {
        for(ABIndex = 0; ABIndex < 25; ABIndex++) {
            if(rotEncMsg[REMIndex] == alphabet[ABIndex]) {
                rotAlphabet[ABIndex]++;
            }
        }
    }
    for(rotABIndex = 1; rotABIndex < 25; rotABIndex++) {
        rotABIndexM1 = rotABIndex - 1;
        if(rotAlphabet[rotABIndex] >= rotAlphabet[rotABIndexM1]) {
            greatest = rotAlphabet[rotABIndex];
        }
        else {
            greatest = greatest;
        }
    }
    int shift = abs('E' - greatest);
    for(REMIndex = 0; REMIndex < 13; REMIndex++) {
            if(rotEncMsg[REMIndex] < 65 || rotEncMsg[REMIndex] > 90) {    //If the letter is not between A-Z, keep its value
            rotDecMsgKl[REMIndex] = rotEncMsg[REMIndex];           
        }
        else if (rotEncMsg[REMIndex] - shift < 65) {             //If the new value is before a A, finish rotation from Z.
            int difference = 64 - rotEncMsg[REMIndex];
            rotDecMsgKl[REMIndex] = 90 + difference;
        }
        else {                                              //Add the shift value to rotate each other letter.
            rotDecMsgKl[REMIndex] = rotEncMsg[REMIndex] - shift;
        }
    } 
    return *rotDecMsgKl;
}