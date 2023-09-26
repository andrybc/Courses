#include <stdio.h>
#include <stdlib.h>




int main(){


    double weight;
    int miles;
    double shipping_charge = 0;
    double rate = 0;
    int numofCharge;
    //printf("What is the weight of the package?:");
    
 scanf("Weight: %lf pounds\nMiles: %d miles", &weight, &miles);

    //printf("%lf\n", weight);
    //printf ("%d\n", miles);
   
    
    if(weight > 50){
        printf("Sorry, we only ship packages of 50 pounds or less.");
        return 0;
    }
    else if( weight <= 10 ){

        rate = 3.0;

    }
    else if(weight > 10 && weight <= 50){
        rate = 5.0;
    }
    
    
    
    if( miles % 500 == 0){
        numofCharge = miles/500;
    }
    else{
        numofCharge = miles/500 +1;
    }
  
   // printf("%d\n", numofCharge);

    shipping_charge = numofCharge * rate;


    if( miles > 1000){
        shipping_charge += 10;
        //shipping_charge = shipping_charge +10;
    }



    printf("Your shipping charge is: $%.2lf", shipping_charge);
    return 0;

}