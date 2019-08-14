#include <stdio.h>

int main(){
    float temp;
    float *p2;

    /* (b) */
    temp = 26.5;
    p2 = &temp;
    *p2 = 29.0;
    printf("(b) %.1f \n", temp);

    return (0);
}