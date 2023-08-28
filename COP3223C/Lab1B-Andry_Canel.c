#include <stdio.h>

int main() {
    int num = 0;
    int numOfDigits[5];

    printf("Please enter a five digit number: ");
    scanf("%d", &num);

    // Extracting individual digits and storing them in the array
    for (int i = 4; i >= 0; i--) {
        numOfDigits[i] = num%10;
        num/=10;
    }

    // Displaying the digits with spaces
    for (int i = 0; i < 5; i++) {
        printf("%d ", numOfDigits[i]);
    }
   
    return 0;
}