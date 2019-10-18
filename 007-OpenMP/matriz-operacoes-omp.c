#include <omp.h>
#include "matrizv3.h"
#include "matriz-operacoesv3.h"

/*
function multiplicarOMP
Realiza multiplicacao de matriz sequencial, para threads usando OMP
@return 0
@param *mat_a, ponteiro para mymatriz base para multiplicacao
@param *mat_b, ponteiro para mymatriz base para multiplicacao
@param *mat_c, ponteiro para mymatriz resultado
@param tid, inteiro que representa o número da thread
@param ntasks, inteiro que representa o número total de threads
*/
int multiplicarOMP(mymatriz *mat_a, mymatriz *mat_b, mymatriz *mat_c, int tid, int ntasks)
{
    
    //inicializa variáveis de controle dos for`s
    int i_max = mat_a->lin;
    int j_max = mat_b->col;
    int k_max = mat_a->col;

    for (int i = tid; i < i_max; i += ntasks){
        for (int k = 0; k < k_max; k++){
            for (int j = 0; j < j_max; j++){
                mat_c->matriz[i][j] += mat_a->matriz[i][k] * mat_b->matriz[k][j];
                //printf("mat_c->matriz[%d][%d] = %d, calculado por thread %d\n",i,j,mat_c->matriz[i][j],tid);
            }
        }
    }

    return 0;
}

/*
function multiplicarOMPblocos
Realiza multiplicacao de matriz em bloco, para threads usando OMP
@return 0
@param *mat_suba, ponteiro para matriz_bloco_t base para multiplicacao
@param *mat_subb, ponteiro para matriz_bloco_t base para multiplicacao
@param *mat_subc, ponteiro para matriz_bloco_t resultado
*/
int multiplicarOMPblocos(matriz_bloco_t *mat_suba, matriz_bloco_t *mat_subb, matriz_bloco_t *mat_subc)
{
    multiplicar_submatriz(mat_suba, mat_subb, mat_subc);   
    return 0;
}