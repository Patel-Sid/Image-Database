/*
 * Created by Sotirios-Efstathios Maneas on 2017-01-02.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"
#include "utils.h"

int main(void) {

        // char array to hold a line of input
	char buf[BUFFER_SIZE] = {'\0'};

        // char* array to hold the pointers to tokens
	char *args[INPUT_ARG_MAX_NUM];

        // the root of the tree
        struct TreeNode root;
        root.value = "";
        root.child = NULL;
        root.sibling = NULL;

	struct TreeNode *root_ptr = &root;

	int result = 0;
	while (fgets(buf, BUFFER_SIZE, stdin) != NULL){

		result = tokenize(buf,args);
		char cmd_arg = *(args[0]);

		// Insert a new image
		if (cmd_arg == 'i' && result == 5) {
			tree_insert(root_ptr, args);
		}
		// Ask the database to output the names of all files that match the attributes specified in the q command
		else if (cmd_arg == 'q' && result == 4) {
			tree_search(root_ptr, args);
		}
		// Ask the database to print all its contents organized by attribute values
		else if (cmd_arg == 'p' && result == 1) {
			tree_print(root_ptr);
		}
		// A command is invalid or the number of arguments is incorrect
		else {
			fprintf(stderr, "Invalid command.\n");
		}
	}
        return 0;
}
