#include "Rational.h"
#include <stdio.h>

Rational_Type make_Rational(int numer, int denom){
        Rational_Type r;
        r.numerator = numer;
        r.denominator = denom;

        return r;
}
/*Addition operation*/
Rational_Type addition(Rational_Type a, Rational_Type b){
        Rational_Type result;

        /*When the two values do not have the same denominator*/
        if(a.denominator != b.denominator){
                result.denominator = a.denominator * b.denominator;
                result.numerator = (a.numerator * b.denominator) + (b.numerator * a.denominator);
        }
        else{
                result.denominator = a.denominator;
                result.numerator = a.numerator + b.numerator;
        }

        return result;
}

Rational_Type subtraction(Rational_Type a, Rational_Type b){
        Rational_Type result;

        /*When the two values do not have the same denominator*/
        if(a.denominator != b.denominator){
                result.denominator = a.denominator * b.denominator;
                result.numerator = (a.numerator * b.denominator) -(b.numerator *a.denominator);
        }
        else{
                result.denominator = a.denominator;
                result.numerator = a.denominator - b.denominator;

        }

        return result;
}

Rational_Type multiplication(Rational_Type a, Rational_Type b){
        Rational_Type result;

        result.denominator = a.denominator * b.denominator;
        result.numerator = a.numerator * b.numerator;

        return result;
}

Rational_Type division(Rational_Type a, Rational_Type b){
        Rational_Type result;

        result.denominator = a.denominator * b.numerator;
        result.numerator = a.numerator * b.denominator;

        return result;
}

void display(Rational_Type a){
        printf("%d / %d", a.numerator, a.denominator);
}

