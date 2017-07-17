/*
 * Created by Sotirios-Efstathios Maneas on 2017-01-02.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"


/**
 *  A helper function that allocates a new tree node.
 *
 *  @param value The entry's value. It represents either an attribute or a filename.
 *  @return A pointer to the newly allocated node.
 *  (for now it returns NULL, so the resultiler does not resultlain)
 */
struct TreeNode *allocate_node(const char *value) {
	struct TreeNode *t = malloc(sizeof(struct TreeNode));
	t->value = malloc(sizeof(value));
	strcpy(t->value, value);
	t->child = NULL;
	t->sibling = NULL;
	return t;
}

//Keep a running counter of attributes + filename
int count = 4;
void my_values(char **values, char **array) {
	// Decrement 
    for (int i = 0; i < count; i++){
		values[i] = array[i+1];
    }
    count--;
}

/**
 *  Insert a new image to a tree
 *
 *  @param tree A pointer to the root of the tree.
 *  @param values An array, whose first three members are the attribute values for
 *                the image and the last one is the filename
 */
void tree_insert(struct TreeNode *root, char **values) {
    if (count == 0) {
		return;
    }
    char *value = values[1];
    char *next_values[count-1];
    my_values(next_values, values);
    struct TreeNode *my_node, *parent;
    // If root has no child then assign the given value
    if (root->child == NULL) {
		root->child = allocate_node(value);
    }
    my_node = root->child;
    parent = root;
    while (strcmp(my_node->value, value) < 0 && my_node->sibling != NULL) {
        parent = my_node;
        my_node = my_node->sibling;
    }
    int result = strcmp(my_node->value, value);
    // Both the values are equal
    if (result == 0){
        my_node = my_node;
    } 
    // The user given query is greater than 
    else if (result < 0){
        my_node->sibling = allocate_node(value);
		my_node = my_node->sibling;
    } 
    // The user given query is less than 
    else if (result > 0){
    	// If we are at parent node without siblings
    	if (parent->child == my_node){
		    parent->child = allocate_node(value);
        	parent->child->sibling = my_node;
        	my_node = parent->child;
    	}
    	// If the node we need to insert is between two other nodes
    	else{
    		parent->sibling = allocate_node(value);
    		parent->sibling->sibling = my_node;
    		my_node = parent->sibling; 
    	}

    }
    tree_insert(my_node, next_values);
    count = 4;
}


/**
 *  Searches a tree to print all files with matching attribute values.
 *
 *  @param tree A pointer to the root of the tree.
 *  @param values An array of attribute values
 */
int j = 0;
// If we have a empty tree then print NULL
void tree_search(const struct TreeNode *root, char **values) {
	if (root->child == NULL && root->sibling == NULL && j == 0){
		printf("(NULL)");
		return;
	}
	else{
		j++;
		// Change the root so we do have "" value every time
		if(strcmp(root->value, "") == 0){
			root = root->child;
		}
		// Compare first attribute
		if(strcmp(root->value,values[1]) == 0){
			struct TreeNode *node, *next_node, *next_next_node;
			node = root->child;
			// Compare second attribute if it exists
			while(strcmp(node->value,values[2]) != 0){
				// The query is not in tree
				if(node->sibling == NULL){
					printf("%s\n", "(NULL)");
					return;
				}
				// The attribute is in the tree
				else{
					node = node->sibling;
				}
			}
			next_node = node->child;
			// Compare third attribute if it exists
			while(strcmp(next_node->value,values[3]) != 0){
				// The attribute is not in tree
				if(next_node->sibling == NULL){
					printf("%s\n", "(NULL)");
					return;
				}
				// The attribute is in the tree
				else{
					next_node = next_node->sibling;
				}
			}
			next_next_node = next_node->child;
			if(next_next_node->sibling == NULL){
				// Print the file name
				printf("%s\n", next_next_node->value);
			}
			// If there are more files (if leaf has siblings)
			// Then keep looking for more siblings and print all of them 
			else{
				// Keep looking till no more siblings are found
				while(next_next_node->sibling != NULL){
					printf("%s ", next_next_node->value);
					next_next_node = next_next_node->sibling;
				}
				printf("%s\n", next_next_node->value);
			}
		}
		// Recurse on the sibling if present
		else if (root->sibling != NULL){
			tree_search(root->sibling, values);
		}
		else{
			// The query is not in tree
			printf("%s\n", "(NULL)");
			return;
		}
	}
}

/**
* Helps print the tree to the standard output recursively.
*
* @param tree A point to the root of the tree.
* @param way The path of the tree from the root
*/
void helper_tree_print(const struct TreeNode *tree, char *way){
	// Get eneough memory for the previous path, the current value and the null 
	char *new_way = malloc(strlen(way) + strlen(tree->value) + 1);
	// Copy the current path and allocate it on the heap
	strcpy(new_way, way);
	// We want to make sure we don't print the first whitespace
	if (strlen(way) != 0){
		strcat(new_way, " ");
	}
	// Now finally add the current value so we keep track of the whole tree
	strcat(new_way, tree->value);
	// Recurse on the child pathway
	if(tree->child != NULL){
		helper_tree_print(tree->child, new_way);
	}
	else{
		printf("%s\n", new_way);
	}
	// Recurse on the sibling pathway
	if(tree->sibling != NULL){
		helper_tree_print(tree->sibling,way);
	}
}

/**
 *  Prints a resultlete tree to the standard output.
 *
 *  @param tree A pointer to the root of the tree.
 */

// Gloabl counter to keep track of root of tree
int i = 0;
void tree_print(const struct TreeNode *tree) {
	// If we have just the root 
	if (tree->child == NULL && tree->sibling == NULL && i == 0){
		printf("(NULL)");
		return;
	}
	else{
		i++;
		// Call the helper function since we have a full tree to print
		helper_tree_print(tree->child,"");
	}
}
