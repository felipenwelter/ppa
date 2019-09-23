#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "matrizv3.h"

mymatriz *msomar (mymatriz *mat_a, mymatriz *mat_b, int tipo);
mymatriz *mmultiplicar (mymatriz *mat_a, mymatriz *mat_b, int tipo);

int multiplicar_submatriz (matriz_bloco_t *mat_suba, matriz_bloco_t *mat_subb, matriz_bloco_t *mat_subc);
matriz_bloco_t **csubmatrizv2(int mat_lin, int mat_col, int divisor);
matriz_bloco_t **particionar_matriz(int **matriz, int mat_lin, int mat_col, int orientacao, int divisor);


 /* //restaurei para ter de exemplo apenas
  int gerar_matriz(int **matriz, int linha, int coluna, int valor);
  int zerar_matriz (int **matriz, int linha, int coluna);
  int imprimir_matriz (int **matriz, int linha, int coluna);
  int comparar_matriz (int **matriza, int **matrizb, int linha, int coluna);
  int **liberar_matriz (int **matriz, int linha, int coluna);
  int **alocar_matriz (int linha, int coluna);

  // submatriz
  int gerar_submatriz (int **mat_origem, int **submatriz, bloco_t *bloco);
  matriz_bloco_t **particionar_matriz (int **matriz, int mat_lin, int mat_col, int orientacao, int nro_submatrizes);
  matriz_bloco_t **liberar_submatriz (matriz_bloco_t **submatriz, int nro_submatriz);
  matriz_bloco_t **constroi_submatrizv2 (int mat_lin, int mat_col, int divisor);*/