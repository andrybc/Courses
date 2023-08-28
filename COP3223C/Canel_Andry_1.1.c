/*
COP3223 Summer 2023 Assignment 1_1
Copyright 2023 Andry Canel
*/


#include <stdio.h>
#include <string.h>
int main() {
    int hoursSubmitted = 0;
    float hourlyRate = 0;
    char employeeName[100]= "";



    
    while (strcmp(employeeName, "-1") != 0) {// continue the loop until the user enters '-1' to end the program


        

        printf("Enter employee name (type '-1' to exit): ");// prompt the user for the employee's name
        scanf("%s", employeeName);

        if(strcmp(employeeName, "-1") == 0) break;//if entered "-1" break 
        
        printf("Enter the number of hours worked by %s: ", employeeName);// prompt the user for the number of hours worked
        scanf("%d", &hoursSubmitted);

        

        printf("Enter the hourly rate for %s ($00.00): ", employeeName);// prompt the user for the hourly rate
        scanf("%f", &hourlyRate);

        float grossPay = 0;
        
        if (hoursSubmitted <= 40) {// if hours worked is less than or equal to 40, use the straight time rate
            
            grossPay = hoursSubmitted * hourlyRate;// Calculate the gross pay based on the number of hours worked
        } else {// if hours worked is more than 40, calculate time-and-a-half for the overtime hours
            
            float overtimeHours = hoursSubmitted - 40;
            grossPay = (40*hourlyRate) + (overtimeHours*hourlyRate * 1.5);
        }

        
        printf("Gross pay for %s is $%.2f\n\n", employeeName, grossPay);// display the calculated gross pay for the employee


    }

    return 0;
}