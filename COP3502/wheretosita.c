#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/*
Andry Canel
10/8/2023
Lab 13


*/
#define MAX_STRING_SIZE 19  //defining max size of strings


int count = 0;//global variable to count how many 

typedef struct attendee {

char name[19];
int boughtPopcorn;



} attendee;

int** arrayOfHaters(int * hateEachOther, int numofAttendees, int restrictions){

    int** connections = (int**)malloc(numofAttendees * sizeof(int*));
    for( int i = 0; i < numofAttendees; i++){
        connections[i] = (int*)calloc(numofAttendees, sizeof(int));
    }

    for(int i = 0; i < restrictions ; i++){
        int row = hateEachOther[i *2];
        int col = hateEachOther[i * 2 +1];

        connections[row][col] = 1;



    }


    return connections;

}
void print2DArray ( int** array, int rowCol){

    for( int i = 0; i < rowCol; i++){
        for( int j = 0; j < rowCol; j++){

            printf("%d ", array[i][j]);



        }

        printf("\n");

    }

}
void printPermutation ( int* perm, int numofAttendees, attendee* userGroups){

    for( int i = 0; i < numofAttendees; i++){
        int index = perm[i];

        printf("%s %d, ", userGroups[index].name, userGroups[index].boughtPopcorn);

    }
    printf("\n");

}
int validPerm(int* perm, int numofAttendees, attendee* userGroups, int** hateEachother) {
    int i;
            //printPermutation(perm, numofAttendees, userGroups);

    for (i = 0; i < numofAttendees - 1; i++) {
        // check if attendee at perm[i] and perm[i+1] hate each other
        if (hateEachother[perm[i]][perm[i+1]] == 1 || hateEachother[perm[i+1]][perm[i]] == 1) {
           // printf("haters next to each other\n\n");
           // printf("%s, %s\n", userGroups[perm[i]].name, userGroups[perm[i+1]].name);
            return 0;  // Not a valid permutation
        }
       // printPermutation(perm, numofAttendees, userGroups);
        // Check if both attendees at perm[i] and perm[i+1] haven't bought popcorn
        if (userGroups[perm[i]].boughtPopcorn == 0 && userGroups[perm[i+1]].boughtPopcorn == 0) {
            // Check if their neighbors have bought popcorn
           // printf("broke people next to each other\n");
           //printf("%s, %s\n", userGroups[perm[i]].name, userGroups[perm[i+1]].name);
            if ((i == 0 || userGroups[perm[i-1]].boughtPopcorn == 0) || (i+1 == numofAttendees - 1 || userGroups[perm[i+2]].boughtPopcorn == 0)) {
             //  printf("and both exteriors DID NOT BUY POPCORN\n");
              // printf("%s, %s\n\n", userGroups[perm[i-1]].name, userGroups[perm[i+2]].name);
                return 0;  // Not a valid permutation
            }
           // printf("but both exterier did buy popcorn\n");
            //printf("%s, %s\n\n", userGroups[perm[i-1]].name, userGroups[perm[i+2]].name);

        }
    }
    // Check if first and last attendees bought popcorn
   /* if (userGroups[perm[0]].boughtPopcorn == 0 && userGroups[perm[numofAttendees - 1]].boughtPopcorn == 0) {
        return 0;  // Not a valid permutation
    }*/
    
    return 1;  // Valid permutation
}


void createPerms(int* perm, int* used, int permutationSize, int numofAttendees, attendee* userGroups, int** hateEachother) {
    if (permutationSize == numofAttendees) {
        if (validPerm(perm, numofAttendees, userGroups, hateEachother)) {
            count++;
           // printPermutation(perm, numofAttendees, userGroups);
        }
    }
    int i;
    for (i = 0; i < numofAttendees; i++) {
        if (!used[i]) {
            used[i] = 1;
            perm[permutationSize] = i;
            createPerms(perm, used, permutationSize+1, numofAttendees, userGroups, hateEachother);
            used[i] = 0;
        }
    }
}



int main(){
    int numAttendees, restrictions;
    int* hateEachOther;

    scanf("%d %d", &numAttendees, &restrictions);
    
    attendee* userGroup = (attendee*)malloc( numAttendees * sizeof(attendee));//allocating space

    for(int i = 0; i < numAttendees; i++){

        scanf("%s %d", userGroup[i].name, &userGroup[i].boughtPopcorn);
        //userGroup->hateEachOther = malloc(numAttendees * sizeof(char*));
        
    }
   // printf("%d", userGroup[0].boughtPopcorn);

    
   hateEachOther = (int*)malloc (restrictions * 2 * sizeof(int));
    for(int i = 0; i < restrictions; i++){
        char* name1 = (char*)malloc((MAX_STRING_SIZE +1) * sizeof(char)); 
        char* name2 = (char*)malloc((MAX_STRING_SIZE +1) * sizeof(char)); 

       
        

        scanf("%s %s", name1, name2);

        for(int j = 0; j < numAttendees; j++){

            if(strcmp(userGroup[j].name, name1) == 0){
                hateEachOther[i*2]= j;

            }
            if(strcmp(userGroup[j].name, name2) == 0){
                hateEachOther[i*2+1]= j;

            }
        }

    free(name1);
    free(name2);
        
    }

 /*  for(int i = 0; i < restrictions ; i ++){
        printf("%d %d\n", hateEachOther[i*2], hateEachOther[i*2+1]);
    }
*/ 
    int** allowedSeatting = arrayOfHaters(hateEachOther, numAttendees, restrictions);
    //print2DArray(allowedSeatting, numAttendees);

    int* permutations;
    int* used;

    permutations = (int*)malloc(numAttendees * sizeof(int));
    used = (int*)calloc(numAttendees , sizeof(int));

   createPerms(permutations, used, 0, numAttendees, userGroup, allowedSeatting);

    printf("%d", count);



  
    free(hateEachOther);
    free(used);
    free(permutations);

    for(int i = 0; i < numAttendees ; i++){
        free(allowedSeatting[i]);
    }
    free(allowedSeatting);
    free(userGroup);
    return 0;
}