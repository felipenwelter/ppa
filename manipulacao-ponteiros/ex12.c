#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
    int valor[3] = {10,20,30};
    int *ptr_valor = NULL;

    ptr_valor = &valor[0];
    if (*(++ptr_valor) == valor[1])
        printf("OK (1)\n");
    ptr_valor = &valor[0];
    printf("%d \n", *ptr_valor);
    if( *(ptr_valor++) == valor[1])
        printf("OK (2)\n");
    
    return 0;
}