#include <stdio.h>
#define PI 3.14159

double calculateCircum(double rad){
        return 2 * PI * rad;
}

double calculateArea(double rad){
        return PI * rad * rad;
}

int main(){
        double  radius, area, circum;
        char  repeat[] = "n";

        //Calculate the circumference and area of a circle with radius inputted by user
        do{
                printf("This program will calculate the circumference and area of a circle!\n\n");

                do{
                        printf("Enter a radius greater than 0: ");
                        scanf("%lf",&radius);

                        if(radius <= 0){                //Validate radius
                                printf("The radius must be greater than 0, re-enter again!\n");
                        }
                }while(radius <= 0);

                //Calcualte Circumference and Area
                circum = calculateCircum(radius);
                area = calculateArea(radius);

                printf("The circumference is %.2f\n", circum);
                printf("The area is %.2f\n", area);

                printf("Would you like to calculate another circle with another radius? (Enter Y or N):");
                scanf("%s", repeat);

        }while(repeat[0] == 'Y' || repeat[0] == 'y');

        printf("Program ending...\n");

        return 0;
}
