#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

char Alphabet(char *alphabet);
char RotationEncryption(char *msg, char *rotEncMsg, int shift);
char RotationDecryption(char *rotEncMsg, char *rotDecMsg, int shift);
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
    task = 1; //manually setting task to bypass input for now.
    char commonLetters[6] = {'E', 'T', 'A', 'O', 'I', 'N', '\0'};
    char alphabet[27] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '\0'};
    char msg[1023] = "The quick brown fox jumps over a lazy dog.";
    char rotEncMsg[1023] = {};
    char subAB[27] = {0};
    int shift = 8;
    char subEncMsg[13] = {}; 
    char subDecMsg[13] = {};
    char subDecMsgKl[13] = {};
    char rotDecMsg[13] = {};
    char rotDecMsgKl[13] = {};
    
    switch(task)
    {
        case 1: rotEncMsg[1023] = RotationEncryption(msg, rotEncMsg, shift);
            printf("Rotation Cipher Encryption:\n");
            printf("    Message: %s\n", msg);
            printf("    Rotation key: %d.\n", shift);
            printf("    Encryption: %s\n", rotEncMsg); break;
        case 2: rotEncMsg[1023] = RotationEncryption(msg, rotEncMsg, shift);
            rotDecMsg[1023] = RotationDecryption(rotEncMsg, rotDecMsg, shift);
            printf("Rotation Cipher Decryption:\n");
            printf("    Encrypted Message: %s\n", rotEncMsg);
            printf("    Rotation key: %d.\n", shift);
            printf("    Decryption: %s\n", rotDecMsg); break;
        case 3: subAB[27] = SubstitutionAlphabet(subAB);
            printf("Substitution Alphabet: %s\n", subAB);
            printf("             Alphabet: %s\n", alphabet);
            subEncMsg[1023] = SubstitutionEncryption(msg, subAB, subEncMsg, alphabet); 
            printf("Substitution Encryption: %s\n", subEncMsg); 
            subDecMsg[1023] = SubstitutionDecryption(subEncMsg, subAB, subDecMsg, alphabet);
            printf("Substitution Decryption: %s\n", subDecMsg); break;
            
        case 4: //rotEncMsg[13] = RotationEncryption(msg, rotEncMsg); 
            printf("    Encryption: %s\n", rotEncMsg);        
            rotDecMsg[13] = RotationDecryptionKeyless(rotEncMsg, rotDecMsgKl, alphabet); 
            printf("    Decryption: %s\n", rotDecMsgKl); break;
        case 5: break; 
        case 6: break;
    }
}


//RotationEncryption takes a string and shifts each character in that string by a roation amount (e.g. 6), ignoring characters that...
//...are not letters.

char RotationEncryption(char *msg, char *rotEncMsg, int shift) {
    int index; //Declaring string index.
    for(index = 0; index < 1023; index++) {
        if(msg[index] > 96 && msg[index] < 123) {
            msg[index] = msg[index] - 32;
        }
    }
    for(index = 0; index < 1023; index++) {
        if(msg[index] < 65 || msg[index] > 90) {    //If the letter is not between A-Z, keep its value
            rotEncMsg[index] = msg[index];           
        }
        else if (msg[index] + shift > 90) {             //If the new value goes past Z, finish rotation from A
            int difference = 90 - msg[index];
            int newShift = abs(shift - difference);
            rotEncMsg[index] = 64 + newShift;
        }
        else {                                              //Add the shift value to rotate each other letter.
            rotEncMsg[index] = msg[index] + shift;
        }

    }
    return *rotEncMsg;
}   


//RotationDecrption takes the encrypted msg from RotationEncryption and shifts each letter back to it's original value.

char RotationDecryption(char *rotEncMsg, char *rotDecMsg, int shift) {
    int index;
    for(index = 0; index < 512; index++) {
        if(rotEncMsg[index] > 96 && rotEncMsg[index] < 123) {
            rotEncMsg[index] = rotEncMsg[index] - 32;
        }
    }
    for(index = 0; index < 154; index++) {
        if(rotEncMsg[index] < 65 || rotEncMsg[index] > 90) {    //If the letter is not between A-Z, keep its value
            rotDecMsg[index] = rotEncMsg[index];           
        }
        else if (rotEncMsg[index] - shift < 65) {             //If the new value is before a A, finish rotation from Z.
            int difference = abs(64 - rotEncMsg[index]);
            int newShift = shift - difference;
            rotDecMsg[index] = 90 - newShift;
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
    int greatest = rotAlphabet[0];
    int msgLen = sizeof(rotEncMsg);
    for(REMIndex = 0; REMIndex < 512; REMIndex++) {
        if(rotEncMsg[REMIndex] < 122 &&  rotEncMsg[REMIndex] > 97) {
            rotEncMsg[REMIndex] = rotEncMsg[REMIndex] - 32;
        }
    }
    for(REMIndex = 0; REMIndex < 512; REMIndex++) {
        for(ABIndex = 0; ABIndex < 25; ABIndex++) {
            if(rotEncMsg[REMIndex] == alphabet[ABIndex]) {
                rotAlphabet[ABIndex]++;
            }
        }
    }
    for(rotABIndex = 0; rotABIndex < 25; rotABIndex++) {
        if(rotAlphabet[rotABIndex] >= greatest) {
            greatest = rotAlphabet[rotABIndex];
        }
        else {
            greatest = greatest;
        }
    }
    int KLShift = 14;
    
    //int eShift = abs(69 - greatest);
    //int tShift = abs(69 - greatest);
    //int aShift = abs(69 - greatest);      //Use array instead of these and implement algorithm in a for loop to find shift amount
    //int oShift = abs(69 - greatest);
    //int iShift = abs(69 - greatest);
    //int nShift = abs(69 - greatest);
    
    for(REMIndex = 0; REMIndex < 512; REMIndex++) {
        if(rotEncMsg[REMIndex] < 65 || rotEncMsg[REMIndex] > 90) {    //If the letter is not between A-Z, keep its value
            rotDecMsgKl[REMIndex] = rotEncMsg[REMIndex];           
        }
        else if (rotEncMsg[REMIndex] - KLShift < 65) {             //If the new value is before a A, finish rotation from Z.
            int difference = abs(64 - rotEncMsg[REMIndex]);
            rotDecMsgKl[REMIndex] = 90 - difference;
        }
        else {                                              //Add the shift value to rotate each other letter.
            rotDecMsgKl[REMIndex] = rotEncMsg[REMIndex] - KLShift;
        }
    }
    printf("    Greatest = %d\n", greatest);
    return *rotDecMsgKl;
}