#include <unistd.h>
#include "matriz-operacoes-mpi.h"
#include <mpi.h>

//Variaveis executar calculo da média
int ntasks = 4; //deve ser igual nro_submatrizes
int nro_submatrizes = 4; //deve ser igual ntasks
int count_for = 10; //numero de repeticoes para média de runtime

int N = 4;

void print_results(char *prompt, int a[N][N], int lin, int col);

typedef struct
{
    int tid;
    int ntasks;
    mymatriz *mat_a;
    mymatriz *mat_b;
    mymatriz *mat_c;
    matriz_bloco_t *mat_bloco_a;
    matriz_bloco_t *mat_bloco_b;
    matriz_bloco_t *mat_bloco_c;
} param_t;

/*
function exec_multi_thread
Instancia cada thread para multiplicacao de matriz sequencial
@return NULL
@param *arg, ponteiro para objeto param_t
*/
void *exec_multi_thread(void *arg)
{
    param_t *p = (param_t *)arg;

	int rank, size;

    int *arrayA, *arrayB, *arrayC;
    int *recA, *recB, *recC;
    int sizeA, sizeB, sizeC;
    int pos;

    sizeA = p->mat_a->lin * p->mat_a->col;
    sizeB = p->mat_b->lin * p->mat_b->col;
    sizeC = p->mat_a->lin * p->mat_b->col;
    arrayA = (int*) malloc( sizeA * sizeof(int*) );
    arrayB = (int*) malloc( sizeB * sizeof(int*) );
    arrayC = (int*) malloc( sizeC * sizeof(int*) );

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (p->tid == 0){

        pos = 0;
        for (int i = 0; i < p->mat_a->lin; i++) {
            for (int j = 0; j < p->mat_a->col; j++){
                arrayA[pos++] = p->mat_a->matriz[i][j];
            }
        }

        pos = 0;
        for (int i = 0; i < p->mat_b->lin; i++) {
            for (int j = 0; j < p->mat_b->col; j++){
                arrayB[pos++] = p->mat_b->matriz[i][j];
            }
        }

    }

    //allocating local data
    recA = (int*) malloc( sizeA/size * sizeof(int*) );
    recC = (int*) malloc( sizeC/size * sizeof(int*) );

	if (arrayB == NULL ){
        printf ("NULL\n");
        arrayB = (int*) malloc( sizeB * sizeof(int*) );
    }

    // now p0 scatter matrix sendA to all 
    MPI_Scatter( arrayA , sizeA/size , MPI_INT , recA , sizeA/size , MPI_INT , 0, MPI_COMM_WORLD );

    //if (rank == 4){
    //    printf("thread %d - ",rank);
    //    for (int i = 0; i < (sizeA/size); i++){
    //        printf("%d ",recA[i]);
    //    }
    //    printf("\n");
    //}

    //now p0 broadcast sendB to all others
    MPI_Bcast ( arrayB, sizeB , MPI_INT , 0 , MPI_COMM_WORLD );

    //sleep(rank);
	// all do this part to calculate recC as multiplicated matrix
    int n = p->mat_b->col;	
    for ( int i=0 ; i < (p->mat_a->lin/size); i++ ){
        for ( int j = 0 ; j < p->mat_b->col; j++ ){
            recC[i*n+j] = 0;
            //printf("[%d] recC[%d] = %d when i = %d and j = %d\n ", rank, (i * p->mat_b->col) + j, recC[(i * p->mat_b->col) + j], i, j);
            for ( int k = 0 ; k < p->mat_a->col ; k++ ){
                //printf("%d ", i*n+j);
                recC[i*n+j] += recA[i*n+k]*arrayB[k*n+j];
                //printf (" process %d recC [%d] = % d  | %d x %d \n" , rank , i*n+j , recC[i*n+j] , recA[i*n+k], arrayB[k*n+j]) ;    
            }
        }
    }

    //sleep(rank);
    //printf("\nthread %d \n", rank);
    //for (int i = 0; i < sizeC/size; i++)
    //    printf("%d ", recC[i]);
    //printf("\n");

    // now p0 will gather all result data from all prcesses
    MPI_Gather( recC , sizeC/size , MPI_INT , arrayC , sizeC/size , MPI_INT , 0, MPI_COMM_WORLD ) ;

	MPI_Barrier(MPI_COMM_WORLD); /* barrier is needed if no necessary synchronization for the timing is ensured yet */

    if (rank == 0){
        printf("\n\n");
        for (int i = 0; i < sizeC; i++){
            printf("arrayC[%d] = %d\n", i, arrayC[i]);
        }
    }

    return 0;
}



void print_results(char *prompt, int a[N][N], int lin, int col)
{
    int i, j;

    printf ("\n\n%s\n", prompt);
    for (i = 0; i < lin; i++) {
            for (j = 0; j < col; j++) {
                    printf(" %d", a[i][j]);
            }
            printf ("\n");
    }
    printf ("\n\n");
}

/*
function exec_multi_thread_blocos
Instancia cada thread para multiplicacao de matriz em bloco
@return NULL
@param *arg, ponteiro para objeto param_t
*/
void *exec_multi_thread_blocos(void *arg)
{
    param_t *p = (param_t *)arg;
    multiplicarOMPblocos(p->mat_bloco_a, p->mat_bloco_b, p->mat_bloco_c);
    return NULL;
}








int loadMatrix(char* matrix_name, mymatriz* address){

    //variaveis para manipulacao de arquivos no disco
    FILE *fmat;
    int nr_line;
    int *vet_line = NULL;
    int N, La;

    //Leitura da Matriz
    fmat = fopen(matrix_name, "r");
    if (fmat == NULL)
    {
        printf("ERRO: na abertura dos arquivos.\n");
        exit(1);
    }
    extrai_parametros_matriz(fmat, &N, &La, &vet_line, &nr_line);
    address->matriz = NULL;
    address->lin = N;
    address->col = La;

    if (malocar(address))
    {
        printf("ERRO: na alocacao de memoria para mat_a.\n");
        exit(1);
    }

    filein_matriz(address->matriz, N, La, fmat, vet_line, nr_line);
    free(vet_line);
    fclose(fmat);

    return 0;
    
}


double seqMultiplication(mymatriz* mat_a, mymatriz* mat_b, mymatriz* mat_c){

    double start_time, end_time;
    double tempo_MATRIZ_SeqC = 0;

    char filename[100];
    FILE *fmat;

    // Multiplicação Sequencial    
    for (int count = 0; count < count_for; count++)
    {   
        //printf("\rExecutando multiplicação sequencial %d de %d", count+1, count_for);
        //fflush(stdout);

        start_time = wtime();
        mmultiplicar(mat_a, mat_b, mat_c, 1);  //1=mais rápido (2.04), 5=mais lento (5.94)
        end_time = wtime();
        tempo_MATRIZ_SeqC += end_time - start_time;
        //printf(" sequencial %d. tempo: %.20f \t avg= %.20f\n",count, end_time - start_time, tempo_MATRIZ_SeqC / (count+1));
    }

    sprintf(filename, "MATRIZ_SeqC.result");
    fmat = fopen(filename, "w");
    fileout_matriz(mat_c, fmat);
    fclose(fmat);

    return tempo_MATRIZ_SeqC;
}





double blcMultiplication(mymatriz* mat_a, mymatriz* mat_b, mymatriz* mat_c){

    double start_time, end_time;
    double tempo_MATRIZ_SeqBlC = 0;

    //variaveis para controle de blocos
    matriz_bloco_t **Vsubmat_a = NULL;
    matriz_bloco_t **Vsubmat_b = NULL;
    matriz_bloco_t **Vsubmat_c = NULL;

    char filename[100];
    FILE *fmat;

    for (int count = 0; count < count_for; count++)
    {
        //printf("\rExecutando multiplicação sequencial em bloco %d de %d", count+1, count_for);
        //fflush(stdout);

        start_time = wtime();
        Vsubmat_a = particionar_matriz(mat_a->matriz, mat_a->lin, mat_a->col, 1, nro_submatrizes);
        Vsubmat_b = particionar_matriz(mat_b->matriz, mat_b->lin, mat_b->col, 0, nro_submatrizes);
        Vsubmat_c = csubmatrizv2(mat_a->lin, mat_b->col , nro_submatrizes);

        //multiplicacao de blocos
        for (int i = 0; i < nro_submatrizes; i++){
            multiplicar_submatriz (Vsubmat_a[i], Vsubmat_b[i], Vsubmat_c[i]);
        }

        //matriz resultado
        mat_c->matriz = NULL;
        mat_c->lin = mat_a->lin;
        mat_c->col = mat_b->col;

        //realiza a alocação de memória para matriz resultado
        if (malocar(mat_c)) {
            printf ("ERROR: Out of memory\n");
            exit(1);
        }else{
            mzerar(mat_c);
        }

        //soma os blocos separados
        msomar(Vsubmat_c[0]->matriz,Vsubmat_c[1]->matriz, mat_c, 1);
        for (int i = 2; i < nro_submatrizes; i++){
            msomar(mat_c,Vsubmat_c[i]->matriz, mat_c, 1);	
        }

        end_time = wtime();
        tempo_MATRIZ_SeqBlC += end_time - start_time;
        //printf(" bloco %d. tempo: %.20f \t avg= %.20f\n",count, end_time - start_time, tempo_MATRIZ_SeqBlC / (count+1));
    }

    sprintf(filename, "MATRIZ_SeqBlC.result");
    fmat = fopen(filename, "w");
    fileout_matriz(mat_c, fmat);
    fclose(fmat);
    
    return tempo_MATRIZ_SeqBlC;

}




/*
function main
Funcao principal para realizar a multiplicacao de matrizes sequencial, sequencial por thread,
em bloco e em bloco por thread, comparando resultados e mostrando tempo e speedup.
@return 0
@param argv, devem ser informadas a matriz_a e matriz_b e opcionalmente número de threads/blocos
*/
int main(int argc, char *argv[])
{
   
    //variaveis para armazenar matrizes origem e de resultado
    mymatriz mat_a, mat_b;
    //mymatriz res_matriz_SeqC;
    //mymatriz res_matriz_SeqBlC;
    mymatriz res_matriz_ThreadC;
    

    //double tempo_MATRIZ_SeqC = 0;
    //double tempo_MATRIZ_SeqBlC = 0;

    //variaveis para controle de threads
    param_t *args;

	int rank, size;//,i;
	//int tag=0;

    MPI_Init(&argc, &argv);

        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        MPI_Comm_size(MPI_COMM_WORLD, &size);

        loadMatrix(argv[1], &mat_a);
        loadMatrix(argv[2], &mat_b);
        
        if (rank == 0){
            //mimprimir(&mat_a);
            //mimprimir(&mat_b);
        }

        if(rank == 0) {
            //printf("[%d] Master called\n", rank);


            ////tempo_MATRIZ_SeqC = seqMultiplication(&mat_a, &mat_b, &res_matriz_SeqC);
            //printf("\n\tTempo Médio MATRIZ_SeqC:\t%.6f sec \n", tempo_MATRIZ_SeqC / count_for);
            ////tempo_MATRIZ_SeqBlC = blcMultiplication(&mat_a, &mat_b, &res_matriz_SeqBlC);




            // Impressao dos resultados de tempo
            ////printf("\n\n\tCOMPARAR MATRIZ_SeqC c/ MATRIZ_SeqBlC\n\t");
            ////mcomparar(&res_matriz_SeqC, &res_matriz_SeqBlC);            

            ////printf("\n\tTempo Médio MATRIZ_SeqC:\t%.6f sec \n", tempo_MATRIZ_SeqC / count_for);
            ////printf("\tTempo Médio MATRIZ_SeqBlC:\t%.6f sec\n", tempo_MATRIZ_SeqBlC / count_for );

            //Liberação de memória
            ////mliberar(&res_matriz_SeqC);
            ////mliberar(&res_matriz_SeqBlC);

       

        }else{ 
            
        }


        int tid = rank;
        args = (param_t *)malloc(ntasks * sizeof(param_t));

        args[tid].tid = tid;
        args[tid].ntasks = size;
        args[tid].mat_a = &mat_a;
        args[tid].mat_b = &mat_b;
        args[tid].mat_c = &res_matriz_ThreadC;
        
        exec_multi_thread((void *)(args + tid));


int teste;



    MPI_Finalize();


    return 0;
}








