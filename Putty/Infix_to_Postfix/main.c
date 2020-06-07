#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "queue.h"

//Prototypes
int invalidNotation(char[]);
void infixToPostfix(char[], stack_type*, queue_type*);
int evaluatePostfix(stack_type*, queue_type*);

stack_type nS;
queue_type nQ;


int main(void){
        char question[100];
        int evaluate;
        stack_type *stack = &nS;
        queue_type *queue = &nQ;

        stack = stack_new();
        queue = queue_new();


        printf("--Welcome to the Infix/Postfix Program--\n");

        //Validate notation
        do{
                printf("Enter a math problem: ");
                scanf("%[^\n]%*c", question);
        }while(invalidNotation(question));

        printf("Evaluating expression...\n");

        //Evaluate infix to postfix
        infixToPostfix(question, stack, queue);

        evaluate = evaluatePostfix(stack, queue);

        if(evaluate == -3000)
                printf("Integer Division Error!\n");
        else
                printf("The result of your problem is: %d\n", evaluate);

        printf("\nProgram Ending..\n");

        return 0;
}


int invalidNotation(char n[]){
        int invalid;    //true(1) means invalid, false(0) means valid
        int lParen = 0, rParen = 0;
        int i;

        for(i = 0; i < strlen(n); i++){
                //If the char is space
                if(n[i] == 32){
                        invalid = 0;
                }
                else if(n[i] == '*' || n[i] == '/' || n[i] == '+' || n[i] == '-'){
                        if(n[i+1] == '*' || n[i+1] == '/' || n[i+1] == '+' || n[i+1] == '-'){
                                printf("Invalid notation: Continuous Operator. Try again!\n");
                                invalid = 1;
                                break;
                        }
                        invalid = 0;
                }
                else if(n[i] >= '0' && n[i] <= '9'){
                        if(n[i+1] >= '0' && n[i+1] <= '9'){
                                printf("Invalid notation: Number must be singular digits. Try again!\n");
                                invalid = 1;
                                break;
                        }
                        invalid = 0;
                }
                else if(n[i] == '(' || n[i] == ')'){
                        continue;
                }
                else{
                        printf("Invalid notation. Try again!\n");
                        invalid = 1;
                        break;
                }
        }

        //Check whether parenthesis has mismatch
        int j;
        for(j = 0; j < strlen(n); j++){
                if(n[i] == '('){
                        lParen++;
                }
                else if(n[i] == ')'){
                        rParen++;
                }
        }

        //Parenthesis mismatch
        if(lParen != rParen){
                printf("Invalid notation: Parenthesis mismatch. Try again!\n");
                invalid = 1;
        }

        return invalid;
}


void infixToPostfix(char expression[], stack_type *s, queue_type *q){
        int i;

        for(i = 0; expression[i] != '\0'; i++){
                if(expression[i] == ' '){
                        continue;
                }
                else if(expression[i] >= '0' && expression[i] <= '9'){
                        queue_enqueue(q, expression[i]);
                }
                else if(expression[i] == '('){
                        stack_push(s, expression[i]);
                }
                else if(expression[i] == '*' || expression[i] == '/' || expression[i] == '+' || expression[i] == '-'){
                        if(stack_top(s) == 0){
                                stack_push(s, expression[i]);
                        }
                        else{
                                if(stack_top(s) == '*' || stack_top(s) == '/'){
                                        queue_enqueue(q, stack_pop(s));
                                }
                                else if(stack_top(s) == '+' || stack_top(s) == '-'){
                                        if(expression[i] == '+' || expression[i] == '-')
                                                queue_enqueue(q, stack_pop(s));
                                }

                                stack_push(s, expression[i]);
                        }
                }
                else if(expression[i] == ')'){
                        while(stack_top(s) != '(')
                                queue_enqueue(q, stack_pop(s));
                        stack_pop(s);
                }

                if(expression[i+1] == '\0'){
                        while(stack_top(s) != 0)
                                queue_enqueue(q, stack_pop(s));
                }
        }

}


int evaluatePostfix(stack_type *s, queue_type *q){
        int i;
        char temp, lOperator, rOperator;
        int idx = 0;
        int qSize = q->numOfElements;
        char value[10];

        for(i = 0; i < qSize;i++){
                temp = queue_dequeue(q);


                if(temp == '(' || (temp >= '0' && temp <= '9'))
                        stack_push(s,temp);

                if(temp < 48 || temp > 57){
                        if(stack_height(s) >= 2){
                                rOperator = stack_pop(s) - '0'; //Save the right operator
                                lOperator = stack_pop(s) - '0'; //Save the left operator
                        }
                        else if(stack_height(s) == 1){          //When stack height is one
                                rOperator = stack_pop(s) - '0'; //Save the right operator
                                idx-=1;
                                lOperator = value[idx];         //Save the value from the array to left operator
                        }
                        else if(stack_height(s) == 0){
                                rOperator = value[--idx];       //Save the value from the array to the right operator
                                lOperator = value[--idx];       //Save the value from the array to the left operator
                        }

                        //Perform Arithmetic operations
                        if(temp == '+'){
                                value[idx] = lOperator + rOperator;
                                idx++;
                        }
                        else if(temp == '-'){
                                value[idx] = lOperator - rOperator;
                                idx++;
                        }
                        else if(temp == '/'){
                                //Check if there is integer division
                                if(rOperator == 0)
                                        return -3000;
                                else{
                                        value[idx] = lOperator / rOperator;
                                        idx++;
                                }
                        }
                        else if(temp == '*'){
                                value[idx++] = lOperator * rOperator;
                                idx++;
                        }

                }

        }

        return value[0];

}
