#include "bst.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

struct BST_type{
        struct BST_type *left_child;
        struct BST_type *right_child;
        char* data;
        int level;
};

static int successfulInsert;
static int successfulDelete = 1;

int bst_create(bst **newTree){
        *newTree = NULL;
        return 1;
}

/*Helper function to insert a node recursively*/
int recursive_insert(bst **theTree, char *value, int level){
        /*Base Case*/
        if((*theTree) == NULL){
                (*theTree) = (bst *) malloc(sizeof(bst));
                (*theTree)->data = value;
                (*theTree)->level = level;
                return 1;
        }
        else if(strcmp(value, (*theTree)->data) > 0){           /*When value is greater than data*/
                successfulInsert = recursive_insert(&((*theTree)->right_child), value, level+1);
        }
        else if(strcmp(value, (*theTree)->data) < 0){           /*When value is smaller than data*/
                successfulInsert = recursive_insert(&((*theTree)->left_child), value, level+1);
        }
        else{
                return 0;
        }

        return successfulInsert;
}

int bst_insert(bst **theTree, char *value){
        return recursive_insert(theTree, value, 0);             /*Calling a helper function*/
}

int bst_find(bst **theTree, char *value){
        bst *rootNode;
        bool found = false;
        rootNode = *theTree;

        if(*theTree == NULL){
                return 0;
        }

        /*When value does not match the data in the node*/
        while(found == false){
                if(strcmp(value, (*theTree)->data) == 0){               /*When value matches the tree's node data*/
                        *theTree = rootNode;    /*Points to the root node*/
                        found = true;
                        return 1;
                }
                else if(strcmp(value, (*theTree)->data) < 0){           /*When value is smaller than data*/
                        if((*theTree)->left_child == NULL){
                                *theTree = rootNode;
                                return 0;
                        }
                        else{
                                (*theTree) = (*theTree)->left_child;
                        }
                }
                else if(strcmp(value, (*theTree)->data) > 0){           /*When value is greater than data*/
                        if((*theTree)->right_child == NULL){
                                *theTree = rootNode;
                                return 0;
                        }
                        else{
                                (*theTree) = (*theTree)->right_child;
                        }
                }
        }

        *theTree = rootNode;
        return 0;
}

/*Find the minimum for the data to be replaced*/
bst* find_min(bst **tree){
        if((*tree) == NULL)
                return NULL;
        else if((*tree)->right_child != NULL)           /*node that is the min value wont have right child*/
                return find_min(&(*tree)->right_child);         /*rightmost element will be the minimum*/
        return *tree;
}

/*Helper function to remove a node recursively*/
bst * recursive_remove(bst **root, char *value){
        bst *temp;

        /*Search for data to be deleted*/
        if(*root == NULL){
                successfulDelete = 0;
                return NULL;
        }
        if(strcmp(value, (*root)->data) > 0){
                (*root)->right_child = recursive_remove(&((*root)->right_child), value);
        }
        else if(strcmp(value, (*root)->data) < 0){
                (*root)->left_child = recursive_remove(&((*root)->left_child), value);
        }
        else{
                if((*root)->left_child == NULL && (*root)->right_child == NULL){                        /*No Children*/
                        free(*root);
                        successfulDelete = 1;
                        return NULL;
                }
                else if((*root)->left_child == NULL || (*root)->right_child == NULL){                   /*One Children*/
                        if((*root)->left_child == NULL)
                                temp = (*root)->right_child;
                        else
                                temp = (*root)->left_child;

                        free(*root);
                        successfulDelete = 1;
                        return temp;
                }
                else{                                                                                   /*Two Children*/
                        temp = find_min(&((*root)->left_child));
                        (*root)->data = temp->data;
                        (*root)->left_child = recursive_remove(&((*root)->left_child), temp->data);
                        successfulDelete = 1;
                }
        }

        return *root;
}

int bst_remove(bst **theTree, char *value){
        recursive_remove(theTree, value);       /*Calling a helper function*/
        return successfulDelete;
}

void recursive_display(bst **tree, int level){
        /*Display inorder traversal*/
        if(*tree != NULL){
                recursive_display(&((*tree)->left_child), level+1);
                printf("Level %d node is %s \n", level, (*tree)->data);
                recursive_display(&((*tree)->right_child), level+1);
        }
}

void bst_display(bst **theTree){
        printf("(Inorder Traversal)\n");

        if((*theTree) == NULL)
                printf("Binary Tree is Empty!\n");
        else
                recursive_display(theTree, 0);
}

int bst_destroy(bst **theTree){
        if((*theTree) != NULL){
                bst_destroy(&(*theTree)->left_child);
                bst_destroy(&(*theTree)->right_child);
                free(*theTree);                 /*Free the memory*/
                (*theTree) = NULL;              /*Set the reference pointer to NULL*/
        }
        else
                return 0;

        return 1;
}
