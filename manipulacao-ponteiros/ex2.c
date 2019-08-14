#include <stdio.h>
#include <stdlib.h>

int fI( int *p5, int *p4){
    int idade;

    p5 = p4 + 2;
    idade = *p5;
    printf("(i) %d \n", idade);
    return 0;
}

int fJ( int *p5, int idade){
    int *p4;

    p4 = p5 - 1;
    idade = *p4;
    printf("(j) %d \n", idade);
    return 0;
}

int fK( int *p4, int idade){
    p4 = p4 - 2;
    idade = *p4;
    printf("(k) %d \n", idade);
    return 0;
}

int fL( int *p5, int *vetor){
    p5 = &vetor[2] - 1;
    printf("(l) %d \n", *p5);
    return 0;
}

int fM( int *p5){
    p5++;
    printf("(m) %d \n", *p5);
    return 0;
}

int fN( int *p5){
    p5++;
    printf("(n) %d \n", *p5);
    return 0;
}

int main(int argc, char **argv){
    int idade = 10;
    int vetor[3] = {0,1,2};
    int *p4 = NULL;
    int *p5 = NULL;

    p4 = p5 = &vetor[1];

    fI(p5,vetor);
    fJ(p4,idade);
    fK(&vetor[2],idade);
    fL(p5,vetor);
    fM(p4);
    fN(p5);

    return (0);
}