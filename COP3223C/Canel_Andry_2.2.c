/*
COP3223 Summer 2023 Assignment 2_2
Copyright 2023 Andry Canel
*/
#include <stdio.h>

// Recursive function to calculate the greatest common divisor (GCD)
int gcd(int x, int y) {
    if (y == 0) {
        return x; // Base case: If y is 0, return x
    } else {
        return gcd(y, x % y); // Recursive case: Call gcd with y and x % y
    }
}

int main() {
    int num1, num2;
    
    printf("Please input the first number: ");//Prompting for x
    scanf("%d", &num1);
    
    printf("Please input the second number: ");//Prompting for y
    scanf("%d", &num2);
    
    int result = gcd(num1, num2);//Storing divisor in result using the recursive function gcd
    
    printf("The common divisor for %d and %d is %d\n", num1, num2, result);
    
    return 0;
}