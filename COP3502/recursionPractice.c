#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int zeros(int n) {
 int res = 0;
 while (n != 0) {
 res += n/5;
 n /= 5;
 }
 return res;
}


int zerosRecursion(int n) {
    if (n == 0) {
        return 0;
    } else {
        return n/5 + zeros(n/5);
    }
}

int main(){

printf("%d\n", zeros(10));
printf("%d\n", zerosRecursion(10));
    return 0;
}