#include "matrizv3.h"

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
  
  int value = 0;

  if (matriz == NULL){
    printf(" Problema - Matriz não alocada.\n");
    return (-1);
  }

  /* srand(time(NULL)) objetiva inicializar o gerador de números aleatórios
  com o valor da função time(NULL). Este por sua vez, é calculado
  como sendo o total de segundos passados desde 1 de janeiro de 1970
  até a data atual.
  Desta forma, a cada execução o valor da "semente" será diferente.
  */
  srand(time(NULL));

  //alimenta matriz com valores
  for (int i = 0; i < matriz->lin; i++){
    for (int j = 0; j < matriz->col; j++){
      switch(valor){
      case -9999:
        value = rand() % 100;
        break;
      default:
        value = 0;
        break;
      }

      matriz->matriz[i][j] = value;

    }
  }

  return 0;
}



int mimprimir (mymatriz *matriz){

  if (matriz == NULL){
    printf(" Problema - Matriz não alocada.\n");
    return (-1);
  }
    
  //imprime primeira linha de cabeçalho
  printf("   ");
  for (int j = 0; j < matriz->col; j++){
      //printf(" %d ", j);  . fica ruim quando valores maior que um digito
  }
  printf("\n");

  //imprime o conteúdo da matriz
  for (int i = 0; i < matriz->lin; i++){
    printf("%d: ", i); //imprime número da linha
    for (int j = 0; j < matriz->col; j++){
      printf("[%d]", matriz->matriz[i][j]);
    }
    printf("\n");
  }

  return (0);
}



int mzerar (mymatriz *matriz){
  
  if (matriz == NULL){
    printf(" Problema - Matriz não alocada.\n");
    return (0);
  }

  //zera cada posição da matriz
  for (int i = 0; i < matriz->lin; i++){
    for (int j = 0; j < matriz->col; j++){
      matriz->matriz[i][j] = 0;
    }
  }

  return 0;
}

int mliberar (mymatriz *matriz){

  if (matriz != NULL){
    //libera a alocação de cada linha
    for (int i = 0; i < matriz->lin; i++){
        free(matriz->matriz[i]);
    }
    free(matriz->matriz);
  }
  
  return 0;
}

int mcomparar (mymatriz *mat_a, mymatriz *mat_b){
    printf("mcomparar");
    return 0;
}
