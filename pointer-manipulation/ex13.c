#include <stdio.h>

int main(){
    char aux;
    char *nome = "Algoritmos";
    char *p3;

    /* (c) */
    p3 = &nome[0];
    aux = *p3;
    printf("%c", aux);

    /* (d) */
    p3 = &nome[4];
    aux = *p3;
    printf("%c", aux);

    /* (e) */
    p3 = nome;
    printf("%c", *p3);

    /* (f) */
    p3 = p3 + 4;
    printf("%c", *p3);

    /* (g) */
    p3 = p3 - 4;
    printf("%c", *p3);

    return (0);
}