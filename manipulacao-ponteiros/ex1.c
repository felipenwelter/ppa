#include <stdio.h>
#include <stdlib.h>

int fA( int valor, int *p1){
    valor = 10;
    p1 = &valor;
    *p1 = 20;
    printf("(a2) %d \n", valor);
    return 0;
}

int main(int argc, char **argv){
    int valor = 5;
    int *p1 = NULL;

    printf("(a1) %d  \n", valor);
    fA(valor,p1);
    printf("(a3) %d \n", valor);

    return (0);
}