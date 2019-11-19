//#include <mpi.h>
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

	//int rank,size,i;
	//int tag=0;
	//MPI_Status status;
	//char msg[20];

    //MPI_Init(NULL, NULL);

       // MPI_Comm_rank(MPI_COMM_WORLD, &rank);
       // MPI_Comm_size(MPI_COMM_WORLD, &size);


        //MPI_Bcast(void *buffer, int count, MPI_Datatype, int root, MPI_Comm comm);

        //strcpy(msg,"Hello World!\n");
        //MPI_Bcast(msg, 20, MPI_CHAR, 0, MPI_COMM_WORLD);
        //printf("Message received: %s\n", msg);

        /*if(rank == 0) {
            strcpy(msg,"Hello World!\n");
            for(i=1;i<size;i++) {
                printf("0 enviando 20 para %d\n", i);
                MPI_Send(msg,20,MPI_CHAR,i,tag, MPI_COMM_WORLD);
            }
        } else {
            printf("%d esta esperando\n", rank);
            MPI_Recv(msg,20,MPI_CHAR,0,tag, MPI_COMM_WORLD, &status);
            printf("Message received: %s\n", msg);
        }*/

    //MPI_Finalize();


    //inicializa variáveis de controle dos for`s
    /*int i_max = mat_a->lin;
    int j_max = mat_b->col;
    int k_max = mat_a->col;

    for (int i = tid; i < i_max; i += ntasks){
        for (int k = 0; k < k_max; k++){
            for (int j = 0; j < j_max; j++){
                mat_c->matriz[i][j] += mat_a->matriz[i][k] * mat_b->matriz[k][j];
                //printf("mat_c->matriz[%d][%d] = %d, calculado por thread %d\n",i,j,mat_c->matriz[i][j],tid);
            }
        }
    }*/

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