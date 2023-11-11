/*
Andry Canel
project.c
Lab 13
10/29/23
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stddef.h>

#define m_pi 3.14159265358979323846

// Define a structure for a standing group
typedef struct standingGroup{
    int numsPeople;
    double angleToCenter;
}standingGroup;

// Function to swap two standing groups
void swap(standingGroup* a, standingGroup* b) {
    standingGroup t = *a;
    *a = *b;
    *b = t;
}

// Function to partition the array of standing groups
int partition(standingGroup arr[], int low, int high) {
    double pivot = arr[high].angleToCenter;
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j].angleToCenter <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// Function to perform quick sort on the array of standing groups
void quickSort(standingGroup arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Function to print the details of the standing groups
void printGroups (standingGroup arr[], int numofGroups){
    for(int i = 0; i < numofGroups; i++){
        printf("Standing Group #%d has %d people and are at a %f angle\n", i+1, arr[i].numsPeople, arr[i].angleToCenter);
    }
}

// Function to return the minimum of two integers
int min(int num1, int num2) {
    return (num1 < num2 ) ? num1 : num2;
}

// Function to return the maximum of two integers
int max(int num1, int num2) {
    return (num1 > num2 ) ? num1 : num2;
}

int main(){
    int initialAngle, numGroupStanding;

    // Read the initial angle and the number of standing groups
    scanf("%d %d", &numGroupStanding, &initialAngle);

    // Allocate memory for the array of standing groups
    standingGroup* arrayOfGroups = (standingGroup*)malloc(2 * numGroupStanding * sizeof(standingGroup));
    int minPeopleInProjection = 0;

    // Read the details of the standing groups and calculate the total number of people in the projection
    for(int i = 0; i < numGroupStanding; i++){
        int x,y;
        scanf("%d %d %d", &x,&y,&arrayOfGroups[i].numsPeople);
        minPeopleInProjection += arrayOfGroups[i].numsPeople;
        double angleRadians = atan2(y,x);
        double angleDegrees = angleRadians * (180.0 / m_pi);
        if (angleDegrees < 0) angleDegrees += 360;
        arrayOfGroups[i].angleToCenter = angleDegrees;
        arrayOfGroups[i + numGroupStanding] = arrayOfGroups[i];
        arrayOfGroups[i + numGroupStanding].angleToCenter += 360;
    }

    // Sort the array of standing groups
    quickSort(arrayOfGroups, 0, 2* numGroupStanding - 1);

    // Remove duplicate standing groups and calculate the new number of standing groups
int newNumGroups = 0;
for (int i = 1; i < 2 * numGroupStanding; i++) {
    if (arrayOfGroups[i].angleToCenter != arrayOfGroups[newNumGroups].angleToCenter) {
        newNumGroups++;
        if (i != newNumGroups) {
            arrayOfGroups[newNumGroups] = arrayOfGroups[i];
        }
    } else {
        arrayOfGroups[newNumGroups].numsPeople += arrayOfGroups[i].numsPeople;
    }
}

// Adjust the number of groups
newNumGroups++;

// Resize the array to fit the new number of groups
arrayOfGroups = (standingGroup*)realloc(arrayOfGroups, newNumGroups * sizeof(standingGroup));

// Continue with the rest of the code

//printGroups(arrayOfGroups, newNumGroups);
//printf("%d\n",minPeopleInProjection);

int left = 0, right = 0;
// Initialize variables for the minimum number of people and maximum angle
int minPeople = minPeopleInProjection;
double maxAngle = -1;

// Initialize variables for the previous number of people and angle
int prevPeople = arrayOfGroups[0].numsPeople;
double prevAngle = arrayOfGroups[0].angleToCenter;

// Iterate over the array of standing groups
for (int i = 0; i < newNumGroups; i++) {
    // Update the left and right pointers
    while (left < newNumGroups && arrayOfGroups[left].angleToCenter < arrayOfGroups[i].angleToCenter - initialAngle) {
        left++;
    }
    while (right < newNumGroups && arrayOfGroups[right].angleToCenter <= arrayOfGroups[i].angleToCenter + initialAngle) {
        right++;
    }
    // Adjust the right pointer if necessary
    if (right >= newNumGroups) {
        right--;
    }
    // Get the number of people in the projection at the right pointer
    int currentPeople = arrayOfGroups[right].numsPeople;
    // Update the minimum number of people if necessary
    if (currentPeople < minPeople) {
        minPeople = currentPeople;
    }
    // Set the minimum number of people to 0 if the difference between the angles is greater than the initial angle
    if (arrayOfGroups[i].angleToCenter - prevAngle > initialAngle) {
        minPeople = 0;
    }
    // Update the maximum angle if necessary
    if (currentPeople < prevPeople || (currentPeople == prevPeople && arrayOfGroups[i].angleToCenter - prevAngle > maxAngle && initialAngle < arrayOfGroups[i].angleToCenter - prevAngle)) {
        maxAngle = arrayOfGroups[i].angleToCenter - prevAngle;
    }
    // Update the previous number of people and angle
    prevPeople = currentPeople;
    prevAngle = arrayOfGroups[i].angleToCenter;
}

// Print the minimum number of people and the maximum angle
printf("%d\n", minPeople);
printf("%.4f\n", maxAngle);

// Free the memory allocated for the array of standing groups
free(arrayOfGroups);

return 0;
}