#include "matrizv3.h"
#include "toolsv3.h"

mymatriz res; //auxiliar, grava resultado da soma

//As matrizes envolvidas na adição devem ser da mesma ordem, quer dizer, devem ter o mesmo
//número de linhas e colunas. A matriz resultante terá a mesma configuração.

mymatriz *msomar (mymatriz *mat_a, mymatriz *mat_b, int tipo){

    int i_max, j_max; //auxiliares para controle de aninhamento

    //matriz resultado
	res.matriz = NULL;
	res.lin = mat_a->lin;
	res.col = mat_a->col;

    //realiza a alocação de memória para matriz resultado
    if (malocar(&res)) {
		printf ("ERROR: Out of memory\n");
	}else{
        mzerar(&res);
    }

    //define aninhamento, conforme parametro tipo
    i_max = mat_a->lin;
    j_max = mat_a->col;
    if (tipo == 1){ //tipo = 1: ordem de aninhamento ji
        i_max = mat_a->col;
        j_max = mat_a->lin;
    }
    
    //realiza a soma dos elementos da matriz a e b
    for (int i = 0; i < i_max; i++){
        for (int j = 0; j < j_max; j++){

            
            if (tipo == 0){ //tipo = 0: ordem de aninhamento ij
                //printf("[a] %d ", mat_a->matriz[i][j] );
                //printf("[b] %d ", mat_b->matriz[i][j]);
                res.matriz[i][j] = mat_a->matriz[i][j] + mat_b->matriz[i][j];
                //printf("[r] %d\n", res.matriz[i][j]);

            }else{ //tipo = 1: ordem de aninhamento ji
                //printf("[a] %d ", mat_a->matriz[i][j] );
                //printf("[b] %d ", mat_b->matriz[i][j]);
                res.matriz[j][i] = mat_a->matriz[j][i] + mat_b->matriz[j][i];
                //printf("[r] %d\n", res.matriz[i][j]);

            }
            
        }
    }
    printf(" in msomar returned the address %p\n", &res);
    return &res;
}


//As matrizes envolvidas na adição devem ser da mesma ordem, quer dizer, devem ter o mesmo
//número de linhas e colunas. A matriz resultante terá a mesma configuração.


mymatriz *mmultiplicar (mymatriz *mat_a, mymatriz *mat_b, int tipo){

    int i_max, j_max, k_max; //auxiliares para controle de aninhamento

    //matriz resultado
	res.matriz = NULL;
	res.lin = mat_a->lin;
	res.col = mat_b->col;

    //realiza a alocação de memória para matriz resultado
    if (malocar(&res)) {
		printf ("ERROR: Out of memory\n");
	}else{
        mzerar(&res);
    }

    //define aninhamento, conforme parametro tipo
    i_max = mat_a->lin;
    j_max = mat_b->col;
    k_max = mat_b->lin;
    if (tipo == 1){ //tipo = 1: ordem de aninhamento jik
        i_max = mat_b->col;
        j_max = mat_a->lin;
        k_max = mat_a->col;
    }

    //realiza a multiplicacao dos elementos da matriz a e b
    for (int i = 0; i < i_max; i++){
        for (int j = 0; j < j_max; j++){

            int temp = 0;
            for (int k = 0; k < k_max; k++){

                temp += mat_a->matriz[i][k] * mat_b->matriz[k][j];
                //printf("a[%d][%d] = %d\n", i, k, mat_a->matriz[i][k] );
                //printf("b[%d][%d] = %d\n", k, i, mat_b->matriz[k][j] );
                //printf("%d x %d = %d (%d)\n", mat_a->matriz[i][k], mat_b->matriz[k][j], mat_a->matriz[i][k] * mat_b->matriz[k][j], temp);

            }

            res.matriz[i][j] = temp;
            //printf("r[%d][%d] = %d \n\n", i, j, res.matriz[i][j]);
            
        }
    }

    return &res;
}


//TODO - COMMENTS
//TODO - validar tamanho das matrizes enviadas por parametro, se pode somar e multiplicar mesmo