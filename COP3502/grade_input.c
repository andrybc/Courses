#include <stdlib.h>
#include <stdio.h>





int main(){
    
    int grade;

    int gradeCounter = 0;
    int gradeAbove70 = 0;



    scanf("%d", &grade);
    
    while( grade != -1  ){

        if( grade >100 || grade < 0){
         printf("That is not a valid grade!\n") ;  

        }

       else if(grade >=70){
            gradeAbove70++;
            gradeCounter++;

        }
        else{
            gradeCounter++;
        }

        scanf("%d", &grade);




    }


    printf("You entered %d passing grades.\n", gradeAbove70);

    float validGrade = ((float)gradeAbove70/ (float)gradeCounter) *100;

    printf("%.1f", validGrade); 
    
    printf("%% of the valid grades entered are passing grades ");



    return 0;
}