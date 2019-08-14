#include <stdio.h>
#include <stdlib.h>

int fE(char *nome){
    char *p3;

    p3 = nome;
    printf("(e) %c \n",*p3);
    return 0;
}

int main(int argc, char **argv){
    char *nome = "Algoritmos";
    
    fE(nome);
    
    return (0);
}