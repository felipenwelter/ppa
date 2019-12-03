#include <stdio.h>
#include <stdlib.h>

int fC(char *p3, char* nome){
    char aux;
    
    p3 = &nome[0];
    aux = *p3;
    printf("(c) %c \n", aux);
    return 0;
}

int main(int argc, char **argv){
    char *nome = "Algoritmos";
    char *p3 = NULL;

    fC(p3,nome);
    return (0);
}