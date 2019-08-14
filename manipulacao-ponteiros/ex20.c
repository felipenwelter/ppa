#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv){
    int i = 30, j = 50;
    int *p, *q;
    
    p = &i;
    q = &j;

    printf("%d\n", -4+**&p);
}