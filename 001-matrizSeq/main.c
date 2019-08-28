#define N 10
#define M 10
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "matrizv3.h"

//gcc -Wall -O3 matrizv3.o toolsv3.o main.c -o main


int main(int argc, char *argv[]) {

    mymatriz mat_a;
    
	mat_a.matriz = NULL;
	mat_a.lin = N;
	mat_a.col = M;

    if (malocar(&mat_a)) {
        printf ("Error..\n");
    };
    
    mimprimir(&mat_a);
    mzerar(&mat_a);
    mimprimir(&mat_a);
    mgerar(&mat_a, -9999);
    mimprimir(&mat_a);
    mliberar(&mat_a);
    
    return 0;

}
