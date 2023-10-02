#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char** eachShift(char* word) {
 char** res = calloc(26, sizeof(char*)); // 3 pts
 int len = strlen(word);
 for (int i=0; i<26; i++) { // 1 pt
 res[i] = calloc(len+1, sizeof(char)); // 3 pts
 for (int j=0; j<len; j++) // 1 pt
 res[i][j] = ((word[j]-'A')+i)%26 + 'A'; // 2 pts
 res[i][len] = '\0'; // 1 pt
 }
 return res; // 1 pt
}

int main() {
 char word[100];
 scanf("%s", word);
 char** grid = eachShift(word); // 2 pts
 for (int i=0; i<26; i++) // 1 pt
 printf("%s\n", grid[i]); // 1 pt
 for (int i=0; i<26; i++) // 1 pt
 free(grid[i]); // 2 pts
 free(grid); // 1 pt
}