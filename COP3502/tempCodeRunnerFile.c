#include <stdlib.h>
#include <stdio.h>
#include <math.h>

float fahrenheitToCelsius(float degree) {//function to convert from F to C
    float conversion = (5.0 / 9.0) * (degree - 32.0); //putting the degrees (in fahrenheit) into the formula to convert it into celcius
    return conversion; //returning the new value
}

float celsiusToFahrenheit(float degree) {// same thing as previous function but now doing from C to F
    float conversion = (9.0 / 5.0) * degree + 32.0;
    return conversion;
}

int main() {
    printf("What would you like to convert to today?\nFahrenheit to Celsius (type \"C\") or Celsius to Fahrenheit (type \"F\")\n");//Prompting the user which way they would like to convert to

//variables to hold the users choice, the degrees they want to convert, and final conversion value
    char ans;
    float degrees;
    float convert = 0;
    scanf(" %c", &ans);//scanning in the C or F

    switch (ans) {//using a switch statement to choose what to run | default is if neither C or F is typed
        case 'C':
            printf("Nice! Please provide the temperature to convert into Celsius: ");
            scanf("%f", &degrees);//scanning in current degree user wants to convert
            convert = fahrenheitToCelsius(degrees);//setting convert to the value returned by this function that passes the variable degree into it
            printf("%d degree F = %d degree C", (int)degrees, (int)convert);//print it out and casting the values as  ints
            break;
        case 'F'://same thing as before but using the celsiesToFahrenheit function instead
            printf("Nice! Please provide the temperature to convert into Fahrenheit: ");
            scanf("%f", &degrees);
            convert = celsiusToFahrenheit(degrees);
            printf("%d degree C = %d degree F", (int)degrees, (int)convert);
            break;
        default:
            printf("An error has occurred...ending program\n");
            break;
    }

    return 0;
}
