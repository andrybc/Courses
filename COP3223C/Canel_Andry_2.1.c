/*
COP3223 Summer 2023 Assignment 2_1
Copyright 2023 Andry Canel
*/



#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to generate a random number within the specified range
int random_number_gen(int upperBound) {
    return rand() % upperBound + 1; // Generate a random number between 1 and upperBound (inclusive)
}

// Function to handle the guessing logic
void guess_number(int targetNumber, int upperBound) {
    int guess;
    int numGuesses = 0;

    printf("I have chosen a number. What's your guess? ");

    do {
        scanf("%d", &guess);
        numGuesses++;
        if (numGuesses >= 8) {
            printf("Better luck next time!\n");
            break;
        }
        if (guess == targetNumber) {
            printf("You got it in %d guess%s!\n", numGuesses, (numGuesses > 1) ? "es" : "");
            break;
        } else if (guess < targetNumber) {
            printf("Too low. Guess again: ");
        } else {
            printf("Too high. Guess again: ");
        }


    } while (1); // Loop continues indefinitely until the player guesses the correct number or exceeds the maximum number of guesses
}

int main() {
    int playAgain = 1;

    do {
        printf("Let's play Guess the Number!\n");

        int level;
        printf("Choose a difficulty level (1, 2, or 3): ");
        scanf("%d", &level);

        int upperBound;
        switch (level) {
            case 1:
                upperBound = 10; // Set the upper bound to 10 for easy difficulty
                break;
            case 2:
                upperBound = 100; // Set the upper bound to 100 for medium difficulty
                break;
            case 3:
                upperBound = 1000; // Set the upper bound to 1000 for hard difficulty
                break;
            default:
                printf("Invalid difficulty level. Exiting the game.\n");
                return 0; // If an invalid difficulty level is chosen, exit the game
        }

        srand(time(0)); // Seed the random number generator with the current time
        int targetNumber = random_number_gen(upperBound); // Generate the target number within the specified range

        guess_number(targetNumber, upperBound); // Call the guess_number function to handle the guessing logic

        printf("Would you like to play again? (1 for yes, 0 for no): ");
        scanf("%d", &playAgain);
    } while (playAgain); // Loop continues as long as the player wants to play again

    printf("Thank you for playing! Goodbye!\n");
    return 0;
}