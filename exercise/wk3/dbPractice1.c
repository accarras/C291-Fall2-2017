//factorial of a number is the product of the number with all
// the numbers below it.
//eg: Factorial of 5 = 5 * 4 * 3 * 2 * 1 = 120
#include <stdio.h>

int values[1];
int factorial(int);

int main(void)
{
    int n = 0; // this variable was undeclared, but needed
               // stores the number we're working with
        
    printf( "Debugging Practice 1 - Quiz 3, Q3\n\n");
     printf( "Please enter the number whose factorial you wish to find: ");
    scanf("%d", &n);

    int fact = factorial(n);
    printf("The factorial of %d is %d", n,fact);

    return 0;
}

int factorial(int number)
{
    // this definitely only works with positive integers
    // is fine for the scope of this debugging?
    int factorial = 1;
    for (int i=1; i<=number; i++){
            // factorial starts off at 1
            // it is multiplied by 1 + the number of iterations starting at 0
            // iterations go until it has looped as "number" times 
            factorial = factorial * i;
    } // tasteful brackets added

    return factorial;
}