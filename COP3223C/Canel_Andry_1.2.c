/*
COP3223 Summer 2023 Assignment 1_2
Copyright 2023 Andry Canel
*/


#include <stdio.h>
#include <stdbool.h>

int main() {
    int num, originalNum, remainder, reversedNum = 0;//initializing required variables
    bool isPalindrome = true;//setting default boolean to true

    printf("Please enter a five-digit integer: ");
    scanf("%d", &num);

    originalNum = num;//storing the original number in a variable for later

    // reverse the number using mod and division
    while (num != 0) {
        remainder = num % 10;
        reversedNum = (reversedNum* 10) + remainder;
        num/=10;
    }

   
    if (reversedNum != originalNum) { // if the reversed number is equal to the original number
        isPalindrome = false;
    }

    // out what we found
    if (isPalindrome) {
        printf("%d is a palindrome number!", originalNum);
    } else {
        printf("%d is not a palindrome number :(", originalNum);
    }

    return 0;
}