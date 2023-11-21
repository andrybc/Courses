#include <stdlib.h>
#include <stdio.h>





int main(){


    float sealevels[]= {-38.57,-31.44,-26.52,-28.45,-27.26,-21.50,-26.73,-18.48,-16.65,-12.58, -7.56,-4.29,
    -2.18, 0.44, 1.91,1.43,4.85,10.97,5.68,14.11,23.70,22.60,28.02,38.56,36.32,41.44,45.28,48.09,52.02,56.30,59.39};
    printf("The program uses data from NASA to predict sea level from the years 2020 to 2050\n");
    float sum = 0;
    float avgSeaLevel = 0;

    for(int i = 0; i < 31; i++){
        sum += sealevels[i];
    }
    avgSeaLevel = sum/31.0;
    printf("%f", avgSeaLevel);

    float predictedLevels[7];

    for(int i = 0; i < 7; i++){
        int  year = 2020 + (i *5);
        int x = year - 1993;
        printf("%d\n",x);
        predictedLevels[i]= x * avgSeaLevel + sealevels[0];
        
            }

    printf("The predicted Global Mean Sea Level is \n");


    for(int i = 0; i < 7 ; i ++){
        printf("%d %.2f\n", 2020+(i*5), predictedLevels[i]);
    }
    printf("These predictions were made using data provided by \n");

    for(int i = 0; i < 31 ; i ++){
        if(i == 30){
        printf("%.2f", sealevels[i]);
  
        }
        else{
        printf("%.2f, ", sealevels[i]);

        }
    }
    return 0;
}