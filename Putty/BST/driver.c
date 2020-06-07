#include <stdio.h>
#include "bst.h"

int main(void){

        bst *root;
        int successfulCreate, successfulInsert, successfulFind, successfulDelete, successfulDestroy;

        printf("\n-----Binary Search Tree-----\n");

        printf("Creating a Binary Search Tree...\n");
        successfulCreate = bst_create(&root);
        if(successfulCreate == 1)
                printf("BST Created Successfully\n");
        else
                printf("BST Create Unsuccessful...\n");


        printf("\n---First Insert: Insert Maryland\n");
        successfulInsert = bst_insert(&root, "Maryland");
        if(successfulInsert == 1)
                printf("BST Insert Successfully\n");
        else
                printf("BST Insert Unscuccessfully, the value is already in the tree!\n");

        printf("\n---Second Insert: Insert Hawaii\n");
        successfulInsert = bst_insert(&root, "Hawaii");
        if(successfulInsert == 1)
                printf("BST Insert Successfully\n");
        else
                printf("BST Insert Unscuccessfully, the value is already in the tree!\n");


        printf("\n---Third Insert: Insert Pennsylvania\n");
        successfulInsert = bst_insert(&root, "Pennsylvania");
        if(successfulInsert == 1)
                printf("BST Insert Successfully\n");
        else
                printf("BST Insert Unscuccessfully, the value is already in the tree!\n");

        printf("\n---Fourth Insert: Insert Hawaii\n");
        successfulInsert = bst_insert(&root, "Hawaii");
        if(successfulInsert == 1)
                printf("BST Insert Successfully\n");
        else
                printf("BST Insert Unscuccessfully, the value is already in the tree!\n");


        printf("\nDISPLAY the current tree:\n");
        bst_display(&root);
        printf("\n");

        /*Find the value Pennsylvania*/
        printf("Find Pennsylvania in the tree: ");
        successfulFind = bst_find(&root, "Pennsylvania");
        if(successfulFind == 1)
                printf("BST Find Successfully!!\n");
        else
                printf("BST Find Unscuccessful...\n");


        printf("\n---Fifth Insert: Insert New York\n");
        successfulInsert = bst_insert(&root, "New York");
        if(successfulInsert == 1)
                printf("BST Insert Successfully\n");
        else
                printf("BST Insert Unscuccessfully, the value is already in the tree!\n");


        printf("\n---Sixth Insert: California\n");
        successfulInsert = bst_insert(&root, "California");
        if(successfulInsert == 1)
                printf("BST Insert Successfully\n");
        else
                printf("BST Insert Unscuccessfully, the value is already in the tree!\n");

        printf("\n---Seventh Insert: Insert Kentucky\n");
        successfulInsert = bst_insert(&root, "Kentucky");
        if(successfulInsert == 1)
                printf("BST Insert Successfully\n");
        else
                printf("BST Insert Unscuccessfully, the value is already in the tree!\n");

        /*Find the value Washington*/
        printf("\nFind Washington in the tree: ");
        successfulFind = bst_find(&root, "Washington");
        if(successfulFind == 1)
                printf("BST Find Successfully!!\n");
        else
                printf("BST Find Unscuccessful...\n");


        printf("\n---Eighth Insert: Insert Indiana\n");
        successfulInsert = bst_insert(&root, "Indiana");
        if(successfulInsert == 1)
                printf("BST Insert Successfully\n");
        else
                printf("BST Insert Unscuccessfully, the value is already in the tree!\n");


        printf("\n---Ninth Insert: Insert Puerto Rico\n");
        successfulInsert = bst_insert(&root, "Puerto Rico");
        if(successfulInsert == 1)
                printf("BST Insert Successfully\n");
        else
                printf("BST Insert Unscuccessfully, the value is already in the tree!\n");

        /*Find the value Puerto Rico*/
        printf("\nFind Puerto Rico in the tree: ");
        successfulFind = bst_find(&root, "Puerto Rico");
        if(successfulFind == 1)
                printf("BST Find Successfully!!\n");
        else
                printf("BST Find Unscuccessful...\n");

        /*Display the tree*/
        printf("\nDISPLAY the current tree:\n");
        bst_display(&root);
        printf("\n");


        /*Remove Puerto Rico*/
        printf("\nDelete Puerto Rico\n");
        successfulDelete = bst_remove(&root, "Puerto Rico");
        if(successfulDelete == 1)
                printf("BST Remove Successfully\n");
        else
                printf("BST Remove Unscuccessfully, the value is not in the tree!\n");

        /*Find the value Puerto Rico*/
        printf("\nFind Puerto Rico in the tree: ");
        successfulFind = bst_find(&root, "Puerto Rico");
        if(successfulFind == 1)
                printf("BST Find Successfully!!\n");
        else
                printf("BST Find Unscuccessful...\n");


        printf("\n---Tenth Insert: Insert Arizona\n");
        successfulInsert = bst_insert(&root, "Arizona");
        if(successfulInsert == 1)
                printf("BST Insert Successfully\n");
        else
                printf("BST Insert Unscuccessfully, the value is already in the tree!\n");

        printf("\n---Eleventh Insert: Insert Alabama\n");
        successfulInsert = bst_insert(&root, "Alabama");
        if(successfulInsert == 1)
                printf("BST Insert Successfully\n");
        else
                printf("BST Insert Unscuccessfully, the value is already in the tree!\n");

        printf("\n---Twelveth Insert: Insert Arkansas\n");
        successfulInsert = bst_insert(&root, "Arkansas");
        if(successfulInsert == 1)
                printf("BST Insert Successfully\n");
        else
                printf("BST Insert Unscuccessfully, the value is already in the tree!\n");

        printf("\n---Thirteenth Insert: Insert Maine\n");
        successfulInsert = bst_insert(&root, "Maine");
        if(successfulInsert == 1)
                printf("BST Insert Successfully\n");
        else
                printf("BST Insert Unscuccessfully, the value is already in the tree!\n");

        printf("\n---Fourteenth Insert: Insert Louisiana\n");
        successfulInsert = bst_insert(&root, "Louisiana");
        if(successfulInsert == 1)
                printf("BST Insert Successfully\n");
        else
                printf("BST Insert Unscuccessfully, the value is already in the tree!\n");

        printf("\n---Fifteenth Insert: Insert Texas\n");
        successfulInsert = bst_insert(&root, "Texas");
        if(successfulInsert == 1)
                printf("BST Insert Successfully\n");
        else
                printf("BST Insert Unscuccessfully, the value is already in the tree!\n");

        printf("\n---Sixteenth Insert: Insert Washington\n");
        successfulInsert = bst_insert(&root, "Washington");
        if(successfulInsert == 1)
                printf("BST Insert Successfully\n");
        else
                printf("BST Insert Unscuccessfully, the value is already in the tree!\n");

        /*Display the tree*/
        printf("\nDISPLAY the current tree:\n");
        bst_display(&root);
        printf("\n");


        /*Find the value New York*/
        printf("\nFind New York in the tree: ");
        successfulFind = bst_find(&root, "New York");
        if(successfulFind == 1)
                printf("BST Find Successfully!!\n");
        else
                printf("BST Find Unscuccessful...\n");

        /*Find the value Arkansas*/
        printf("\nFind Arkansas in the tree: ");
        successfulFind = bst_find(&root, "Arkansas");
        if(successfulFind == 1)
                printf("BST Find Successfully!!\n");
        else
                printf("BST Find Unscuccessful...\n");

        /*Remove Arkansas*/
        printf("\nDelete Arkansas\n");
        successfulDelete = bst_remove(&root, "Arkansas");
        if(successfulDelete == 1)
                printf("BST Remove Successfully\n");
        else
                printf("BST Remove Unscuccessfully, the value is not in the tree!\n");

        /*Display the tree*/
        printf("\nDISPLAY the current tree:\n");
        bst_display(&root);
        printf("\n");


        /*Remove Texas*/
        printf("\nDelete Texas\n");
        successfulDelete = bst_remove(&root, "Texas");
        if(successfulDelete == 1)
                printf("BST Remove Successfully\n");
        else
                printf("BST Remove Unscuccessfully, the value is not in the tree!\n");

        /*Display the tree*/
        printf("\nDISPLAY the current tree:\n");
        bst_display(&root);
        printf("\n");


        /*Remove Maryland*/
        printf("\nDelete Maryland\n");
        successfulDelete = bst_remove(&root, "Maryland");
        if(successfulDelete == 1)
                printf("BST Remove Successfully\n");
        else
                printf("BST Remove Unscuccessfully, the value is not in the tree!\n");

        /*Display the tree*/
        printf("\nDISPLAY the current tree:\n");
        bst_display(&root);
        printf("\n");


        /*Destroying the tree*/
        printf("Destorying the tree and freeing up the memory...\n");
        successfulDestroy = bst_destroy(&root);
        if(successfulDestroy == 1)
                printf("BST Destroy Successfully\n");
        else
                printf("BST Destroy Unscuccessfully...\n");

        /*Display the tree*/
        printf("\nDISPLAY the current tree:\n");
        bst_display(&root);


        printf("\nProgram Ending...\n");

        return 0;
}
