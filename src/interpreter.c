// McGill University
// COMP 310 - ECSE 427
// Assignment 1: OS Shell
// Authors:
// Rambod Azimi - 260911967
// Cindy Irawan - 261132839

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <unistd.h>
#include "shellmemory.h"
#include "shell.h"

int MAX_ARGS_SIZE = 10; // Increase it for now...

int badcommand() {
	printf("%s\n", "Unknown Command");
	return 1;
}

int badcommand_my_cd() {
	printf("%s\n", "Bad command: my_cd");
}

int badcommand_tooManyTokens() {
	printf("%s\n", "Bad command: Too many tokens");
	return 1;
}

// For run command only
int badcommandFileDoesNotExist() {
	printf("%s\n", "Bad command: File not found");
	return 3;
}

// Function prototypes
int help();
int quit();
int set(char* var, char* value);
int enhancedSet2(char* var, char* value1, char* value2);
int enhancedSet3(char* var, char* value1, char* value2, char* value3);
int enhancedSet4(char* var, char* value1, char* value2, char* value3, char* value4);
int enhancedSet5(char* var, char* value1, char* value2, char* value3, char* value4, char* value5);
int print(char* var);
int run(char* script);
int badcommandFileDoesNotExist();

// Interpret commands and their arguments
int interpreter(char* command_args[], int args_size) {
	int i;

	// If the userInput has 0 word or more than 3 words, display error
	if (args_size < 1 || args_size > MAX_ARGS_SIZE) {
		return badcommand();
	}

	for (i = 0; i < args_size; i++){ // Strip spaces new line etc
		command_args[i][strcspn(command_args[i], "\r\n")] = 0;
	}

	if (strcmp(command_args[0], "help") == 0) {
	    // help
	    if (args_size != 1) return badcommand();
	    return help();
	
	} else if (strcmp(command_args[0], "quit") == 0) {
		// quit
		if (args_size != 1) return badcommand();
		return quit();

	} else if (strcmp(command_args[0], "set") == 0) {
		//set
		if (args_size < 3) return badcommand(); 
		if (args_size > 7) return badcommand_tooManyTokens(); // If more than 5 tokens passed, display too many tokens error message
		if (args_size == 3) { // Single alphanumeric token
			return set(command_args[1], command_args[2]);
		} else if (args_size == 4) { // 2 alphanumeric tokens
			return enhancedSet2(command_args[1], command_args[2], command_args[3]);
		} else if (args_size == 5) { // 3 alphanumeric tokens
			return enhancedSet3(command_args[1], command_args[2], command_args[3], command_args[4]);
		} else if (args_size == 6) { // 4 alphanumeric tokens
			return enhancedSet4(command_args[1], command_args[2], command_args[3], command_args[4], command_args[5]);
		} else if (args_size == 7) { // 5 alphanumeric tokens
			return enhancedSet5(command_args[1], command_args[2], command_args[3], command_args[4], command_args[5], command_args[6]);
		}
	
	} else if (strcmp(command_args[0], "print") == 0) {
		if (args_size != 2) return badcommand();
		return print(command_args[1]);
	
	} else if (strcmp(command_args[0], "run") == 0) {
		if (args_size != 2) return badcommand();
		return run(command_args[1]);
	
	} else if (strcmp(command_args[0], "my_touch") == 0) {
		if (args_size != 2) return badcommand(); // Command looks like: my_touch filename (single alphanumeric token for the name)
		return touch(command_args[1]);
	} else if (strcmp(command_args[0], "my_cd") == 0) {
		if (args_size != 2) return badcommand(); // Command looks like: my_cd dirname (single alphanumeric token for the name)
		return cd(command_args[1]);
	} else return badcommand();
}

int cd(char* dirName) {
// Check to see if there is a directory called "dirName" inside the current directory
char s[100];
char *slash = "/";
char* currentPath = getcwd(s, sizeof(s)); // Get the current directory path using getcwd function in unistd library
char destinationPath[1000];
strcpy(destinationPath, currentPath);
strcat(destinationPath, slash); // Adding /
strcat(destinationPath, dirName); // Destination path = CurrentPath/DirectoryName

int errorCode = chdir(destinationPath); // Change the directory
if (errorCode != 0) { 
	// error if the directory does not exist
	return badcommand_my_cd();
}
return 0;
}

int touch(char* fileName) {
	FILE *fp;
	fp = fopen(fileName, "w"); // Create an empty file in the current directory
	return 0;
}

// Help command which displays all the commands
int help() {

	char help_string[] = "COMMAND			DESCRIPTION\n \
help			Displays all the commands\n \
quit			Exits / terminates the shell with “Bye!”\n \
set VAR STRING		Assigns a value to shell memory\n \
print VAR		Displays the STRING assigned to VAR\n \
echo STRING		Displays an alphanumeric STRING\n \
echo $VAR		Displays the value assigned to VAR\n \
my_ls			Lists all the files in the current directory\n \
my_mkdir DIRNAME	Creates a new directory with the name DIRNAME\n \
my_touch FILENAME	Creates a new empty file with the name FILENAME\n \
my_cd DIRNAME		Changes current directory to the directory DIRNAME\n \
run SCRIPT.TXT		Executes the file SCRIPT.TXT\n ";
	printf("%s\n", help_string);
	return 0;
}

// Terminate the shell with Bye!
int quit() {
	printf("%s\n", "Bye!");
	exit(0);
}

int set(char* var, char* value) {
	char *link = "=";
	char buffer[1000];
	strcpy(buffer, var);
	strcat(buffer, link);
	strcat(buffer, value);

	mem_set_value(var, value);

	return 0;
}

// set command with 2 alphanumeric tokens
int enhancedSet2(char* var, char* value1, char* value2) {
	char *link = "=";
	char *space = " ";
	char buffer[1000];
	char buffer2[1000];
	strcpy(buffer, var);
	strcat(buffer, link);
	strcat(buffer, value1);
	strcat(buffer, space);
	strcat(buffer, value2);

	strcpy(buffer2, value1);
	strcat(buffer2, space);
	strcat(buffer2, value2);

	mem_set_value_enhanced(var, buffer2);

	return 0;
}

// set command with 3 alphanumeric tokens
int enhancedSet3(char* var, char* value1, char* value2, char* value3) {
	char *link = "=";
	char *space = " ";
	char buffer[1000];
	char buffer2[1000];
	strcpy(buffer, var);
	strcat(buffer, link);
	strcat(buffer, value1);
	strcat(buffer, space);
	strcat(buffer, value2);
	strcat(buffer, space);
	strcat(buffer, value3);

	strcpy(buffer2, value1);
	strcat(buffer2, space);
	strcat(buffer2, value2);
	strcat(buffer2, space);
	strcat(buffer2, value3);

	mem_set_value_enhanced(var, buffer2);
	return 0;
}

// set command with 4 alphanumeric tokens
int enhancedSet4(char* var, char* value1, char* value2, char* value3, char* value4) {
	char *link = "=";
	char *space = " ";
	char buffer[1000];
	char buffer2[1000];
	strcpy(buffer, var);
	strcat(buffer, link);
	strcat(buffer, value1);
	strcat(buffer, space);
	strcat(buffer, value2);
	strcat(buffer, space);
	strcat(buffer, value3);
	strcat(buffer, space);
	strcat(buffer, value4);

	strcpy(buffer2, value1);
	strcat(buffer2, space);
	strcat(buffer2, value2);
	strcat(buffer2, space);
	strcat(buffer2, value3);
	strcat(buffer2, space);
	strcat(buffer2, value4);

	mem_set_value_enhanced(var, buffer2);
	return 0;
}

// set command with 5 alphanumeric tokens
int enhancedSet5(char* var, char* value1, char* value2, char* value3, char* value4, char* value5) {
	char *link = "=";
	char *space = " ";
	char buffer[1000];
	char buffer2[1000];
	strcpy(buffer, var);
	strcat(buffer, link);
	strcat(buffer, value1);
	strcat(buffer, space);
	strcat(buffer, value2);
	strcat(buffer, space);
	strcat(buffer, value3);
	strcat(buffer, space);
	strcat(buffer, value4);
	strcat(buffer, space);
	strcat(buffer, value5);

	strcpy(buffer2, value1);
	strcat(buffer2, space);
	strcat(buffer2, value2);
	strcat(buffer2, space);
	strcat(buffer2, value3);
	strcat(buffer2, space);
	strcat(buffer2, value4);
	strcat(buffer2, space);
	strcat(buffer2, value5);

	mem_set_value_enhanced(var, buffer2);
	return 0;
}

int print(char* var) {
	printf("%s\n", mem_get_value(var)); 
	return 0;
}

int run(char* script) {
	int errCode = 0;
	char line[1000];
	FILE *p = fopen(script, "rt");  // The program is in a file

	if(p == NULL){
		return badcommandFileDoesNotExist();
	}

	fgets(line, 999, p);
	while(1) {
		errCode = parseInput(line);	// Which calls interpreter()
		memset(line, 0, sizeof(line));

		if(feof(p)) {
			break;
		}
		fgets(line, 999, p);
	}

    fclose(p);

	return errCode;
}
