#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv){
    int i = 3;
    int j = 5;
    int *p = NULL;
    int *q = NULL;

    p = &i;
    q = &j;

    p = &*&j;
    i = *&j;
    printf("i=(*&)j; = %d\n", i);
    
    return (0);
}