#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv){
    int i = 5;
    int *p;
    
    p = &i;
    printf("%p %d %d %d %d \n", p, *p+2, **&p, 3**p, **&p+4);

    return(0);
}