#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

stack_type nStack;

stack_type *stack_new(void){
        stack_type *newStack = &nStack;
        (*newStack).stack = (char* )calloc(10, sizeof(char));
        (*newStack).numOfElements = 0;
        (*newStack).topElement = 0;
        (*newStack).size = 10;

        return newStack;
}

int stack_push(stack_type *mStack, char newChar){
        int pushSuccess;
        mStack->topElement = newChar;

        //When the num of elements in the stack is 0
        if(mStack->numOfElements == 0){
                *((*mStack).stack) = newChar;
                (*mStack).numOfElements = 1;
                pushSuccess = 0;
        }
        else if(mStack->numOfElements < mStack->size){          //When the num of elements is within the size of stack
                //Move the elements of the stack
                int i;
                i = mStack->numOfElements;
                while(i > 0){
                        *((*mStack).stack + i) = *((*mStack).stack + i - 1);
                        i--;
                }

                *((*mStack).stack) = newChar;
                (*mStack).numOfElements++;
                pushSuccess = 0;
        }
        else if(mStack->numOfElements >=  mStack->size){        //When num of elements is greater than the size
                int i;
                mStack->size = mStack->size * 2;        //Double the size
                mStack->stack = (char *)realloc(mStack->stack, (mStack->size)*sizeof(char));

                //Move the elements of the stack
                i = mStack->numOfElements;
                while(i > 0){
                        *((*mStack).stack + i) = *((*mStack).stack + i - 1);
                        i--;
                }

                *((*mStack).stack) = newChar;
                (*mStack).numOfElements++;
                pushSuccess = 0;
        }
        else{
                pushSuccess = -1;
        }

        return pushSuccess;
}

int stack_height(stack_type *mStack){
        return (*mStack).numOfElements;
}

char stack_pop(stack_type *mStack){
        char charPopped = (*mStack).topElement;

        if(mStack->numOfElements == 0){
                fprintf(stderr, "%s","Error Stack Underflow!!");
        }

        //Move the elements of the stack
        int i = 0;
        while(i < mStack->numOfElements){
                *((*mStack).stack + i) = *((*mStack).stack + i + 1);
                i++;
        }

        mStack->numOfElements--;

        if(mStack->numOfElements == 0){
                (*mStack).topElement = 0;
        }
        else{
                mStack->topElement = *((*mStack).stack);
        }

        return charPopped;
}

char stack_top(stack_type *mStack){
        return mStack->topElement;
}

void stack_delete(stack_type *mStack){
        free(mStack);
}
