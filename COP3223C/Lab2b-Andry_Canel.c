#include <stdio.h>

int main() {
    int num = 0;
printf("N \t 10*N \t 100*N \t 1000*N\n");

for(int i = 1; i <=10; i++){
    printf("%d \t %d \t %d \t %d\n", i, 10*i,100*i,1000*i);
}
   
    return 0;
}