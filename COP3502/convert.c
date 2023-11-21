#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int fahrenheitToCelsius (int degree){
float conversion = (5.0/9.0) * ((float)degree-32.0);

return (int)conversion;


}

int celsiusToFahrenheit (int degree){
float conversion = ((9.0/5.0) * ((float)degree))+32.0;
return (int)conversion;


}



int main(){

        printf("What would you like to convert to today?: \nFahrenheit to celsius(type \"C\") or celsiusToFahrenheit (type \"F\")\n");
        
        char ans;
        int degrees;
        int convert = 0;
        scanf(" %c", &ans);
        switch (ans)
        {
        case 'C':
            printf("Nice! Please provide the temerpature to convert into celcius: ");
            
            scanf(" %d", &degrees);
            convert = fahrenheitToCelsius(degrees);
            printf("%d degree F = %d degree C", degrees ,convert);
            break;
        case 'F':
            printf("Nice! Please provide the temerpature to convert into fahrenheit: ");
            scanf(" %d", &degrees);
            convert= celsiusToFahrenheit(degrees);
            printf("%d degree C = %d degree F", degrees ,convert);
            break;
        default:
            printf("An error has occured...ending program\n");
            break;
        }




}