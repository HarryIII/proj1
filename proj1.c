/* The program:
 *      This program use File I/O functions to read messages and seperate functions to encrypt or decrypt
 *      the messages accordingly. There are multiple options for encryption/decyrption which are displayed
 *      in the options menu and can be selected by setting the desired task in the decisions.txt file. 
 *      The program is capable of processing two cipher methods: rotation cipher (or Caesar cipher)
 *      and substitutiton cipher.
 */


/* File I/O Information:
 *      input.txt:
 *          1: (task number --> 'task') 
 *          2: (shift amount --> 'shift')
 *      filemessage.txt:
 *          1: (message to be encrypted --> 'msg')
 *      testRotEncMsg.txt:
 *          1: (message to be decrypted by rotation --> 'rotEncMsgTest')
 *      testSubAlphabet.txt:
 *          1: (given substitution alphabet --> 'subAlphabetTest')
 *      testSubEncMsg.txt:
 *          1: (message to be decrypted by substitutiton --> 'subEmcMsgTest')
 *
 * ---Each file contains sample messages (these should be replaced)---
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdbool.h>

//Following lines contain function prototypes for each function in program.
char Alphabet(char *alphabet);

char RotationSubstitutionAlphabet(char *alphabet, char *rotSubAB, int shift);
char RotationEncryption(char *msg, char *rotEncMsg, char *rotSubAB, char *alphabet);
char RotationDecryption(char *rotEncMsgTest, char *rotDecMsg, char *rotSubAB, char *alphabet); 

char SubstitutionAlphabet(char *subAB);
char SubstitutionEncryption(char *msg, char *subAB, char *subEncMsg, char *alphabet);
char SubstitutionDecryption(char *subEncMsgTest,  char *subAlphabetTest, char *subDecMsg, char *alphabet);

char RotationDecryptionKeyless(char *rotEncMsgTest, char *alphabet, char *commonLetters);


/*  Main Function:
 *      The main function displays the options menu to the console, contains the strings (and some other variables) used by the functions and 
 *      contains the switch statement that accepts the task input and executes the appropriate function.
 */

int main() {
    int task;                                                                                                           //Declaring integer for storing selected task.
    printf("Select a task: \n");                                                                                        //This line and following 6 lines print menu
    printf("1. Encryption of a message with a rotation cipher given the msg text and rotation amount.\n");              //... options.
    printf("2. Decryption of a message encrypted with a rotation cipher given cipher text and rotation amount.\n");
    printf("3. Encryption of a message with a substitution cipher given msg text and alphabet substitution.\n");
    printf("4. Decryption of a message encrypted with a substitution cipher given cipher text and substitutions.\n");
    printf("5. ---[INCOMPLETE]--- Decryption of a message encrypted with a rotation cipher given cipher text only.\n");
    printf("6. ---[NOT AVAILABLE]--- Decryption of a message encrypted with a substitution cipher given cipher text only.\n");
    printf(" \n");

    //Following strings contains the alphabet, a place for a rotation substitution alphabet and a place for a substitution alphabet (generated later).
    char alphabet[27] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '\0'};
    char rotSubAB[27] = {0};        //"rotSubAB" = rotation substitution alphabet.
    char subAB[27] = {0};           //"subAB" = substitution alphabet.
    //The following string contains the 6 most common letters found in english texts.
    char commonLetters[6] = {'E', 'T', 'A', 'O', 'I', 'N'};
    //The following string is a place for the message input (to be allocated by text in File I/O).
    char msg[1023] = {};            //"msg" = message.
    //The following strings are places for all of the rotation cipher messages.
    char rotEncMsg[1023] = {};      //"rotEncMsg" = rotaton encryption message.
    char rotDecMsg[1023] = {};      //"rotDecMsg" = rotation decryption message.
    //The following strings are places for all  of the substitution cipher messages.
    char subEncMsg[1023] = {};      //"subEncMsg" = substitution encryption message.
    char subDecMsg[1023] = {};      //"subDecMsg" = substitution decryption message.
    
    int shift;                      //Declaring integer for storing selected rotation key (shift amount).
    
    FILE *decision;
    decision = fopen("decisions.txt", "r");
    if(decision == NULL) {
        perror("decision");
    }
    fscanf(decision, "%d %d", &task, &shift);      //Scanning input file for assigning task and shift variables.
    
    //Generating alphabets for both cipher methods at beginning
    rotSubAB[27] = RotationSubstitutionAlphabet(alphabet, rotSubAB, shift);
    subAB[27] = SubstitutionAlphabet(subAB);
    //The following lines contain the arrays for File I/O input.
    char rotEncMsgTest[1023] = {0};
    char subAlphabetTest[27] = {0};
    char subEncMsgTest[1023] = {0};
    //The following functions open each file and print an error if any return NULL
    FILE *testRotEncMsg;
    testRotEncMsg = fopen("testRotEncMsg.txt", "r");
    if(testRotEncMsg == NULL) {
        perror("testRotEncMsg");
    }
    FILE *testSubAlphabet;
    testSubAlphabet = fopen("testSubAlphabet.txt", "r");
    if(testSubAlphabet == NULL) {
        perror("testSubAlphabet");
    }
    FILE *filemessage;
    filemessage = fopen("filemessage.txt", "r");
    if(filemessage == NULL) {
        perror("testSubAlphabet");
    }
    FILE *testSubEncMsg;
    testSubEncMsg = fopen("testSubEncMsg.txt", "r");
    if(testSubEncMsg == NULL) {
        perror("testSubEncMsg");
    }

    //The following functions find seek to the end of the file to find it's size and seek back to the start so it can be read properly.
    fseek(testRotEncMsg, 0, SEEK_END);
    int tREMSize = ftell(testRotEncMsg) + 1;
    fseek(testRotEncMsg, 0, SEEK_SET);
    
    fseek(testSubAlphabet, 0, SEEK_END);
    int tSABSize = ftell(testSubAlphabet) + 1;
    fseek(testSubAlphabet, 0, SEEK_SET);
    
    fseek(filemessage, 0, SEEK_END);
    int fMSize = ftell(filemessage) + 1;
    fseek(filemessage, 0, SEEK_SET);
    
    fseek(testSubEncMsg, 0, SEEK_END);
    int tSEMSize = ftell(testSubEncMsg);
    fseek(testSubEncMsg, 0, SEEK_SET);
   
    //The following functions read each file and save their data to the previously seen arrays. 
    fgets(rotEncMsgTest, tREMSize, testRotEncMsg);
    fgets(subAlphabetTest, tSABSize, testSubAlphabet);
    fgets(msg, fMSize, filemessage);
    fgets(subEncMsgTest, tSEMSize, testSubEncMsg);
    
    //The following lines inform the user of which task they have selected by printing to the console.
    printf("Task %d selected:\n", task);
    printf(" \n");
    
    //Switch statement allows executes the appropriate code that relates to the users task selection input.
    switch(task)
    {
        case 1: rotEncMsg[1023] = RotationEncryption(msg, rotEncMsg, rotSubAB, alphabet);           //Calling rotation ecnryption function and saving return value to "rotEncMsg" string.
            printf("Rotation Cipher Encryption:\n");                                                //Printing relevant information on following lines.
            printf(" \n");
            printf("    Message: %s\n", msg);
            printf("    Rotation key: %d.\n", shift);
            printf("    Encryption: %s\n", rotEncMsg); break;
        case 2: rotDecMsg[1023] = RotationDecryption(rotEncMsgTest, rotDecMsg, rotSubAB, alphabet); //Calling rotation decryption function and saving return value to "rotDecMsg" string.
            printf("Rotation Cipher Decryption:\n");                                                //Printing relevant information on the following lines.
            printf(" \n");
            printf("    Encrypted Message: %s \n", rotEncMsgTest);
            printf("    Rotation key: %d.\n", shift);
            printf("    Decryption: %s\n", rotDecMsg); break;
        case 3: printf("Substitution Cipher Encryption: \n");
            printf(" \n");
            printf("Substitution Alphabet: %s\n", subAB);                                           //Printing substitution alphabet.
            printf("Alphabet:              %s\n", alphabet);
            printf(" \n");
            printf("Message:    %s \n", msg);
            subEncMsg[1023] = SubstitutionEncryption(msg, subAB, subEncMsg, alphabet);              //Calling substitution encryption function and saving return value to "subEncMsg" string.
            printf("Encryption: %s\n", subEncMsg); break;                                           //Printing relevant information.
        case 4: printf("Substitution Cipher Decryption: \n");
            printf(" \n");
            printf("Substitution Alphabet: %s\n", subAB);                                           //Printing substitution alphabet.
            printf("Alphabet:              %s\n", alphabet); 
            printf(" \n");
            printf("Encryption: %s \n", subEncMsgTest);
            subDecMsg[1023] = SubstitutionDecryption(subEncMsgTest, subAlphabetTest, subDecMsg, alphabet);    //Calling substitution decryption function and saving return value to "subDecMsg" string.
            printf("Decryption: %s \n", subDecMsg); break;
        case 5: printf("Encryption: %s\n", rotEncMsgTest);                                                    //Printing unseen message.
            printf(" \n");
            RotationDecryptionKeyless(rotEncMsgTest, alphabet, commonLetters); break;                         //Calling rotation decryption (keyless) function.
        case 6: printf("Sorry, option 6 is not yet available."); break;                                                                          
    }
    
    //The following functions close each file once the program has finished.
    fclose(testRotEncMsg);
    fclose(testSubAlphabet);
    fclose(decision);
    fclose(filemessage);
    fclose(testSubEncMsg);
    
}


/* Rotation Cipher Key:
 *      This function takes the shift amount and generates a substitution alphabet for the rotation cipher.
 *      The rotation substitution alphabet is returned to the string 'rotSubAB'.
 */

char RotationSubstitutionAlphabet(char *alphabet, char *rotSubAB, int shift) {
    int abIndex;                                                                  //Integer variable for storing alphabet index.
    for(abIndex = 0; abIndex < 26; abIndex++) {                                   //For loop for generating substitution characters for each index (0-25, representing A-Z).
        if((alphabet[abIndex] + shift) > 90) {                                    //If statement to check whether rotation shift goes beyond 'Z'.
            int difference = 90 - alphabet[abIndex];                              //Finding difference between 'Z' and letter being replaced
            int contShift = abs(shift - difference);                              //Finding shift beyond 'Z' (starting from 'A').
            rotSubAB[abIndex] = 64 + contShift;                                   //Adding remaining shift to letter at index in rotation substitution alphabet.
        }
        else {
        rotSubAB[abIndex] = alphabet[abIndex] + shift;                            //Adding shift to letter at index in rotation substitution alphabet.
        }
    }
    return *rotSubAB;                                                             //Returns rotation substitution alphabet to the string 'rotSubAB'.
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
                rotEncMsg[msgIndex] = rotSubAB[abIndex];                                 //Replaces character with corresponding substitution alphabet character.
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

char RotationDecryption(char *rotEncMsgTest, char *rotDecMsg, char *rotSubAB, char *alphabet) {
    int index, rotSubABIndex, rotEncMsgIndex, msgLen = 1023;                                   //Declaring indicies and initialising the length of the message (an arbitrary number).
    for(index = 0; index < msgLen; index++) {                                                  //For loop goes through each character to check if it is lower-case and converts any instances  
        if(rotEncMsgTest[index] > 96 && rotEncMsgTest[index] < 123) {                                  //... into upper-case letters.
            rotEncMsgTest[index] = rotEncMsgTest[index] - 32;
        }
    }
    for(rotEncMsgIndex = 0; rotEncMsgIndex < msgLen; rotEncMsgIndex++) {                       //For loop for rotation decryption. Goes through each character of the encrypted message.
           for(rotSubABIndex = 0; rotSubABIndex < 26; rotSubABIndex++) {                       //... For each encrypted message character, each character of rotation substitution alphabet is compared to later test if it matches.
               if(rotEncMsgTest[rotEncMsgIndex] < 65 || rotEncMsgTest[rotEncMsgIndex] > 90) {          //If statement checks if the letter is not within range of A-Z, keeping the value at any index
                   rotDecMsg[rotEncMsgIndex] = rotEncMsgTest[rotEncMsgIndex];                      //... where true.
               }
               else if(rotEncMsgTest[rotEncMsgIndex] == rotSubAB[rotSubABIndex]) {                 //Else If statement checks if encrypted message character matches rotation substitution alphabet character.
                   rotDecMsg[rotEncMsgIndex] = alphabet[rotSubABIndex];                        //... Where true, message character is replaced with corresponding rotation substitution alphabet character.
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
    int abIndex;                                    //Declaring Alphabet Index.
    bool check[100]={0};                            //Boolean array (size is arbitrary) to serve later for reference as to whether or not an index has been used.
    srand(time(NULL));                              //Generates a "random" seed based on computer's internal clock.
    for(abIndex = 0; abIndex < 26; ++abIndex) {     //For loop for generating the random positions for each letter.
        int rNum = rand() % (90 + 1 - 65) + 65;     //Generating a random integer between 90 and 65.
        if(!check[rNum]) {                          //If statement to check if alphabet position is not already taken, using that position where true. 
          subAB[abIndex] = rNum;
        }
        else {                                      //Else statement that sets index back by a value of 1 so the program can re-try a new postion for that letter.
            abIndex--;
        }
        check[rNum] = 1;                            //Sets the value at that index to 1, indicating that the position at this index is taken.
    }
    return *subAB;                                  //Returns the substitution alphabet is returned to the string 'subAB'.
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

char SubstitutionDecryption(char *subEncMsgTest,  char *subAlphabetTest, char *subDecMsg, char *alphabet) {
    int SubEncMsgIndex, subABIndex, msgLen = 1023;                                               //Declaring Substitution Encryption Message and Substitution Alphabet indices. Initialising Message Length.
    for(SubEncMsgIndex = 0; SubEncMsgIndex < msgLen; SubEncMsgIndex++) {                         
        if(subEncMsgTest[SubEncMsgIndex] > 96 && subEncMsgTest[SubEncMsgIndex] < 123) {                  
            subEncMsgTest[SubEncMsgIndex] = subEncMsgTest[SubEncMsgIndex] - 32;
        }
    }
    for(SubEncMsgIndex = 0; SubEncMsgIndex < msgLen; SubEncMsgIndex++) {                         //For loop for substitution decryption. Goes through each character of the encrypted message.
           for(subABIndex = 0; subABIndex < 26; subABIndex++) {                                  //... For each encrypted message character, each character of substitution alphabet is compared to later test if it matches.
               if(subEncMsgTest[SubEncMsgIndex] < 65 || subEncMsgTest[SubEncMsgIndex] > 90) {            //If statement checks if the letter is not within range of A-Z, keeping the value at any index where
                   subDecMsg[SubEncMsgIndex] = subEncMsgTest[SubEncMsgIndex];                        //... where true.
               }
               else if(subEncMsgTest[SubEncMsgIndex] == subAlphabetTest[subABIndex]) {                         //Else If statement checks if encrypted message character matches substitution alphabet character.
                   subDecMsg[SubEncMsgIndex] = alphabet[subABIndex];                             //... Where true, message character is replaced with substitution alphabet character.
               }
           }   
    }
       return *subDecMsg;                                                                        //Returns the message, decrypted by the substitution cipher, to the string 'subDecMsg'.
}
  
  
/* Rotation Decryption Keyless:
 *      This function takes a message encrypted by a rotation cipher and offers 6 possible decrypted
 *      messages for the user to interpret, based off of the 6 most common letters in the english language.
 *      ---[INCOMPLETE]-- Partially Working. There is a pattern to when it works and when it doesn't. Pressing run enough
 *      will achieve expected results (although these may not necessarily always be correct).
 *      Does not return a value to a char as it prints each attempt from the function.
 */
    
char RotationDecryptionKeyless(char *rotEncMsgTest, char *alphabet, char *commonLetters) {
    int REMIndex, ABIndex, occurIndex, commonOrder, lShift;                                   //Declaring indicies and local shift amount.
    int msgLen = 1023;                                                                        //Initialising message length.
    char commonLetter;                                                                        //Declaring variable for most common letter.
    int occurences[25] = {0};                                                                 //Integer array for number of occurences of each letter. 
    char tempRotSubAB[25] = {0};                                                              //Temporary rotation substitution alphabet, changes for every attempt.
    char tempRotDecMsg[1023] = {0};                                                           //Temporary rotation decryption message, changes for every attempt based on rotation alphabet changing.                           
    int greatest = occurences[0];                                                             //Integer describes greatest number of occurences of a letter.
    for(REMIndex = 0; REMIndex < msgLen; REMIndex++) {                                        //For loop goes through each character to check if it is lower-case and converts any instances 
        if(rotEncMsgTest[REMIndex] > 96 && rotEncMsgTest[REMIndex] < 123) {                   //... into upper-case letters. 
            rotEncMsgTest[REMIndex] = rotEncMsgTest[REMIndex] - 32;                                           
        }
    }
    for(REMIndex = 0; REMIndex < msgLen; REMIndex++) {                                        //For loop to count how many instances of each letter occur.
        for(ABIndex = 0; ABIndex < 26; ABIndex++) {
            if(rotEncMsgTest[REMIndex] == alphabet[ABIndex]) {                                //If statement to test each index for what letter is present (by comparing to the alphabet).
                occurences[ABIndex]++;                                                        //Saves value to 'occurences[25]' array.
            }
        }
    }
    for(commonOrder = 0; commonOrder < 6; commonOrder++) {                                    //For loop for each attempt (most common letter is replaced by the 6 most common (found in 'commonLetters[6]' array)).
        int attempt = commonOrder + 1;                                                        //Setting attempt number (for printing purposes only).
        for(occurIndex = 0; occurIndex < 26; occurIndex++) {                                  //For loop finds most common letter
            if(occurences[occurIndex] >= greatest) {                                          //... by comparing to the last in If statement.
                greatest = occurences[occurIndex];                                            //Overwrites greatest and commonLetter variables where If statement is true.
                commonLetter = alphabet[occurIndex];
            }
            else {                                                                            //Value remains where If statement is false.                                    
                greatest = greatest;
                commonLetter = commonLetter;
            }
        }
        lShift = abs(commonLetters[commonOrder] - commonLetter);                              //Finding shift amount based on most common letter in 'commonLetters[]' array.
        for(ABIndex = 0; ABIndex < 26; ABIndex++) {                                           //For loop generates temporary rotation substitution alphabet.
            if(alphabet[ABIndex] - lShift < 65) {                                             //If statement to fix error of shift going past boundary of A-Z.
                int difference = alphabet[ABIndex] - 64;
                int contShift = abs(lShift - difference);
                tempRotSubAB[ABIndex] = 90 - contShift;   
            }
            else {                                                                            //Else statement for normal case of using shift.
                tempRotSubAB[ABIndex] = alphabet[ABIndex] - lShift;
            }
        }
        for(REMIndex = 0; REMIndex < msgLen; REMIndex++) {                                    //For loop for applying temporary rotation substitution alphabet (for each attempt)
            for(ABIndex = 0; ABIndex < 26; ABIndex++) {                                       
                if(rotEncMsgTest[REMIndex] < 65 || rotEncMsgTest[REMIndex] > 90) {            //If statement for where rotation encryption message test is outside boundary of A-Z,
                    tempRotDecMsg[REMIndex] = rotEncMsgTest[REMIndex];                        //... to keep its value at that index the same.
                }
                else if(rotEncMsgTest[REMIndex] == alphabet[ABIndex]) {                       //Else If statement replaces each letter between A-Z with corresponding temporary rotation alphabet letter.
                    tempRotDecMsg[REMIndex] = tempRotSubAB[ABIndex];
                }
            }
        }
        printf("Attempt %d: \n", attempt);                                                    //Printing each attempt to console.
        printf("            %s \n", tempRotDecMsg);                                         
    }
    return 0;                                                                                 //Returning zero as each attempt was printed rather than returned.
}