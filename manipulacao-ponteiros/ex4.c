#include <stdio.h>
#include <stdlib.h>

int *fF(char *p3){
    p3 = p3 + 5;
    printf("(f) %c \n",*p3);
    return p3;
}

int fG(char *p3){
    char *aux = NULL;
    p3--;
    aux = p3;
    p3++;
    printf("(g) %c \n", *aux);
    return 0;
}

int *fH(int *vetor, int *p4){
    int idade = 45;

    vetor[0] = 31;
    vetor[1] = idade;
    vetor[2] = 27;
    p4 = ++vetor;
    printf("(h2) %d \n",*p4);
    printf("(h3) %p %p \n", p4, vetor);
    return p4;
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
    
    p3 = fF(nome);
    fG(p3);

    printf("(h1) %p %p \n", p4, vetor);
    p4 = p5 = fH(vetor,p4);
    printf("(h5) %d \n", vetor[1]);
    printf("(h4) %p %p \n", p4, vetor);

    return (0);
}