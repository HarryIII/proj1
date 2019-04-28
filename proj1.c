#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

char Alphabet(char *alphabet);

char RotationSubstitutionAlphabet(char *alphabet, char *rotSubAB, int shift);
char RotationEncryption(char *msg, char *rotEncMsg, char *rotSubAB, char *alphabet);
char RotationDecryption(char *rotEncMsg, char *rotDecMsg, char *rotSubAB, char *alphabet); 

char SubstitutionAlphabet(char *subAB);
char SubstitutionEncryption(char *msg, char *subAB, char *subEncMsg, char *alphabet);
char SubstitutionDecryption(char *subEncMsg,  char *subAB, char *subDecMsg, char *alphabet);

char RotationDecryptionKeyless(char *rotEncMsg, char *rotDecMsgKl, char *alphabet, char *commonLetters);


/*  Main Function:
 *      The main function displays the options menu to the console, contains the strings (and some other variables) used by the functions and 
 *      contains the switch statement that accepts the task input and executes the appropriate function.
 */

int main() {
    int task;                                                                                                       //Declaring integer for storing selected task.
    printf("Select a task: \n");                                                                                    //This line and following 6 lines print menu
    printf("1. Encryption of a message with a rotation cipher given the msg text and rotation amount.\n");          //... options.
    printf("2. Decryption of a message encrypted with a rotation cipher given cipher text and rotation amount.\n");
    printf("3. Encryption of a message with a substitution cipher given msg text and alphabet substitution.\n");
    printf("4. Decryption of a message encrypted with a substitution cipher given cipher text and substitutions.\n");
    printf("5. Decryption of a message encrypted with a rotation cipher given cipher text only.\n");
    printf("6. ---[NOT AVAILABLE]--- Decryption of a message encrypted with a substitution cipher given cipher text only.\n");
    //Following strings contains the alphabet, a place for a rotation substitution alphabet and a place for a substitution alphabet (generated later).
    char alphabet[27] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '\0'};
    char rotSubAB[27] = {};     //"rotSubAB" = rotation substitution alphabet.
    char subAB[27] = {0};       //"subAB" = substitution alphabet.
    //The following string contains the 6 most common letters found in english texts.
    char commonLetters[6] = {'E', 'T', 'A', 'O', 'I', 'N'};
    //The following string is a place for the message input (to be allocated by text in File I/O).
    char msg[1023] = {};    //"msg" = message.
    //The following strings are places for all of the rotation cipher messages.
    char rotEncMsg[1023] = {};      //"rotEncMsg" = rotaton encryption message.
    char rotDecMsg[1023] = {};      //"rotDecMsg" = rotation decryption message.
    char rotDecMsgKl[1023] = {};    //"rotDecMsgKl" = rotation decryption message keyless.
    //The following strings are places for all  of the substitution cipher messages.
    char subEncMsg[1023] = {};      //"subEncMsg" = substitution encryption message.
    char subDecMsg[1023] = {};      //"subDecMsg" = substitution decryption message.
    
    int shift;      //Declaring integer for storing selected rotation key (shift amount).
    
    scanf("%d %d", &task, &shift);      //Scanning input file for task and shift variables.
    
    //Generating alphabets for both cipher methods at beginning
    rotSubAB[27] = RotationSubstitutionAlphabet(alphabet, rotSubAB, shift);
    subAB[27] = SubstitutionAlphabet(subAB);
    
    switch(task)
    {
        case 1: rotEncMsg[1023] = RotationEncryption(msg, rotEncMsg, rotSubAB, alphabet);
            printf("Rotation Cipher Encryption:\n");
            printf("    Message: %s\n", msg);
            printf("    Rotation key: %d.\n", shift);
            printf("    Encryption: %s\n", rotEncMsg); break;
        case 2: rotEncMsg[1023] = RotationEncryption(msg, rotEncMsg, rotSubAB, alphabet);
            rotDecMsg[1023] = RotationDecryption(rotEncMsg, rotDecMsg, rotSubAB, alphabet);
            printf("Rotation Cipher Decryption:\n");
            printf("    Encrypted Message: %s\n", rotEncMsg);
            printf("    Rotation key: %d.\n", shift);
            printf("    Decryption: %s\n", rotDecMsg); break;
        case 3: printf("Substitution Alphabet: %s\n", subAB);
            printf("             Alphabet: %s\n", alphabet);
            subEncMsg[1023] = SubstitutionEncryption(msg, subAB, subEncMsg, alphabet); 
            printf("Substitution Cipher Encryption: %s\n", subEncMsg); break;
        case 4: printf("Substitution Alphabet: %s\n", subAB);
            printf("             Alphabet: %s\n", alphabet); 
            subDecMsg[1023] = SubstitutionDecryption(subEncMsg, subAB, subDecMsg, alphabet);
            printf("Substitution Cipher Decryption: %s\n", subDecMsg); break;
        case 5: printf("                      Encryption: %s\n", rotEncMsg);
            RotationDecryptionKeyless(rotEncMsg, rotDecMsgKl, alphabet, commonLetters); break;
        case 6: break;
    }
}


/* Rotation Cipher Key:
 *      This function takes the shift amount and generates a substitution alphabet for the rotation cipher.
 *      The rotation substitution alphabet is returned to the string 'rotSubAB'
 */

char RotationSubstitutionAlphabet(char *alphabet, char *rotSubAB, int shift) {
    int abIndex;
    //if shift is negative (less than zero) find equivelent positive shift
    for(abIndex = 0; abIndex < 26; abIndex++) {
        if((alphabet[abIndex] + shift) > 90) {
            int difference = 90 - alphabet[abIndex];                       
            int contShift = abs(shift - difference);
            rotSubAB[abIndex] = 64 + contShift;
        }
        else {
        rotSubAB[abIndex] = alphabet[abIndex] + shift;
        }
    }
    return *rotSubAB;
}


/* Rotation Encryption:
 *      This function uses the previously generated rotation substitution alphabet to replace every upper-case letter in the message 
 *      with the corresponding letter (found at the same index) in the rotation substitution alphabet. There is a fixed distance between each letter 
 *      in the alphabet and the correspodning letter at the same index in the rotation substitution alphabet. Before doing so however, the function converts 
 *      any character that is lower-case into upper-case so that the function is not case-sensitive. This function only encrypts English letters and
 *      leaves any special characters in the string as they were in the original message.
 *      The encrypted message is returned to the string 'rotEncMsg'.
 */

char RotationEncryption(char *msg, char *rotEncMsg, char *rotSubAB, char *alphabet) {
    int msgIndex, abIndex, msgLen = 1023;                                                //Declaring string index and initialising the length of the message (an arbitrary number).
    for(msgIndex = 0; msgIndex < msgLen; msgIndex++) {                                   //For loop goes through each character to check if it is lower-case and converts any instances 
        if(msg[msgIndex] > 96 && msg[msgIndex] < 123) {                                  //... into upper-case letters.
            msg[msgIndex] = msg[msgIndex] - 32;                                          //Lower-case ASCII characters begin at 97 ('a'), and end at 122 ('z'). The difference between each
        }                                                                                //... corresponding upper and lower-case characters on the ASCII table is 32.
    }
    for(msgIndex = 0; msgIndex < msgLen; msgIndex++) {                                   //For loop for rotation encryption.
        for(abIndex = 0; abIndex < 26; abIndex++) {
           if(msg[msgIndex] < 65 || msg[msgIndex] > 90) {                                //If statement checks if the letter is not within range of A-Z, keeping the value at any index where
             rotEncMsg[msgIndex] = msg[msgIndex];                                        //... there is a positive instance.
            }
            else if(msg[msgIndex] == alphabet[abIndex]) {                                //Else If statement checks if message character matches alphabet character. 
                rotEncMsg[msgIndex] = rotSubAB[abIndex];
            }
        } 
    }
    return *rotEncMsg;                                                                   //Returns the message, encrypted by the rotation cipher, to the string 'rotEncMsg'.
}   


/* Rotation Decryption: 
 *      The substitution decryption function takes an encrypted message (possibly from RotationEncryption) and replaces each letter back to it's original value with
 *      the same same rotation substitution alphabet given. Similar to the rotation encryption function, this function converts any lower-case letters into upper case and ignores special
 *      or foreign characters (i.e. they retain their original value).
 *      The decrypted message is returned to the string 'rotDecMsg'.
 */

char RotationDecryption(char *rotEncMsg, char *rotDecMsg, char *rotSubAB, char *alphabet) {
    int index, rotSubABIndex, rotEncMsgIndex, msgLen = 1023;                                   //Declaring string index and initialising the length of the message (an arbitrary number).
    for(index = 0; index < msgLen; index++) {                                                  //For loop goes through each character to check if it is lower-case and converts any instances  
        if(rotEncMsg[index] > 96 && rotEncMsg[index] < 123) {                                  //... into upper-case letters.
            rotEncMsg[index] = rotEncMsg[index] - 32;
        }
    }
    for(rotEncMsgIndex = 0; rotEncMsgIndex < msgLen; rotEncMsgIndex++) {                       //For loop for rotation decryption. Goes through each character of the encrypted message.
           for(rotSubABIndex = 0; rotSubABIndex < 26; rotSubABIndex++) {                       //... For each encrypted message character, each character of rotation substitution alphabet is compared to later test if it matches.
               if(rotEncMsg[rotEncMsgIndex] < 65 || rotEncMsg[rotEncMsgIndex] > 90) {          //If statement checks if the letter is not within range of A-Z, keeping the value at any index where
                   rotDecMsg[rotEncMsgIndex] = rotEncMsg[rotEncMsgIndex];                      //... where true.
               }
               else if(rotEncMsg[rotEncMsgIndex] == rotSubAB[rotSubABIndex]) {                 //Else If statement checks if encrypted message character matches rotation substitution alphabet character.
                   rotDecMsg[rotEncMsgIndex] = alphabet[rotSubABIndex];                        //... Where true, message character is replaced with rotation substitution alphabet character.
               }
           }   
    }
    return *rotDecMsg;                                                                        //Returns the message, decrypted by the rotation cipher, to the string 'rotDecMsg'.
}


/* Substitution Alphabet:
 *      This function generates a new (random) position for each letter in the alphabet every time it is called.
 *      The substitution alphabet is returned to the string 'subAB'.
 */

char SubstitutionAlphabet(char *subAB) {
    int abIndex;                                  //Declaring Alphabet Index.
    bool check[100]={0};                           //Boolean array (size is arbitrary) to serve later for reference as to whether or not that position has been used.
    srand(time(NULL));                             //Generates a "random" seed based on computer's internal clock.
    for(abIndex = 0; abIndex < 26; ++abIndex) {          //For loop for generating the random positions for each letter.
        int rNum = rand() % (90 + 1 - 65) + 65;    //Generating a random integer between 90 and 65.
        if(!check[rNum]) {                         //If statement to check if alphabet position is not already taken, using that position where true. 
          subAB[abIndex] = rNum;
        }
        else {                                     //Else statement that sets index back by a value of 1 so the program can re-try a new postion for that letter.
            abIndex--;
        }
        check[rNum] = 1;                           //Sets the value at that index to 1, indicating that the position at this index is taken.
    }
    return *subAB;                                 //Returns the substitution alphabet is returned to the string 'subAB'.
}


/* Substitution Encryption:
 *      This function uses the previously generated substitution alphabet to replace every upper-case letter in the message 
 *      with the corresponding letter (found at the same index) in the substitution alphabet. Before doing so however, the function converts 
 *      any character that is lower-case into upper-case so that the function is not case-sensitive. This function only encrypts English letters and
 *      leaves any special characters in the string as they were in the original message.
 *      The encrypted message is returned to the string 'subEncMsg'.
 */

char SubstitutionEncryption(char *msg, char *subAB, char *subEncMsg, char *alphabet) {
    int msgIndex, abIndex, msgLen = 1023;                                                 //Declaring Message and Alphabet index. Initialising message length.
    for(msgIndex = 0; msgIndex < msgLen; msgIndex++) {                                    //For loop goes through each character to check if it is lower-case and converts any instances 
        if(msg[msgIndex] > 96 && msg[msgIndex] < 123) {                                   //... into upper-case letters. 
            msg[msgIndex] = msg[msgIndex] - 32;                                           
        }
    }
    for(msgIndex = 0; msgIndex < msgLen; msgIndex++) {                                    //For loop for substitution encryption. Goes through each character of the message.
        for(abIndex = 0; abIndex < 26; abIndex++) {                                       //... For each message character, each character of alphabet is compared to later test if it matches.
            if(msg[msgIndex] < 65 || msg[msgIndex] > 90) {                                //If statement checks if the letter is not within range of A-Z, keeping the value at any index where
                subEncMsg[msgIndex] = msg[msgIndex];                                      //... where true.
            }
            else if(msg[msgIndex] == alphabet[abIndex]) {                                 //Else If statement checks if message character matches alphabet character. 
                subEncMsg[msgIndex] = subAB[abIndex];                                     //... Where true, message character is replaced with substitution alphabet character.
            }
        }   
    }
    return *subEncMsg;                                                                    //Returns the message, encrypted by the substitution cipher, to the string 'subEncMsg'.
}   


/* Substitution Decryption.
 *      The substitution decryption function takes an encrypted message (possibly from SubstitutionEncryption) and replaces each letter back to it's original value with
 *      the same same substitution alphabet given. Similar to the substitution encryption function, this function converts any lower-case letters into upper case and ignores special
 *      or foreign characters (i.e. they retain their original value).
 *      The decrypted message is returned to the string 'subDecMsg'.
 */

char SubstitutionDecryption(char *subEncMsg,  char *subAB, char *subDecMsg, char *alphabet) {
    int SubEncMsgIndex, subABIndex, msgLen = 1023;                                               //Declaring Substitution Encryption Message and Substitution Alphabet indices. Initialising Message Length.
    for(SubEncMsgIndex = 0; SubEncMsgIndex < msgLen; SubEncMsgIndex++) {                         
        if(subEncMsg[SubEncMsgIndex] > 96 && subEncMsg[SubEncMsgIndex] < 123) {                  
            subEncMsg[SubEncMsgIndex] = subEncMsg[SubEncMsgIndex] - 32;
        }
    }
    for(SubEncMsgIndex = 0; SubEncMsgIndex < msgLen; SubEncMsgIndex++) {                         //For loop for substitution decryption. Goes through each character of the encrypted message.
           for(subABIndex = 0; subABIndex < 26; subABIndex++) {                                  //... For each encrypted message character, each character of substitution alphabet is compared to later test if it matches.
               if(subEncMsg[SubEncMsgIndex] < 65 || subEncMsg[SubEncMsgIndex] > 90) {            //If statement checks if the letter is not within range of A-Z, keeping the value at any index where
                   subDecMsg[SubEncMsgIndex] = subEncMsg[SubEncMsgIndex];                        //... where true.
               }
               else if(subEncMsg[SubEncMsgIndex] == subAB[subABIndex]) {                         //Else If statement checks if encrypted message character matches substitution alphabet character.
                   subDecMsg[SubEncMsgIndex] = alphabet[subABIndex];                             //... Where true, message character is replaced with substitution alphabet character.
               }
           }   
    }
       return *subDecMsg;                                                                        //Returns the message, decrypted by the substitution cipher, to the string 'subDecMsg'.
}
  
  
/* Rotation Encryption Keyless:
 *      asdfasdfasdf
 * 
 * 
 * 
 */
    
char RotationDecryptionKeyless(char *rotEncMsg, char *rotDecMsgKl, char *alphabet, char *commonLetters) {
    char rotAlphabet[26] = {};
    int ABIndex, REMIndex, rotABIndex, cLSABIndex, ordinalIndex, shift, msgLen = 1023;
    int greatest = alphabet[0];
    char ordinalGreatest[7] = {};
    char tempRotSubAB[26] = {};
    char tempRotDecMsg[1023] = {};
    for(REMIndex = 0; REMIndex < msgLen; REMIndex++) {
        if(rotEncMsg[REMIndex] > 96 && rotEncMsg[REMIndex] < 123) {
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
    for(ordinalIndex = 0; ordinalIndex < 7; ordinalIndex++) {  
        for(rotABIndex = 0; rotABIndex < 25; rotABIndex++) {
            if(rotAlphabet[rotABIndex] >= greatest) {
                greatest = alphabet[rotABIndex];
            }
            else {
                greatest = greatest;
            }
        }
        ordinalGreatest[ordinalIndex] = greatest;
        for(rotABIndex = 0; rotABIndex < 25; rotABIndex++) {
            if(rotAlphabet[rotABIndex] == greatest) {
                rotAlphabet[rotABIndex] = 0;
            }
            else {
                rotAlphabet[rotABIndex] = rotAlphabet[rotABIndex];
            }
        }
    }    
    char commonLetterShift[7] = {0};
    int cLSIndex;
    
    for(cLSIndex = 0; cLSIndex < 7; cLSIndex++) {
        commonLetterShift[cLSIndex] = abs(commonLetters[cLSIndex] - ordinalGreatest[cLSIndex]);
    }
    for(cLSIndex = 0; cLSIndex < 6; cLSIndex++) {
        int attempt = cLSIndex + 1;
        for(cLSABIndex = 0; cLSABIndex < 26; cLSABIndex++) {
            if((alphabet[cLSABIndex] + shift) > 90) {
                int difference = 90 - commonLetterShift[cLSIndex];                       
                int contShift = abs(shift - difference);
                tempRotSubAB[cLSABIndex] = 64 + contShift;
            }
            else {
            tempRotSubAB[cLSABIndex] = alphabet[cLSABIndex] - commonLetterShift[cLSIndex];
            }
        }
        for(REMIndex = 0; REMIndex < msgLen; REMIndex++) {                                   //For loop for rotation encryption.
            for(ABIndex = 0; ABIndex < 26; ABIndex++) {
               if(rotEncMsg[REMIndex] < 65 || rotEncMsg[REMIndex] > 90) {                                //If statement checks if the letter is not within range of A-Z, keeping the value at any index where
                 tempRotDecMsg[REMIndex] = rotEncMsg[REMIndex];                                        //... there is a positive instance.
                }
                else if(rotEncMsg[REMIndex] == alphabet[ABIndex]) {                                //Else If statement checks if message character matches alphabet character. 
                    tempRotDecMsg[REMIndex] = tempRotSubAB[ABIndex];
                }
            }
        }
        printf("Rotation Decryption Attempt %d: \n", attempt);
        printf("                            %s \n", tempRotDecMsg);    
    }
    return 0;
}
