#include <stdio.h>
#include <stdlib.h>

int funcA(int *par1){
    printf("(2a) %d %p \n", *par1, par1);
    par1++;
    printf("(3a) %d %p \n", *par1, par1);
    return 0;
}

int funcB(int par1){
    printf("(2b) %d %p \n", par1, &par1);
    par1++;
    printf("(3b) %d %p \n", par1, &par1);
    return 0;
}

int main(int argc, char **argv){
    int *ptr_valor = NULL;
    int valor[3] = {10,20,30};

    ptr_valor = valor;
    printf("(1) %d %p %p \n", *ptr_valor, &valor[0], &valor[1]);
    funcA(ptr_valor);
    funcB(*ptr_valor);
    printf("(4) %d %p %p \n", *ptr_valor, &valor[0], &valor[1]);

    return (0);
}