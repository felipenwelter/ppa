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
    printf("linhas: %d e colunas: %d \n", lin,col);

    int **new_matriz; //ponteiro para a matriz
    int i, j; //auxiliar

    if (lin < 1 || col < 1) { //verifica parametros recebidos
      printf ("** Erro: Parametro invalido **\n");
      return (-1);
    }else{
      printf ("lin > 1 and col > 1\n");
    }

    // aloca as linhas da matriz
    new_matriz = (int **) calloc (lin, sizeof(int *));	//Um vetor de 'lin' ponteiros para int
    if (new_matriz == NULL) {
      printf ("** Erro: Memoria Insuficiente **\n");
      return (-1);
    }else{
      printf("new_matriz lines allocated. addresses:\n");
      for (i = 0; i < lin; i++){
        printf("[%d] %p\n",i, &new_matriz[i]);
      }
    }

    // aloca as colunas da matriz
    for ( i = 0; i < lin; i++ ) {
      new_matriz[i] = (int*) calloc (col, sizeof(int));	// 'lin' vetores de 'col' ints
      if (new_matriz[i] == NULL) {
        printf ("** Erro: Memoria Insuficiente **\n");
        return (-1);
      }else{
        for (j = 0; j < col; j++){
          printf("[%d][%d] %p\n", i, j, &new_matriz[i][j]);
        }
      }
    }

    //aponta para nova matriz
    matriz->matriz = new_matriz;

    return (0); // retorna o ponteiro para a matriz
}




int mgerar(mymatriz *matriz, int valor){
    printf("mgerar");
    return 0;
}

int mimprimir (mymatriz *matriz){

  if (matriz == NULL){
    printf(" Problema encontrado - Matriz não alocada.\n");
    return (0);
  }else{
    printf(" Ok - Matriz alocada.\n");
  }
    return 0;
}

int mzerar (mymatriz *matriz){
    printf("mzerar");
    return 0;
}

int mliberar (mymatriz *matriz){
    printf("mliberar");
    return 0;
}

int mcomparar (mymatriz *mat_a, mymatriz *mat_b){
    printf("mcomparar");
    return 0;
}
