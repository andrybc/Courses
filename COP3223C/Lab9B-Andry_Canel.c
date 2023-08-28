#include <stdio.h>

void printNumberInBinary(unsigned int numToPrint) {
    // loop over each bit in the number
    for(int i = (sizeof(numToPrint) * 8) - 1; i >= 0; i--) {
        // print '1' if the bit is set, '0' if it is not
        putchar((numToPrint & (1u << i)) ? '1' : '0');
    }
    printf("\n");
}

unsigned int calculatePowerOfTwo(unsigned int baseNumber, unsigned int power) {
    // left-shift the baseNumber by power bits
    return baseNumber << power;
}

int main() {
    unsigned int userInputNumber;
    unsigned int userInputPower;

    printf("Enter a number: ");
    scanf("%u", &userInputNumber);

    printf("Enter a power: ");
    scanf("%u", &userInputPower);

    // calculate the result of userInputNumber * 2^userInputPower
    unsigned int calculationResult = calculatePowerOfTwo(userInputNumber, userInputPower);

    printf("Result (decimal): %u\n", calculationResult);
    printf("Result (binary): ");
    // print the result in binary format
    printNumberInBinary(calculationResult);

    return 0;
}
