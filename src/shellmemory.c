// McGill University
// COMP 310 - ECSE 427
// Assignment 1: OS Shell
// Authors:
// Rambod Azimi - 260911967
// Cindy Irawan - 261132839

#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include <sys/stat.h>


struct memory_struct {
	char *var;
	char *value;
};

struct memory_struct shellmemory[1000];

// Helper functions
int match(char *model, char *var) {
	int i, len = strlen(var), matchCount = 0;
	for(i = 0; i < len; i++)
		if (*(model+i) == *(var+i)) matchCount++;
	if (matchCount == len)
		return 1;
	else
		return 0;
}

char *extract(char *model) {
	char token = '=';    // Look for this to find value
	char value[1000];  // Stores the extract value
	int i, j, len = strlen(model);
	for(i = 0; i < len && *(model+i) != token; i++); // Loop till we get there
	// Extract the value
	for(i = i+1, j = 0; i < len; i++, j++) value[j] =* (model+i);
	value[j] = '\0';
	return strdup(value);
}

// Shell memory functions
void mem_init() {

	int i;
	// Initializing all the shellmemory to "none"
	for(i = 0; i < 1000; i++) {		
		shellmemory[i].var = "none";
		shellmemory[i].value = "none";
	}
}

// Checks the shell memory for the variable and returns the value saved in the varibale 
int check_mem(char *variableName) {
	int i;
	for (i = 0; i < 1000; i++) { // Check all the contents of shell memory one by one
		if (strcmp(shellmemory[i].var, variableName) == 0) { // Success
			printf("%s\n", shellmemory[i].value); // Print the value associated to the variable
			return 0;
		}
	}
	// Failure
	printf("\n"); // Print an empty line in case the variable does not exist in the shell memory
	return 1;
}

// Another version of check_mem function
int check_mem2(char *variableName) {
	int i;
	for (i = 0; i < 1000; i++) { // Check all the contents of shell memory one by one
		if (strcmp(shellmemory[i].var, variableName) == 0) { // Success
			mkdir(shellmemory[i].value, 0777); // Create a new directory with the specified name in the current folder
			return 0;
		}
	}
	// Failure
	printf("%s\n", "Bad command: my_mkdir");
	return 1;
}

// Set key value pair (single alphanumeric token)
void mem_set_value(char *var_in, char *value_in) {
	int i;
	for (i = 0; i < 1000; i++) {
		if (strcmp(shellmemory[i].var, var_in) == 0) {
			shellmemory[i].value = strdup(value_in);
			return;
		} 
	}
	// Value does not exist, need to find a free spot.
	for (i = 0; i < 1000; i++) {
		if (strcmp(shellmemory[i].var, "none") == 0) {
			shellmemory[i].var = strdup(var_in);
			shellmemory[i].value = strdup(value_in);
			return;
		} 
	}
	return;
}

// Enhanced version of mem_set_value function which supports values up to 5 alphanumeric tokens
void mem_set_value_enhanced(char *var_in, char value_in[]) {
	int i;
	for (i = 0; i < 1000; i++) {
		if (strcmp(shellmemory[i].var, var_in) == 0) {
			shellmemory[i].value = strdup(value_in);
			return;
		} 
	}
	// Value does not exist, need to find a free spot.
	for (i = 0; i < 1000; i++) {
		if (strcmp(shellmemory[i].var, "none") == 0) {
			shellmemory[i].var = strdup(var_in);
			shellmemory[i].value = strdup(value_in);
			return;
		} 
	}
	return;
}

// Get value based on input key
char *mem_get_value(char *var_in) {
	int i;

	for (i = 0; i < 1000; i++){
		if (strcmp(shellmemory[i].var, var_in) == 0) {

			return strdup(shellmemory[i].value);
		} 
	}
	return "Variable does not exist";

}