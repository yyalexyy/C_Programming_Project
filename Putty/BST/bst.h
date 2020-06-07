typedef struct BST_type bst;

/* creates an empty BST*/
int bst_create(bst **newTree);

/* insert the string value[] into the bst
 return true if successful;
 return false if the string already exists in the tree
*/
int bst_insert(bst **theTree, char *value);

/* find a particular string in the tree.
 return true if it is found;
 return false if it does not exist in the tree.
*/
int bst_find(bst **theTree, char *value);

/* remove a particular string from the tree.
 return true if it is found (and deleted);
 return false if it was never in the tree;
*/
int bst_remove(bst **theTree, char *value);

/* print out the bst in a format that will allow
 you to determine if it was built correctly.
 using a queue and breadth-first traversal with
 a newline at each new level is one approach;
 printing all the nodes in a detph-first traversal
 but labelling each node with its depth is another
 possibility.  There are others.  Choose one.
*/
void bst_display(bst **theTree);

/* destroy the tree and free up all memory*/
int bst_destroy(bst **theTree);
