#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stddef.h>


#define M_PI 3.14159265358979323846

typedef struct standingGroup{

    int numsPeople;
    double angleToCenter;
}standingGroup;

void swap(standingGroup* a, standingGroup* b) {
    standingGroup t = *a;
    *a = *b;
    *b = t;
}
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

void quickSort(standingGroup arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void printGroups (standingGroup arr[], int numofGroups){

    for(int i = 0; i < numofGroups; i++){
        printf("Standing Goup #%d has %d people and are at a %f angle\n", i+1, arr[i].numsPeople, arr[i].angleToCenter);
    }
}
int min(int num1, int num2) {
    return (num1 < num2 ) ? num1 : num2;
}

int max(int num1, int num2) {
    return (num1 > num2 ) ? num1 : num2;
}


int main(){

    int initialAngle, numGroupStanding;

    scanf("%d %d", &numGroupStanding, &initialAngle);

    standingGroup* arrayOfGroups = malloc(2 * numGroupStanding * sizeof(standingGroup));
    int minPeopleInProjection = 0;;

    for(int i = 0; i < numGroupStanding; i++){
        int x,y;
        scanf("%d %d %d", &x,&y,&arrayOfGroups[i].numsPeople);
        minPeopleInProjection += arrayOfGroups[i].numsPeople;
        double angleRadians = atan2(y,x);
        double angleDegrees = angleRadians * (180.0 / M_PI);
        if (angleDegrees < 0) angleDegrees += 360;
            
            

        arrayOfGroups[i].angleToCenter = angleDegrees;
        arrayOfGroups[i + numGroupStanding] = arrayOfGroups[i];
        arrayOfGroups[i + numGroupStanding].angleToCenter += 360;
    }

quickSort(arrayOfGroups, 0, 2* numGroupStanding - 1);
;
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
arrayOfGroups = realloc(arrayOfGroups, newNumGroups * sizeof(standingGroup));

// Continue with the rest of the code

printGroups(arrayOfGroups, newNumGroups);
printf("%d\n",minPeopleInProjection);
double maxAngle = 0.0;

for (int i = 0; i < numGroupStanding; i++) { // Only need to consider the first half as starting points
    int j = (i + 1) % (2 * numGroupStanding);
    int peopleInProjection = arrayOfGroups[i].numsPeople;
    while (j != i && arrayOfGroups[j].angleToCenter - arrayOfGroups[i].angleToCenter <= initialAngle) {
        peopleInProjection += arrayOfGroups[j].numsPeople;
        j = (j + 1) % (2 * numGroupStanding);
    }
    if (peopleInProjection <= minPeopleInProjection) {
        minPeopleInProjection = peopleInProjection;
        double angle = arrayOfGroups[j].angleToCenter - arrayOfGroups[i].angleToCenter;

        maxAngle = max(maxAngle, angle);
    }
}


printf("%d\n", minPeopleInProjection);
printf("%.4f\n", maxAngle);




    return 0;
}