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
//char RotationDecryptionKeyless(char *rotEncMsg, char *rotDecMsgKl, char *alphabet);



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
    
    char commonLetters[6] = {'E', 'T', 'A', 'O', 'I', 'N'};
    char alphabet[27] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '\0'};
    char msg[1023] = "If you can't explain it simply, you don't understand it well enough.";
    char rotEncMsg[1023] = {};
    char subAB[27] = {0};
    int shift = 8;
    char subEncMsg[1023] = {}; 
    char subDecMsg[1023] = {};
    char subDecMsgKl[1023] = {};
    char rotDecMsg[1023] = {};
    char rotDecMsgKl[1023] = {};
    subAB[27] = SubstitutionAlphabet(subAB); //Randomly generating a substitution at the beginnning, so it can be used independant of the case of encryption followed by decryption by subsitution.
    task = 3; //manually setting task to bypass input for now.
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
        case 3: printf("Substitution Alphabet: %s\n", subAB);
            printf("             Alphabet: %s\n", alphabet);
            subEncMsg[1023] = SubstitutionEncryption(msg, subAB, subEncMsg, alphabet); 
            printf("Substitution Encryption: %s\n", subEncMsg); break;
        case 4: printf("Substitution Alphabet: %s\n", subAB);
            printf("             Alphabet: %s\n", alphabet); 
            subDecMsg[1023] = SubstitutionDecryption(subEncMsg, subAB, subDecMsg, alphabet);
            printf("Substitution Decryption: %s\n", subDecMsg); break;
        case 5: /*rotEncMsg[13] = RotationEncryption(msg, rotEncMsg); 
            printf("    Encryption: %s\n", rotEncMsg);        
            rotDecMsg[13] = RotationDecryptionKeyless(rotEncMsg, rotDecMsgKl, alphabet); 
            printf("    Decryption: %s\n", rotDecMsgKl);*/ break; 
        case 6: break;
    }
}


/* Rotation Encryption:
 *      The rotation encryption function takes a string and a shift amount (rotation key). This function rotates every upper-case letter in the string
 *      by the rotation key, so every encrypted character is offset by the same number of letters. Before doing so, however, the function converts 
 *      any character that is lower-case into an upper-case so that the function is not case-sensitive. This function only encrypts English letters and
 *      leaves any special characters in the string as they were in the original message.
 *      The encrypted message is returned to the string 'rotEncMsg'.
 */

char RotationEncryption(char *msg, char *rotEncMsg, int shift) {
    int index, msgLen = 1023;                                       //Declaring string index and initialising the length of the message (an arbitrary number).
    for(index = 0; index < msgLen; index++) {                       //For loop goes through each character to check if it is lower-case and converts any instances 
        if(msg[index] > 96 && msg[index] < 123) {                   //... into upper-case letters.
            msg[index] = msg[index] - 32;                           //Lower-case ASCII characters begin at 97 ('a'), and end at 122 ('z'). The difference between each
        }                                                           //... corresponding upper and lower-case characters on the ASCII table is 32.
    }
    for(index = 0; index < 1023; index++) {                         //For loop for rotation encryption.
        if(msg[index] < 65 || msg[index] > 90) {                    //If statement checks if the letter is not within range of A-Z, keeping the value at any index where
            rotEncMsg[index] = msg[index];                          //... there is a positive instance.
        }
        else if (msg[index] + shift > 90) {                         //If statement to check if the new value (after rotation) goes past Z, and to continue rotation from A
            int difference = 90 - msg[index];                       //... where true.
            int contShift = abs(shift - difference);
            rotEncMsg[index] = 64 + contShift;
        }
        else {                                                      //Else statement to add the rotation amount to any other character (upper-case letters).
            rotEncMsg[index] = msg[index] + shift;
        }

    }
    return *rotEncMsg;                                              //Returns the message, encrypted by the rotation cipher, to the string 'rotEncMsg'.
}   


/* Rotation Decrption: 
 *      The rotation decryption function takes an encrypted message (possibly from RotationEncryption) and shifts each letter back to it's original value with
 *      the same rotation key given. Like the rotation encryption function, this function converts any lower-case letters into upper case and ignores special
 *      or foreign characters (i.e. they retain their original value).
 *      The decrypted message is returned to the string 'rotDecMsg'.
 */

char RotationDecryption(char *rotEncMsg, char *rotDecMsg, int shift) {
    int index, msgLen = 1023;                                             //Declaring string index and initialising the length of the message (an arbitrary number).
    for(index = 0; index < msgLen; index++) {                             //For loop goes through each character to check if it is lower-case and converts any instances  
        if(rotEncMsg[index] > 96 && rotEncMsg[index] < 123) {             //... into upper-case letters.
            rotEncMsg[index] = rotEncMsg[index] - 32;
        }
    }
    for(index = 0; index < msgLen; index++) {                             //For loop for rotation decryption.
        if(rotEncMsg[index] < 65 || rotEncMsg[index] > 90) {              //If statement checks if the letter is not within range of A-Z, keeping the value at any index where
            rotDecMsg[index] = rotEncMsg[index];                          //... there is a positive instance.
        }
        else if (rotEncMsg[index] - shift < 65) {                         //If statement to check if the new value (after rotation) goes past A, and to continue rotation from Z
            int difference = abs(64 - rotEncMsg[index]);                  //... where true.
            int contShift = shift - difference;
            rotDecMsg[index] = 90 - contShift;
        }
        else {                                                            //Else statement to add the rotation amount to any other character (upper-case letters).
            rotDecMsg[index] = rotEncMsg[index] - shift;
        }
    }
    return *rotDecMsg;                                                    //Returns the message, decrypted by the rotation cipher, to the string 'rotDecMsg'.
}


/* Substitution Alphabet:
 *      This function generates a new (random) position for each letter in the alphabet every time it is called.
 *      The substitution alphabet is returned to the string 'subAB'.
 */

char SubstitutionAlphabet(char *subAB) {
    int index;                                     //Declaring string index.
    bool check[100]={0};                           //Boolean array (size is arbitrary) to serve later for reference as to whether or not that position has been used.
    srand(time(NULL));                             //Generates a "random" seed based on computer's internal clock.
    for(index = 0; index < 26; ++index) {          //For loop for generating the random positions for each letter.
        int rNum = rand() % (90 + 1 - 65) + 65;    //Generating a random integer between 90 and 65.
        if(!check[rNum]) {                         //If statement to check if alphabet position is not already taken, using that position where true. 
          subAB[index] = rNum;
        }
        else {                                     //Else statement that sets index back by a value of 1 so the program can re-try a new postion for that letter.
            index--;
        }
        check[rNum] = 1;                           //Sets the value at that index to 1, indicating that the position at this index is taken.
    }
    return *subAB;                                 //Returns the substitution alphabet is returned to the string 'subAB'.
}


//

char SubstitutionEncryption(char *msg, char *subAB, char *subEncMsg, char *alphabet) {
    int msgIndex, abIndex, msgLen = 1023;
    for(msgIndex = 0; msgIndex < msgLen; msgIndex++) {
        if(msg[msgIndex] > 96 && msg[msgIndex] < 123) {
            msg[msgIndex] = msg[msgIndex] - 32;
        }
    }
    for(msgIndex = 0; msgIndex < msgLen; msgIndex++) {
        for(abIndex = 0; abIndex < 26; abIndex++) {
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
    int SubEncMsgIndex, subABIndex, msgLen = 1023;
    for(SubEncMsgIndex = 0; SubEncMsgIndex < msgLen; SubEncMsgIndex++) {
        if(subEncMsg[SubEncMsgIndex] > 96 && subEncMsg[SubEncMsgIndex] < 123) {
            subEncMsg[SubEncMsgIndex] = subEncMsg[SubEncMsgIndex] - 32;
        }
    }
    for(SubEncMsgIndex = 0; SubEncMsgIndex < msgLen; SubEncMsgIndex++) {
           for(subABIndex = 0; subABIndex < 26; subABIndex++) {
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
    
/*char RotationDecryptionKeyless(char *rotEncMsg, char *rotDecMsgKl, char *alphabet) {
    char rotAlphabet[26] = {};
    int ABIndex, REMIndex, rotABIndex, rotABIndexM1, msgLen = 1023;
    int greatest = rotAlphabet[0];
    for(REMIndex = 0; REMIndex < msgLen; REMIndex++) {
        if(rotEncMsg[REMIndex] < 122 &&  rotEncMsg[REMIndex] > 97) {
            rotEncMsg[REMIndex] = rotEncMsg[REMIndex] - 32;
        }
    }
    for(REMIndex = 0; REMIndex < msgLen; REMIndex++) {
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
    
    for(REMIndex = 0; REMIndex < msgLen; REMIndex++) {
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
}*/