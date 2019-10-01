#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int **alocar_matriz(int linha, int coluna){

    int **matriz;
    matriz = (int**) malloc(linha*sizeof(int*));

    for (int i = 0; i < linha; i++){
        matriz[i] = (int*) malloc(coluna*sizeof(int));
    }
    return matriz;
}

int **liberar_matriz(int **matriz, int linha, int coluna){

    for (int i = 0; i < linha; i++){
        free(matriz[i]);
    }
    free(matriz);
    return matriz;
}

int main (int argc, char *argv[]){
    
    int **matriz;
    int i;

    #pragma omp parallel for num_threads (3)
    for (i=0; i < 6; i++){
        int k = omp_get_thread_num();
        printf("thread %d\n",k);
    }

    #pragma omp parallel
    {
        int t = omp_get_thread_num();
        printf("hello from thread %d\n", t);
        #pragma omp master
        {
            printf("the master is %d\n",omp_get_thread_num());
        }
    }

    matriz = alocar_matriz(2,5);

    for (int i = 0; i < 2; i++){
        for (int j = 0; j < 5; j++){
            matriz[i][j] = (i+j)*(i+j);
        }
    }

    for (int i = 0; i < 2; i++){
        for (int j = 0; j < 5; j++){
            printf("matriz[%d][%d] = %d\n", i, j, matriz[i][j]);
        }
    }

    liberar_matriz(matriz,2,5);
    return 0;
}