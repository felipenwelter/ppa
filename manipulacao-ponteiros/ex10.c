#include <stdio.h>
#include <stdlib.h>

int fD(char aux, char *nome){
    char *p3;

    p3 = &nome[4];
    aux = *p3;
    printf("(d) %c \n", aux);
    return 0;
}

int main(int argc, char **argv){
    int valor = 5;
    int *p1 = NULL;
    float temp = 26.5;
    float *p2 = NULL;
    char *nome = "Algoritmos";
    char *p3 = NULL;
    char aux = 'c';
    int idade = 10;
    int vetor[3] = {0,1,2};
    int *p4 = NULL;
    int *p5 = NULL;

    fD(aux,nome);
    return (0);
}