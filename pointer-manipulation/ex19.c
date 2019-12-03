#include <stdio.h>

int main(){
    int valor;
    int *p1;

    /* (a) */
    valor = 10;
    p1 = &valor;
    *p1 = 20;
    printf("(a) %d \n", valor);

    return (0);
}