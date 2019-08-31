#include "matrizv3.h"
#include "toolsv3.h"

/*
function malocar
Alocação espaço de memória para uma matriz
@return result, inteiro 0 para sucesso e outro valor para erro
@param matriz, ponteiro para objeto do tipo mymatriz
*/
int malocar (mymatriz *matriz){

    int **new_matriz; //ponteiro para a nova matriz

    //verifica parametros recebidos
    if (matriz->lin < 1 || matriz->col < 1) { 
      printf ("** Erro: Parametro invalido **\n");
      return (-1);
    }

    // aloca linhas da matriz
    new_matriz = (int **) calloc (matriz->lin, sizeof(int *));	//Um vetor de 'lin' ponteiros para int
    if (new_matriz == NULL) { //verifica se foi alocado memória para a matriz
      printf ("** Erro: Memoria Insuficiente **\n");
      return (-1);
    }

    // para cada linha aloca espaço para as colunas da matriz
    for ( int i = 0; i < matriz->lin; i++ ) {
      new_matriz[i] = (int*) calloc (matriz->col, sizeof(int));	// 'lin' vetores de 'col' ints
      if (new_matriz[i] == NULL) {
        printf ("** Erro: Memoria Insuficiente **\n");
        return (-1);
      }
    }

    //aponta para nova matriz
    matriz->matriz = new_matriz;

    return (0); // retorna o ponteiro para a matriz
}


/*
function mgerar
Inicializa matriz com valores
@return result, inteiro 0 para sucesso e outro valor para erro
@param matriz, ponteiro para objeto do tipo mymatriz
@param valor, indica regra para preenchimento da matriz, sendo:
              -9999: preenche com valores aleatórios
              outro valor: preenche com zero
*/
int mgerar(mymatriz *matriz, int valor){
  
  int value = 0; //auxiliar

  //verifica se foi alocado memória para a matriz
  if (matriz == NULL){
    printf ("** Erro: Memoria Insuficiente **\n");
    return (-1);
  }

  /* srand(wtime(NULL)) inicializa o gerador de números aleatórios com o valor
  da função wtime(NULL). Assim, a cada execução o valor da "semente" será diferente.
  */
  srand(wtime(NULL));

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

  return (0);
}


/*
function mimprimir
Imprime toda a matriz
@return result, inteiro 0 para sucesso e outro valor para erro
@param matriz, ponteiro para objeto do tipo mymatriz
*/
int mimprimir (mymatriz *matriz){

  //verifica se foi alocado memória para a matriz
  if (matriz == NULL){
    printf ("** Erro: Memoria Insuficiente **\n");
    return (-1);
  }
    
  //imprime primeira linha de cabeçalho
  printf("\t");
  for (int j = 0; j < matriz->col; j++){
      printf("#%d\t", j);
  }
  printf("\n");

  //imprime o conteúdo da matriz
  for (int i = 0; i < matriz->lin; i++){
    printf("%d:\t", i); //imprime número da linha
    for (int j = 0; j < matriz->col; j++){
      printf("[%d]\t", matriz->matriz[i][j]);
    }
    printf("\n");
  }
  printf("\n");
  return (0);
}


/*
function mzerar
Zera o conteúdo de todas as posições da matriz
@return result, inteiro 0 para sucesso e outro valor para erro
@param matriz, ponteiro para objeto do tipo mymatriz
*/
int mzerar (mymatriz *matriz){
  
  //verifica se foi alocado memória para a matriz
  if (matriz == NULL){
    printf ("** Erro: Memoria Insuficiente **\n");
    return (-1);
  }

  //chama mgerar para zerar cada posição da matriz
  mgerar(matriz,0);

  return (0);
}


/*
function mliberar
Libera a memória alocada para a matriz
@return result, inteiro 0 para sucesso e outro valor para erro
@param matriz, ponteiro para objeto do tipo mymatriz
*/
int mliberar (mymatriz *matriz){

  if (matriz != NULL){
    //libera a alocação de cada linha
    for (int i = 0; i < matriz->lin; i++){
        free(matriz->matriz[i]);
    }
    free(matriz->matriz);
  }
  
  return (0);
}

/*
function mcomparar
Compara duas matrizes e indica se são exatamente iguais
@return result, inteiro 0 para matrizes iguais e 1 para diferentes, outro valor para erro
@param mat_a, ponteiro para objeto do tipo mymatriz
@param mat_b, ponteiro para objeto do tipo mymatriz
*/
int mcomparar (mymatriz *mat_a, mymatriz *mat_b){

  //verifica se foi alocado memória para a matriz
  if ( (mat_a == NULL) || (mat_b == NULL)) {
    printf ("** Erro: Memoria Insuficiente **\n");
    return (-1);
  }

  //verifica se matrizes tem mesmo tamanho
  if ( (mat_a->lin != mat_b->lin) || (mat_a->col != mat_b->col) ){
    printf ("** Erro: Matrizes tem tamanhos diferentes **\n");
    return (-1);
  }

  for (int i = 0; i < mat_a->lin; i++){
    for (int j = 0; j < mat_a->col; j++){
      if ( mat_a->matriz[i][j] != mat_b->matriz[i][j] ){
        printf ("** Matrizes são diferentes **\n");
        return (1);
      }
    }
  }

  printf("** Matrizes são iguais **\n");

  return (0);
}
