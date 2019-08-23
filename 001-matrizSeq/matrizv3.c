#include "matrizv3.h"
//#include <stdlib.h>
//#include <string.h>

/*#ifndef SOME_HEADER_FILE_H
#define SOME_HEADER_FILE_H
typedef struct {
  int lin_inicio;
  int lin_fim;
  int col_inicio;
  int col_fim;
} bloco_t;

typedef struct {
  int **matriz;
  bloco_t *bloco;
  int mat_col;
  int mat_lin;
  int divisor;
} matriz_bloco_t;

typedef struct {
  int **matriz;
  int lin;
  int col;
} mymatriz;
#endif*/

// gerência de matrizes
int malocar (mymatriz *matriz){
    
    printf("malocar called \n");
    int lin = matriz->lin;
    int col = matriz->col;
    printf("linhas: %d e colunas: %d \n\n", lin,col);

    /*int **new_matriz = NULL;

	new_matriz = (int **) malloc(nLinha * sizeof(int *));
	if (!new_matriz) {
		printf("ERROR: Out of memory\n");
		return NULL;
	}

  	for (int i =0; i < nLinha; i++) {
			new_matriz[i] = (int *) malloc(sizeof(int)*nColuna);
			if (!new_matriz) {
				printf("ERROR: Out of memory\n");
				return NULL;
			}
	}
	return new_matriz;*/
}

int mgerar(mymatriz *matriz, int valor){
    return 0;
}

int mimprimir (mymatriz *matriz){
    return 0;
}

int mzerar (mymatriz *matriz){
    return 0;
}

int mliberar (mymatriz *matriz){
    return 0;
}

int mcomparar (mymatriz *mat_a, mymatriz *mat_b){
    return 0;
}
