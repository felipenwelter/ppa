#include "matrizv3.h"

// gerência de matrizes
int malocar (mymatriz *matriz) {
  printf("Alocando matriz...\n");

  if(matriz->lin <= 0) {
    printf("ERRO: número de linhas indefinido.\n");
    return 0;
  }

  if(matriz->col <= 0) {
    printf("ERRO: número de colunas indefinido.\n");
    return 0;
  }

  int **linhas = (int **) malloc(matriz->lin * sizeof(int *));
  matriz->matriz = linhas;

  for(int i = 0; i < matriz->lin; i++) {
    matriz->matriz[i] = (int *) malloc(matriz->col * sizeof(int));
  }

  printf("Concluída alocação de matriz.\n\n");

  return 1;
}

int mgerar(mymatriz *matriz, int valor) {
  printf("Gerando matriz com valor %i ...\n", valor);

  if(matriz->matriz == NULL) {
      printf("ERRO: Matriz inexistente.\n");
      return 0;
  }

  for(int i = 0; i < matriz->lin; i++) {
    for(int j = 0; j < matriz->col; j++) {
      matriz->matriz[i][j] = valor;
    }
  }

  printf("Concluída geração de matriz.\n\n");

  return 1;
}

int mimprimir (mymatriz *matriz) {
  printf("Imprimindo matriz...\n");

  if(matriz->matriz == NULL) {
      printf("ERRO: Matriz inexistente.\n");
      return 0;
  }

  for(int i = 0; i < matriz->lin; i++) {
    printf("\n");
    for(int j = 0; j < matriz->col; j++) {
      printf("%i\t", matriz->matriz[i][j]);
    }
  }

  printf("\n\nFim impressão matriz.\n\n");

  return 1;
}

int mzerar (mymatriz *matriz) {
  printf("Zerando matriz...\n");

  if(matriz->matriz == NULL) {
      printf("ERRO: Matriz inexistente.\n");
      return 0;
  }

  for(int i = 0; i < matriz->lin; i++) {
    for(int j = 0; j < matriz->col; j++) {
      matriz->matriz[i][j] = 0;
    }
  }

  printf("Concluído processo de 'zerar' matriz.\n\n");

  return 1;
}

int mliberar (mymatriz *matriz) {
  printf("Liberando matriz...\n");

  if(matriz->matriz == NULL) {
      printf("ERRO: Matriz inexistente.\n");
      return 0;
  }

  for(int i = 0; i < matriz->lin; i++) {
    free(matriz->matriz[i]);
  }

  free(matriz->matriz);

  printf("Concluído processo de 'liberar' matriz.\n\n");

  return 1;
}

int mcomparar (mymatriz *mat_a, mymatriz *mat_b) {
  if(mat_a == NULL || mat_a->matriz == NULL) {
    printf ("ERRO: Matriz A inexistente\n\n");
    return 0;
  }

  if(mat_b == NULL || mat_b->matriz == NULL) {
    printf ("ERRO: Matriz B inexistente\n\n");
    return 0;
  }

  if(mat_a->lin != mat_b->lin) {
    printf ("ERRO: Matrizes com número de linhas diferentes.\n");
    printf ("\t- matriz A %i linhas.\n", mat_a->lin);
    printf ("\t- matriz B %i linhas.\n\n", mat_b->lin);
    return 0;
  }

  if(mat_a->col != mat_b->col) {
    printf ("ERRO: Matrizes com número de colunas diferentes.\n");
    printf ("\t- matriz A %i colunas.\n", mat_a->col);
    printf ("\t- matriz B %i colunas.\n\n", mat_b->col);
    return 0;
  }

  for(int i = 0; i < mat_a->lin; i++) {
    for(int j = 0; j < mat_a->col; j++) {
      if(mat_a->matriz[i][j] != mat_b->matriz[i][j]) {
        printf("ERRO: Matriz diferente.\n");
        printf("\t- elemento: linha %i, coluna %i\n", i+1, j+1);
        printf("\t- valor na matriz A %i\n", mat_a->matriz[i][j]);
        printf("\t- valor na matriz B %i\n\n", mat_b->matriz[i][j]);
        return 0;
      }
    }
  }

  printf("Matrizes idênticas.\n\n");

  return 1;
}

// submatriz
int gerar_submatriz (int **mat_origem, matriz_bloco_t *submatriz, bloco_t *bloco) {
  printf ("ERRO: Método não implementado.\n");
  exit (1);
}

int imprimir_submatriz (matriz_bloco_t *submatriz) {
  printf ("ERRO: Método não implementado.\n");
  exit (1);
}

matriz_bloco_t **particionar_matriz (int **matriz, int mat_lin, int mat_col, int orientacao, int divisor) {
  printf ("ERRO: Método não implementado.\n");
  exit (1);
}

matriz_bloco_t **liberar_submatriz (matriz_bloco_t **submatriz) {
  printf ("ERRO: Método não implementado.\n");
  exit (1);
}

int imprimir_bloco (matriz_bloco_t *submatriz) {
  printf ("ERRO: Método não implementado.\n");
  exit (1);
}

matriz_bloco_t **constroi_submatriz (int **matriz, int mat_lin, int mat_col, int divisor) {
  printf ("ERRO: Método não implementado.\n");
  exit (1);
}

matriz_bloco_t **constroi_submatrizv2 (int mat_lin, int mat_col, int divisor) {
  printf ("ERRO: Método não implementado.\n");
  exit (1);
}
