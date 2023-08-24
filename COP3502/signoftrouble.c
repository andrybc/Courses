#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX_STRING_SIZE 100002

void calculateFreq(const char* signName, int* frequencyArray){

        for (size_t i = 0; signName[i] != '\n'; i++) {
            if(signName[i] == ' ') continue;

            frequencyArray[signName[i] - 'A']++;
            printf("The letter %c has shown up %d  times\n", signName[i],frequencyArray[signName[i] - 'A']);

        }

}

int main(){
    //declaring both strings as char arrays

    char *oldSignName;
    char *newSignName;
    int frequencyOldArray[26] = {0}; // initialize all elements to 0
    int frequencyNewArray[26] = {0}; 
    int count = 0;

    oldSignName = (char *)calloc(MAX_STRING_SIZE , sizeof(char));
    newSignName = (char *)calloc(MAX_STRING_SIZE , sizeof(char));

    fgets(oldSignName, MAX_STRING_SIZE,stdin);
    fgets(newSignName, MAX_STRING_SIZE,stdin);

    calculateFreq(oldSignName, frequencyOldArray);
    calculateFreq(newSignName, frequencyNewArray);

    for(int i = 0; i <26; i++){

        if(frequencyNewArray[i] > frequencyOldArray[i]){
            int diff = frequencyNewArray[i]-frequencyOldArray[i];
            count += diff;
        }

    }

    printf("The amount of new letters needed is: %d", count);


    free(oldSignName);
    free(newSignName);
    return 0;
}