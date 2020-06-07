/*Rational.h
 *
 * Header file providing prototypes to support the
 * data type struct Rational
 *
 */


struct Rational{
        int numerator;
        int denominator;
};

typedef struct Rational Rational_Type;

/*create a rational number: numerator and denominator */
Rational_Type make_Rational(int numer, int denom);

/*add two rational numbers */
Rational_Type addition(Rational_Type a, Rational_Type b);

/*substract two rational numbersa */
Rational_Type subtraction(Rational_Type a, Rational_Type b);

/*multiply two rational numbers*/
Rational_Type multiplication(Rational_Type a, Rational_Type b);

/*divide two rational numbers*/
Rational_Type division(Rational_Type a, Rational_Type b);

/*display a rational number appropriately*/
void display(Rational_Type a);
