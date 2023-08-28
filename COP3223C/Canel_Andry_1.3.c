/*
COP3223 Summer 2023 Assignment 1_3
Copyright 2023 Andry Canel
*/


#include <stdio.h>

int main() {
    int numRows = 0;

    // prompt the user for the number of rows (odd number) and keep asking if it is not odd number or between 1 and 19
    do {
        printf("Please enter the number of rows (odd number): ");
        scanf("%d", &numRows);
    } while (numRows%2 == 0 || ( numRows < 1 || numRows > 19));

    int halfRows = numRows / 2;//going to split the printing part into two loops

    
    for (int i = 0; i <= halfRows; i++) {// printing the top part of the diamond
        for (int j = 1; j <= halfRows - i; j++) {
            printf(" ");
        }
        for (int j = 1; j <= (2*i) + 1; j++) {
            printf("*");
        }
        printf("\n");
    }

    
    for (int i = halfRows - 1; i >= 0; i--) {// printing the bottom part of the diamond
        for (int j = 1;  j <= halfRows - i; j++) {
            printf(" ");
        }
        for (int j = 1; j <= (2*i) + 1; j++) {
            printf("*");
        }
        printf("\n");
    }

    return 0;
}
