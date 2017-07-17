/*
 * Created by Sotirios-Efstathios Maneas on 2017-01-02.
 */

#include <stdio.h>
#include <string.h>

#include "utils.h"


/*
 * Tokenize the string stored in cmd based on DELIMITERS as separators.
 * Return the number of tokens, and store pointers to them in cmd_argv.
 */
int tokenize(char *cmd, char **cmd_argv) {
	char *token;
	int i = 0;
	// Get the first token
	token = strtok(cmd, DELIMITERS);
	// Keep looping till we have all the tokens 
	while (token != NULL){
		// Store the pointers to token in cmd_argv
		cmd_argv[i] = token;
		// Increase the count by one and get rest of tokens
		i += 1;
		token = strtok(NULL, DELIMITERS);
	}
	// Return the number of tokens successfully stored
	return i;
}
