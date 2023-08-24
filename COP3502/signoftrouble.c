#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX_STRING_SIZE 100002  //defining max size of strings


/*void function that populates the frequency array for each string..makes sure to not be able to alter the actual
string with setting it as a const. */
void calculateFreq(const char* signName, int* frequencyArray){

        for (size_t i = 0; signName[i] != '\n'; i++) {
            if(signName[i] == ' ') continue;//continue if its a space

            frequencyArray[signName[i] - 'A']++;
          //  printf("The letter %c has shown up %d  times\n", signName[i],frequencyArray[signName[i] - 'A']);

        }

}

int main(){
    //declaring both strings as char arrays

    char *oldSignName;
    char *newSignName;
    int frequencyOldArray[26] = {0}; // initialize all elements to 0 for the frequency arrays for the signs
    int frequencyNewArray[26] = {0}; 
    int count = 0;

    oldSignName = (char *)calloc(MAX_STRING_SIZE , sizeof(char));//calloc to initialize arrays with 0 and max size defined earlier
    newSignName = (char *)calloc(MAX_STRING_SIZE , sizeof(char));

    fgets(oldSignName, MAX_STRING_SIZE,stdin);//scan in both strings
    fgets(newSignName, MAX_STRING_SIZE,stdin);

    calculateFreq(oldSignName, frequencyOldArray);//call function to populate the frequency arrays
    calculateFreq(newSignName, frequencyNewArray);

    for(int i = 0; i <26; i++){//iterate through all indexes to compare the amount of letters each has 

        if(frequencyNewArray[i] > frequencyOldArray[i]){//if new has a greater count in a particular index ...add the amount it has more of to count
            int diff = frequencyNewArray[i]-frequencyOldArray[i];
            count += diff;
        }

    }

    printf("The amount of new letters needed is: %d\n", count);


    free(oldSignName);
    free(newSignName);
    return 0;
}