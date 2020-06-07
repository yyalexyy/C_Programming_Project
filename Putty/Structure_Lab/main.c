#include <stdio.h>
#include "Rational.h"

int greatCommonDenom(int, int);

Rational_Type simplify(Rational_Type);

int main(){

        int  numer1, denom1, numer2, denom2, menuNum;
        Rational_Type A, B, add, subtract1, subtract2, multiply, division1, division2;

        printf("\n-----Rational Number Calculator-----\n");
        printf("Enter the numerator value of the first rational number: ");
        scanf("%d", &numer1);
        printf("Enter the denominator value of the first rational number: ");
        scanf("%d", &denom1);
        /*Validate denominator*/
        while(denom1 == 0){
                printf("Invalid denominator. Re-enter a valid denominator for the first rational number: ");
                scanf("%d", &denom1);
        }

        A = make_Rational(numer1, denom1);

        printf("Enter the numerator value of the second rational number: ");
        scanf("%d", &numer2);
        printf("Enter the denominator value of the second rational numver: ");
        scanf("%d", &denom2);
        /*Validate denominator*/
        while(denom2 == 0){
                printf("Invalid denominator. Re-enter a valid denominator for the second rational number: ");
                scanf("%d", &denom2);
        }

        B = make_Rational(numer2, denom2);

                /*Display both rational numbers*/
                printf("\nYour numbers: A = ");
                display(A);
                printf(", B = ");
                display(B);

        do {
                printf("\n\nCalculation Menu: \n1. A + B \n2. A - B \n3. B - A \n4. A * B \n5. A / B \n6. B / A \n7. 1 / A (inverse of A) \n8. 1 / B (inverse of B) \n9. <Exit> \nEnter the number corresponding to the calculation you want: ");
                scanf("%d", &menuNum);
                /*Validate whether the user has entered a choice within the menu*/
                while(menuNum < 1 || menuNum > 9){
                        printf("Invalid choice. Re-enter your choice: ");
                        scanf("%d", &menuNum);
                }

                /*All the math operations*/
                switch(menuNum){
                        case 1:
                                add = addition(A, B);
                                printf("A + B = ");
                                display(simplify(add));
                                break;
                        case 2:
                                subtract1 = subtraction(A, B);
                                printf("A - B = ");
                                display(simplify(subtract1));
                                break;

                        case 3:
                                subtract2 = subtraction(B, A);
                                printf("B - A = ");
                                display(simplify(subtract2));
                                break;
                        case 4:
                                multiply = multiplication(A, B);
                                printf("A * B = ");
                                display(simplify(multiply));
                                break;
                        case 5:
                                if(B.numerator == 0)
                                        printf("Invalid Calculation. Has resulted the denominator to be 0.\n");
                                else{
                                        division1 = division(A, B);
                                        printf("A / B = ");
                                        display(simplify(division1));
                                }

                                break;
                        case 6:
                                if(A.numerator == 0)
                                        printf("Invalid Calculation. Has resulted the denominator to be 0.\n");
                                else{
                                        division2 = division(B, A);
                                        printf("B / A = ");
                                        display(simplify(division2));
                                }

                                break;
                        case 7:
                                if(A.numerator == 0)
                                        printf("Invalid Calculation. Has resulted the denominator to be 0.\n");
                                else{
                                        Rational_Type temp;
                                        temp = simplify(A);
                                        printf("1 / A = ");
                                        printf("%d / %d", temp.denominator, temp.numerator);
                                }
                                break;
                        case 8:
                                if(B.numerator == 0)
                                        printf("Invalid Calculation. Has resulted the denominator to be 0.\n");
                                else{
                                        Rational_Type temp;
                                        temp = simplify(B);
                                        printf("1 / B = ");
                                        printf("%d / %d", temp.denominator, temp.numerator);
                                }
                                break;
                        case 9:
                                printf("\nExiting the program...\n");
                                break;
                }

        }while(menuNum != 9);

        return 0;
}


/*Find the greatest common denominator*/
int greatCommonDenom(int numer, int denom){
        int gcd, remainder;

        while(denom != 0){
                remainder = numer % denom;
                numer = denom;
                denom = remainder;
        }

        gcd = numer;
        return gcd;
}

/*Simplify the rational number*/
Rational_Type simplify(Rational_Type r){
        int gcd;

        gcd = greatCommonDenom(r.numerator, r.denominator);
        r.numerator = r.numerator / gcd;
        r.denominator = r.denominator / gcd;

        return r;
}
