
#include <stdio.h>

int main(){


    int sum = 0;

    for(int i = 0; i <=1000; i+=2){
        
        if (i%3!=0) sum+=i;
      
    }

    printf("The sum is %d", sum);

    return 0;


}