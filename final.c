/*
Microcontrollers Final

Nick Ek
Ethan Secakusuma
Liam Nasr

4/20/22
Version 0.1
    - DE10-Lite board hex values still TBA

Final Hangman Game

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "drawgame.h" // Drawing game functions
#include "address_map.h" // address map for DE10-Lite Board
#define MAXNUMWORDS 128
#define MAXWORDLENGTH 16


int main() {

    // Scanning in the word bank
    char randomword[MAXNUMWORDS][MAXWORDLENGTH];
    int wordsIn = 0;
    char in[16];

    FILE* pWords = fopen("words.txt", "r");

    while (fgets(in, 16, pWords)) {
        sscanf(in, "%s", randomword[wordsIn]);
        wordsIn++;

    }

    // Debugging if file can't open
    if(pWords == NULL){
        printf("Failed to open word bank\n");
        return 1;
    }

    fclose(pWords);

    // Index for random word
    srand(time(NULL)); // Setting random seed
    int randomIndex = rand() % wordsIn;
    int lengthOfWord = strlen(randomword[randomIndex]);

    // User data
    char letterEntered;
    int letterGuessed[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
    int numLives = 6;
    int numCorrect = 0;
    int currentCorrect = 0;
    int quit = 0;
    char guess[64];
    char previousGuess[26];

    /* volatile int* HEX_ptr = (int*)HEX3_HEX0_BASE; [TO BE TESTED]
    int hex0 = 0x0000003F;
    int hex1 = 0x00000006;
    int hex2 = 0x0000005B;
    int hex3 = 0x0000004F;
    int hex4 = 0x00000066;
    int hex5 = 0x0000006D;
    int hex6 = 0x0000007D;*/

    drawMenu(); // Calling draw menu function

    while (numCorrect < lengthOfWord) {

        // Printing the hidden
        printf("\tWord:");
        for(int i = 0; i < lengthOfWord; i++){
            if(letterGuessed[i] == 1){
                printf("%c", randomword[randomIndex][i]);
            }
            else{
                printf("_");
            }
        }
        printf("\n\n");
        printf("Guess a letter: ");
        fgets(guess, 16, stdin);
        letterEntered = guess[0];
        currentCorrect = numCorrect;


        // For loop checking each character in the word for a match
        for(int i = 0; i < lengthOfWord; i++){
            if(letterGuessed[i] == 1){
                continue;
            }
            if(letterEntered == randomword[randomIndex][i]){
                letterGuessed[i] = 1;
                numCorrect++;
            }
        }

        // Checking if wrong
        if(currentCorrect == numCorrect){
            numLives--;
            if(numLives == 0){
                break;
            }
        }

        // Quit function
        if (strncmp(guess, "quit", 4) == 0) {
            quit = 1;
            break;
        }

        // Drawing functions
        else if(numLives == 1) {
            //*(HEX_ptr) = hex1;
            drawGamePhase5();
        }
        else if(numLives == 2) {
            //*(HEX_ptr) = hex2;
            drawGamePhase4();
        }
        else if(numLives == 3) {
            //*(HEX_ptr) = hex3;
            drawGamePhase3();
        }
        else if(numLives == 4) {
            //*(HEX_ptr) = hex4;
            drawGamePhase2();
        }
        else if(numLives == 5) {
            //*(HEX_ptr) = hex5;
            drawGamePhase1();
        }
        else if(numLives == 6) {
            //*(HEX_ptr) = hex6;
            drawGamePhase0();
        }
    }
    if (quit == 1) {
        printf("\n\tThanks for playing!\n");
    }
    else if (numLives == 0){
        drawGamePhase6();
        printf("\tYou lose x(\n\tThe word was: %s\n", randomword[randomIndex]);
    }
    else{
        printf("\tWinner!!!\n\tThe word was: %s\n", randomword[randomIndex]);
    }
    return 0;
}


