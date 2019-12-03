#include <stdio.h>

int main(){
    int idade;
    int vetor[3];
    int *p4;
    int *p5;

    vetor[0] = 31;
    vetor[1] = 45;
    vetor[2] = 27;

    p4 = vetor;
    idade = *p4;
    printf("(h) %d \n", idade);
    p5 = p4 + 1;
    idade = *p5;
    printf("(i) %d \n", idade);
    p4 = p5 + 1;
    idade = *p4;
    printf("(j) %d \n", idade);
    p4 = p4 - 2;
    idade = *p4;
    printf("(l) %d \n", idade);
    p5 = &vetor[2] - 1;
    printf("(m) %d \n", *p5);
    p5++;
    printf("(n) %d \n",*p5);
    
    return (0);
}