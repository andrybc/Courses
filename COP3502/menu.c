#include <stdlib.h>
#include <stdio.h>



int cmpfunc(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}
int sumArray( int a[], int size){
    int sum = 0;

    for(int i = 0; i < size; i++){
        sum+= a[i];
    }

    return sum;
}


int main(){


        printf("Please enter 5 integers:\n");

        int nums[5];

        for(int i = 0; i < 5; i++){
            scanf(" %d", &nums[i]);
               getchar(); // Consume the newline character

        }

        qsort(nums, 5, sizeof(int), cmpfunc);


        printf("Now what would you like to do with these values:(Choose from the options below 1-4)\n");
        printf("1. Display the smallest number entered\n");
        printf("2. Display the largest number entered\n");
        printf("3. Display the sum of the five numbers entered\n");
        printf("4. Display the average of the 5 numbers entered\n");

        int option;

    scanf("%d", &option);  // Removed extra space in the format specifier

    switch (option) {
    case 1:
        printf("Smallest number: %d\n", nums[0]);
        break;
    case 2:
        printf("Largest number: %d\n", nums[4]);  // Access the last element
        break;
    case 3:
        printf("Sum of the numbers: %d\n", sumArray(nums, 5));
        break;
    case 4:
        printf("Average of the numbers: %.2f\n", (float)sumArray(nums, 5) / 5.0);  // Use floating-point for average
        break;
    default:
        printf("Sorry that was an invalid option\n");
        break;
    }

    return 0;
}