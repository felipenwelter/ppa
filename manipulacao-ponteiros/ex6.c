#include <stdio.h>
#include <stdlib.h>

char *fF(char *p3){
    p3 = p3 + 5;
    printf("(f) %c \n", *p3);
    return p3;
}

int main(int argc, char **argv){
    char *nome = "Algoritmos";
    char *p3 = NULL;

    p3 = fF(nome);

    return(0);
}