// McGill University
// COMP 310 - ECSE 427
// Assignment 1: OS Shell
// Authors:
// Rambod Azimi - 260911967
// Cindy Irawan - 261132839

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
//#include <unistd.h>
#include "interpreter.h"
#include "shellmemory.h"

int MAX_USER_INPUT = 1000;
int parseInput(char ui[]);

// Start of everything
int main(int argc, char *argv[]) {

    // Welcoming message to the user
	printf("%s\n", "Shell version 1.2 Created February 2023");

    // Calling help function in the interpreter.c which displays all the commands
	help();

	char prompt = '$';  				// Shell prompt
	char userInput[MAX_USER_INPUT];		// User's input stored here
	int errorCode = 0;					// Zero means no error, default

	// Initializing user's input to '\0' character
	for (int i = 0; i < MAX_USER_INPUT; i++)
		userInput[i] = '\0';
	
	// Init the whole shell memory to "none" by calling mem_init function in the shellmemory.c
	mem_init();
	while(1) {							
		printf("%c ", prompt);
        // Here you should check the unistd library 
        // So that you can find a way to not display $ in the batch mode
		fgets(userInput, MAX_USER_INPUT - 1, stdin); // Get an string input from the user and save it into userInput array
		errorCode = parseInput(userInput); // Calls parseInput function below
		if (errorCode == -1) exit(99);	// Ignore all other errors
		memset(userInput, 0, sizeof(userInput)); // Copies char 0 (NULL) to the first n (size of userInput) characters of userInput (Basically clears the userInput)
	}

	return 0;

}

// checks for the error code and calls interpreter function in interpreter.c
int parseInput(char ui[]) { // ui is userInput
    char tmp[200];
    char *words[100];                            
    int a = 0;
    int b;                            
    int w = 0; // wordID (number of words in userInput)  
    int errorCode;
    for(a = 0; ui[a]==' ' && a < 1000; a++);        // Skip white spaces
    while(ui[a] != '\n' && ui[a] != '\0' && a < 1000) {
        for(b = 0; ui[a] != ';' && ui[a] != '\0' && ui[a] != '\n' && ui[a] != ' ' && a < 1000; a++, b++) {
            tmp[b] = ui[a];                        
            // Extract a word
        }
        tmp[b] = '\0'; // Insert '\0' at the end of tmp
        words[w] = strdup(tmp); // Make duplicate and save it into words
        w++;
        if(ui[a] == '\0') break; // If the entire command (userInput) is finished, break from the while loop
        a++; 
    }
    errorCode = interpreter(words, w); // In interpreter.c
    return errorCode;
}
