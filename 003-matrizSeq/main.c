#define N 10 //número de linhas da matriz
#define M 10 //número de colunas da matriz

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrizv3.h"

/*
function main
Executa um teste simplificado das funções da biblioteca de matrizes, conforme exemplo disponibilizado
pelo professor no enunciado do exercício.
@return int, 0 para ok e outro valor para erro
*/
int main(int argc, char *argv[]) {

    //declara objeto do tipo mymatriz (definido em matrizv3.h)
    mymatriz mat_a;
    
    //inicializa definições de tamanho da matriz
	mat_a.matriz = NULL;
	mat_a.lin = N;
	mat_a.col = M;
    
    //aloca memória para matriz
    if (malocar(&mat_a)) {
        printf ("Error..\n");
        exit(-1);
    };
    
    mimprimir(&mat_a);
    mzerar(&mat_a);
    mimprimir(&mat_a);
    mgerar(&mat_a, -9999);
    mimprimir(&mat_a);
    mliberar(&mat_a);
    
    return (0);

}