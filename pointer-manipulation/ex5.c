#include <stdio.h>
#include <stdlib.h>

int funcA(int **par1){
    (*par1)[0] = 100;
    (*par1)[1] = 200;
    (*par1)[2] = 300;
    printf("(funcA) vetor[0] %d %p \n", *(*par1), (*par1));
    return 0;
}

int funcB(int par1){
    par1 = 55;
    printf("(fundB) vetor[0] %d %p \n", par1, &par1);
    return 0;
}

int funcC(int *par1){
    *par1 = 555;
    printf("(fundC) vetor[0] %d %p \n", *par1, par1);
    return 0;
}

int funcD(int **par1){
    ++(*par1);
    printf("(funcD) vetor[0] %d %p \n", *(*par1), (*par1));
    return 0;
}

int main(int argc, char **argv){
    int *ptr_valor = NULL;
    int valor[3] = {10,20,30};

    ptr_valor = &valor[0];
    printf("(main-(a)) vetor[0] %d %p %p \n", *ptr_valor, &valor[0], &valor[1]);
    funcA(&ptr_valor);
    printf("(main-(a)) vetor[0] %d %p %p \n", *ptr_valor, &valor[0], &valor[1]);

    ptr_valor = &valor[0];
    printf("(main-(b)) vetor[0] %d %p %p \n", *ptr_valor, &valor[0], &valor[1]);
    funcB(valor[0]);
    printf("(main-(b)) vetor[0] %d %p %p \n", *ptr_valor, &valor[0], &valor[1]);

    ptr_valor = &valor[0];
    printf("(main-(c)) vetor[0] %d %p %p \n", *ptr_valor, &valor[0], &valor[1]);
    funcC(valor);
    printf("(main-(c)) vetor[0] %d %p %p \n", *ptr_valor, &valor[0], &valor[1]);

    ptr_valor = &valor[0];
    printf("(main-(c)) vetor[0] %d %p %p \n", *ptr_valor, &valor[0], &valor[1]);
    funcD(&ptr_valor);
    printf("(main-(c)) vetor[0] %d %p %p \n", *ptr_valor, &valor[0], &valor[1]);

    return (0);
}