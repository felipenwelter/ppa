#include <stdio.h>
#include <stdlib.h>

int fB(float *temp, float *p2){
    p2 = temp;
    *p2 = 29.0;
    printf("(b2) %.1f \n", *temp);
    return 0;
}

int main(int argc, char **argv){
    float temp = 26.5;
    float *p2 = NULL;

    printf("(b1) %.1f \n", temp);
    fB(&temp, p2);
    printf("(b3) %.1f \n", temp);
    
    return(0);
}