/*
COP3223 Summer 2023 Assignment 3_1
Copyright 2023 Andry Canel
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// fefine a constant for the maximum length of a name
#define MAX_NAME_LENGTH 100

// define the initial size of the array
#define INITIAL_ARRAY_SIZE 4

/*
 * function to expand the array size when it reaches its limit.
 * It takes the current array and its size as parameters,
 * and returns a pointer to the new expanded array.
 */
char** expandArray(char** currentArray, int currentSize) {
    char** expandedArray = realloc(currentArray, currentSize * 2 * sizeof(char*));
    if(expandedArray == NULL) {
    printf("Error reallocating memory!\n");
        exit(1);
    }
    return expandedArray;
}

/*
 * function to print all the names in the array.
 * it takes the array and its size as parameters.
 */
void printList(char** namesArray, int arraySize) {
    for(int i = 0; i < arraySize; i++) {
        printf("%s\n", namesArray[i]);
    }
}

/*
 * function to search for a name in the array.
 * it takes the array, its size, and the name to be searched as parameters,
 * and returns the index of the name if it is found, or -1 if it is not found.
 */
int findName(char** namesArray, int arraySize, char* nameToFind) {
    for(int i = 0; i < arraySize; i++) {
        if(strcmp(namesArray[i], nameToFind) == 0) {
            return i;
        }
    }
    return -1;
}

/*
 * function to remove a name from the array and resize the array.
 * it takes the array, its size, and the name to be removed as parameters,
 * and returns the new size of the array.
 */
int removeName(char** namesArray, int arraySize, char* nameToRemove) {
    int nameIndex = findName(namesArray, arraySize, nameToRemove);
    if(nameIndex == -1) {
    printf("Name not found!\n");
        return arraySize;
    }
    free(namesArray[nameIndex]);
    for(int i = nameIndex; i < arraySize - 1; i++) {
        namesArray[i] = namesArray[i + 1];
    }
    return arraySize - 1;
}


int main() {
    int namesCount = 0;
    int arrayCapacity = INITIAL_ARRAY_SIZE;
    char** namesArray = malloc(arrayCapacity * sizeof(char*));
    char userInput[MAX_NAME_LENGTH];

    // continuously ask the user for names until the user enters "done"
    while(1) {
        printf("Please enter a name: ");
        scanf("%s", userInput);
        if(strcmp(userInput, "done") == 0) {
            break;
        }
        // if the array is full, expand its size
        if(namesCount == arrayCapacity) {
            namesArray = expandArray(namesArray, arrayCapacity);
            arrayCapacity *= 2;
        }
        // store each name in dynamically allocated memory
        namesArray[namesCount] = malloc(strlen(userInput) + 1);
        strcpy(namesArray[namesCount], userInput);
        namesCount++;
    }

    // print all names
    printList(namesArray, namesCount);

    // ask the user for a name to find and print its index
    printf("Please enter a name to find: ");
    scanf("%s", userInput);
    int nameIndex = findName(namesArray, namesCount, userInput);
    if(nameIndex == -1) {
        printf("Name not found!\n");
    } else {
        printf("Found name at index %d\n", nameIndex);
    }

    // ask the user for a name to remove and remove it from the array
    printf("Please enter a name to remove: ");
    scanf("%s", userInput);
    namesCount = removeName(namesArray, namesCount, userInput);

    // print the updated list of names
    printList(namesArray, namesCount);

    // free all allocated memory
    for(int i = 0; i < namesCount; i++) {
        free(namesArray[i]);
    }
    free(namesArray);

    return 0;
}
