#include <unistd.h>
#include "matriz-operacoes-mpi.h"
#include <mpi.h>

//variables for the average calculation
int nro_submatrizes = 4; //must be compatible (divided) to the number of threads
int count_for = 10; //repetition amount for the average calc

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

//prototype declarations
int loadMatrix(char* matrix_name, mymatriz* address);
double seqMultiplication(mymatriz* mat_a, mymatriz* mat_b, mymatriz* mat_c);
double blcMultiplication(mymatriz* mat_a, mymatriz* mat_b, mymatriz* mat_c);
double exec_multi_thread(void *arg);
double exec_multi_thread_blocos(param_t *p, mymatriz* res);

/*
function main
Execute the matrix multiplication - sequential, sequential by threads, blocks and
blocks by threads, comparing the results and calculating time spent and speedup.
@return 0
@param argv, name of matrix_a and matrix_b
*/
int main(int argc, char *argv[])
{
    //variables for origin matrixes and result matrixes
    mymatriz mat_a, mat_b;
    mymatriz res_matriz_SeqC;
    mymatriz res_matriz_SeqBlC;
    mymatriz res_matriz_ThreadC;
    mymatriz res_matriz_ThreadBlC;
    
    //variables to control the time spent and calculations
    double tempo_MATRIZ_SeqC = 0;
    double tempo_MATRIZ_SeqBlC = 0;
    double tempo_MATRIZ_ThreadC = 0;
    double tempo_MATRIZ_ThreadBlC = 0;
    double speedup_seqC = 0;
    double speedup_BlC = 0;

    //variables used for thread control
    param_t *args;
    param_t *argsBlc;
	int rank, size;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    loadMatrix(argv[1], &mat_a);
    loadMatrix(argv[2], &mat_b);
        
    if (rank == 0){
        if (mat_a.lin != mat_a.col){
            printf ("** ERRO: Matriz A não é uma matriz quadrada **\n");
            exit(1);
        }
        if (mat_b.lin != mat_b.col){
            printf ("** ERRO: Matriz B não é uma matriz quadrada **\n");
            exit(1);
        }
        if (mat_a.lin != mat_b.lin){
            printf ("** ERRO: Matriz A e Matriz B não possuem as mesmas configurações **\n");
            exit(1);
        }
        if ((mat_a.lin % size) > 0){  //the number of rows and columns must be divisible by the number of threads
            printf ("** ERRO: Número de threads não é proporcional ao tamanho da matriz **\n");
            exit(1);
        }
    }

    if(rank == 0) {
        
        //----------run the sequential multiplication----------
        tempo_MATRIZ_SeqC = seqMultiplication(&mat_a, &mat_b, &res_matriz_SeqC);
        //-----------------------------------------------------

        //----------run the blocks multiplication--------------
        tempo_MATRIZ_SeqBlC = blcMultiplication(&mat_a, &mat_b, &res_matriz_SeqBlC);
        //-----------------------------------------------------
    }

    //----------run the multithread multiplication----------
    
    //initialize result variables
    res_matriz_ThreadC.matriz = NULL;
    res_matriz_ThreadC.lin = mat_a.lin;
    res_matriz_ThreadC.col = mat_b.col;
    malocar(&res_matriz_ThreadC);
    
    args = (param_t *)malloc(size * sizeof(param_t));
    args[rank].tid = rank;
    args[rank].ntasks = size;
    args[rank].mat_a = &mat_a;
    args[rank].mat_b = &mat_b;
    args[rank].mat_c = &res_matriz_ThreadC;
    
    //run multiplication
    tempo_MATRIZ_ThreadC = exec_multi_thread((void *)(args + rank));
    //------------------------------------------------------


    //----------run the multithread blocks multiplication----------

    //initialize block control variables
    matriz_bloco_t **Vsubmat_a = NULL;
    matriz_bloco_t **Vsubmat_b = NULL;
    matriz_bloco_t **Vsubmat_c = NULL;
    nro_submatrizes = size-1; //thread 0 = master, do not compute multiplications

    Vsubmat_a = particionar_matriz(mat_a.matriz, mat_a.lin, mat_a.col, 1, nro_submatrizes);
    Vsubmat_b = particionar_matriz(mat_b.matriz, mat_b.lin, mat_b.col, 0, nro_submatrizes);
    Vsubmat_c = csubmatrizv2(mat_a.lin, mat_b.col, nro_submatrizes);

    argsBlc = (param_t *)malloc(nro_submatrizes * sizeof(param_t));

    for (int i = 0; i < nro_submatrizes; i++){
        argsBlc[i].tid = i;
        argsBlc[i].ntasks = nro_submatrizes;
        argsBlc[i].mat_bloco_a = Vsubmat_a[i];
        argsBlc[i].mat_bloco_b = Vsubmat_b[i];
        argsBlc[i].mat_bloco_c = Vsubmat_c[i];
    }

    //initialize result variables
    res_matriz_ThreadBlC.matriz = NULL;
    res_matriz_ThreadBlC.lin = mat_a.lin;
    res_matriz_ThreadBlC.col = mat_b.col;
    malocar(&res_matriz_ThreadBlC);

    //run multiplication
    tempo_MATRIZ_ThreadBlC = exec_multi_thread_blocos(argsBlc, &res_matriz_ThreadBlC);
    //-------------------------------------------------------------

    if(rank == 0) {

        // Impressao dos resultados de tempo
        printf("\n\tCOMPARAR MATRIZ_SeqC c/ MATRIZ_SeqBlC\n\t");
        mcomparar(&res_matriz_SeqC, &res_matriz_SeqBlC);

        printf("\n\tCOMPARAR MATRIZ_SeqC c/ MATRIZ_ThreadC\n\t");
        mcomparar(&res_matriz_SeqC, &res_matriz_ThreadC); 

        printf("\n\tCOMPARAR MATRIZ_SeqC c/ MATRIZ_ThreadBlC\n\t");
        mcomparar(&res_matriz_SeqC, &res_matriz_ThreadBlC); 

        printf("\n\tTempo Médio MATRIZ_SeqC:\t\t%.6f sec \n", tempo_MATRIZ_SeqC / count_for);
        printf("\tTempo Médio MATRIZ_SeqBlC:\t\t%.6f sec\n", tempo_MATRIZ_SeqBlC / count_for );
        printf("\tTempo Médio MATRIZ_ThreadC:\t\t%.6f sec \n", tempo_MATRIZ_ThreadC);
        printf("\tTempo Médio MATRIZ_ThreadBlC:\t%.6f sec \n", tempo_MATRIZ_ThreadBlC);

        speedup_seqC = (tempo_MATRIZ_SeqC / count_for) / (tempo_MATRIZ_ThreadC);
        speedup_BlC = (tempo_MATRIZ_SeqBlC / count_for) / (tempo_MATRIZ_ThreadBlC );
        printf("\n\tSPEEDUP (MATRIZ_C): \t%.5f (%.2f %c)", speedup_seqC, speedup_seqC*100, 37 );
        printf("\n\tSPEEDUP (MATRIZ_BLC): \t%.5f (%.2f %c)\n\n", speedup_BlC, speedup_BlC*100, 37 );

        if ((speedup_BlC < 1) && (mat_a.lin >= 1000))
            printf("Warning: if you couldn't experience a good speedup, try again and change thread configuration\n");

        //Liberação de memória
        mliberar(&res_matriz_SeqC);
        mliberar(&res_matriz_SeqBlC);
        mliberar(&res_matriz_ThreadC);
        mliberar(&res_matriz_ThreadBlC);

    }

    MPI_Finalize();

    return 0;
}


/*
function loadMatrix
Load the matrix from a file to a mymatriz object.
@return 0
@param argv, matrix name, address of the destiny object
*/
int loadMatrix(char* matrix_name, mymatriz* address){

    //variable for the files manipulation
    FILE *fmat;
    int nr_line;
    int *vet_line = NULL;
    int N, La;

    //matrix reading
    fmat = fopen(matrix_name, "r");
    if (fmat == NULL)
    {
        printf("** ERRO: na abertura do arquivo %s **\n", matrix_name);
        exit(1);
    }
    extrai_parametros_matriz(fmat, &N, &La, &vet_line, &nr_line);
    address->matriz = NULL;
    address->lin = N;
    address->col = La;

    if (malocar(address))
    {
        printf("** ERRO: na alocacao de memoria para matriz %s **\n", matrix_name);
        exit(1);
    }

    filein_matriz(address->matriz, N, La, fmat, vet_line, nr_line);
    free(vet_line);
    fclose(fmat);

    return 0;
}


/*
function seqMultiplication
Execute the matrix sequential multiplication.
@return time spent
@param argv, matrix A, matrix B and matrix C as result
*/
double seqMultiplication(mymatriz* mat_a, mymatriz* mat_b, mymatriz* mat_c){

    double start_time, end_time;
    double tempo_MATRIZ_SeqC = 0;

    char filename[100];
    FILE *fmat;

    //sequential multiplication
    printf("\rExecutando multiplicação sequencial");
    fflush(stdout);
    for (int count = 0; count < count_for; count++)
    {   
        start_time = wtime();
        mmultiplicar(mat_a, mat_b, mat_c, 1);  //1=mais rápido, 5=mais lento
        end_time = wtime();
        tempo_MATRIZ_SeqC += end_time - start_time;
    }

    //save the result in file
    sprintf(filename, "MATRIZ_SeqC.result");
    fmat = fopen(filename, "w");
    fileout_matriz(mat_c, fmat);
    fclose(fmat);

    printf("\rExecutando multiplicação sequencial  .. OK\n");
    fflush(stdout);

    return tempo_MATRIZ_SeqC;
}

/*
function blcMultiplication
Execute the matrix multiplication in blocks.
@return time spent
@param argv, matrix A, matrix B and matrix C as result
*/
double blcMultiplication(mymatriz* mat_a, mymatriz* mat_b, mymatriz* mat_c){

    double start_time, end_time;
    double tempo_MATRIZ_SeqBlC = 0;

    char filename[100];
    FILE *fmat;

    //variables for block control
    matriz_bloco_t **Vsubmat_a = NULL;
    matriz_bloco_t **Vsubmat_b = NULL;
    matriz_bloco_t **Vsubmat_c = NULL;

    //blocks multiplication
    printf("\rExecutando multiplicação em blocos");
    fflush(stdout);
    for (int count = 0; count < count_for; count++)
    {
        start_time = wtime();
        Vsubmat_a = particionar_matriz(mat_a->matriz, mat_a->lin, mat_a->col, 1, nro_submatrizes);
        Vsubmat_b = particionar_matriz(mat_b->matriz, mat_b->lin, mat_b->col, 0, nro_submatrizes);
        Vsubmat_c = csubmatrizv2(mat_a->lin, mat_b->col , nro_submatrizes);

        //block multiplication
        for (int i = 0; i < nro_submatrizes; i++){
            multiplicar_submatriz (Vsubmat_a[i], Vsubmat_b[i], Vsubmat_c[i]);
        }

        //result matrix
        mat_c->matriz = NULL;
        mat_c->lin = mat_a->lin;
        mat_c->col = mat_b->col;

        //result matrix memory allocation
        if (malocar(mat_c)) {
            printf ("** ERRO: Out of memory **\n");
            exit(1);
        }else{
            mzerar(mat_c);
        }

        //sum the separated blocks
        msomar(Vsubmat_c[0]->matriz,Vsubmat_c[1]->matriz, mat_c, 1);
        for (int i = 2; i < nro_submatrizes; i++){
            msomar(mat_c,Vsubmat_c[i]->matriz, mat_c, 1);	
        }

        end_time = wtime();
        tempo_MATRIZ_SeqBlC += end_time - start_time;
    }

    //save the result in file
    sprintf(filename, "MATRIZ_SeqBlC.result");
    fmat = fopen(filename, "w");
    fileout_matriz(mat_c, fmat);
    fclose(fmat);

    printf("\rExecutando multiplicação em blocos  .. OK\n");
    fflush(stdout);

    return tempo_MATRIZ_SeqBlC;
}


/*
function exec_multi_thread
Initialize each thread for the matrix multiplication.
@return NULL
@param *arg, pointer to param_t object
*/
double exec_multi_thread(void *arg)
{
    param_t *p = (param_t *)arg;

    //variable declaration
	int rank, size;
    int *arrayA, *arrayB, *arrayC;
    int *recA, *recC;
    int sizeA, sizeB, sizeC;
    int pos;

    double start_time, end_time;
    double tempo_MATRIZ_ThreadC = 0;

    char filename[100];
    FILE *fmat;

    sizeA = p->mat_a->lin * p->mat_a->col;
    sizeB = p->mat_b->lin * p->mat_b->col;
    sizeC = p->mat_a->lin * p->mat_b->col;
    arrayA = (int*) malloc( sizeA * sizeof(int*) );
    arrayB = (int*) malloc( sizeB * sizeof(int*) );
    arrayC = (int*) malloc( sizeC * sizeof(int*) );

    //identify mpi thread and number of threads (size)
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0){
        printf("\rExecutando multiplicação sequencial em threads");
        fflush(stdout);
    }

    //transform the matrix mat_a and mat_b into a big vector
    //so we can use scatter and gather
    if (rank == 0){

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

    //to allocate local data (part of each thread)
    recA = (int*) malloc( sizeA/size * sizeof(int*) );
    recC = (int*) malloc( sizeC/size * sizeof(int*) );

    MPI_Barrier(MPI_COMM_WORLD);
    start_time = wtime();
    
    //thread master scatter matrix arrayA to the other threads
    MPI_Scatter( arrayA , sizeA/size , MPI_INT , recA , sizeA/size , MPI_INT , 0, MPI_COMM_WORLD );

    //thread master broadcast arrayB to the other threads
    MPI_Bcast ( arrayB, sizeB , MPI_INT , 0 , MPI_COMM_WORLD );

	//calculate recC as multiplicated matrix
    //warning: just work in a square matrix multiple of the number of threads, ex: 5 threads -> 5x5, 10x10, 15x15... matrix
    int n = p->mat_b->col;	
    for ( int i=0 ; i < (p->mat_a->lin/size); i++ ){
        for ( int j = 0 ; j < p->mat_b->col; j++ ){
            recC[i*n+j] = 0;
            for ( int k = 0 ; k < p->mat_a->col ; k++ ){
                recC[i*n+j] += recA[i*n+k]*arrayB[k*n+j];
            }
        }
    }

    //thread master gather all result data from all the slaves
    MPI_Gather( recC , sizeC/size , MPI_INT , arrayC , sizeC/size , MPI_INT , 0, MPI_COMM_WORLD ) ;

	MPI_Barrier(MPI_COMM_WORLD);
    end_time = wtime();
    tempo_MATRIZ_ThreadC = end_time - start_time;

    //set the big vector into the result matrix
    if (rank == 0){
        pos = 0;
        for (int i = 0; i < p->mat_c->lin; i++) {
            for (int j = 0; j < p->mat_c->col; j++){
                p->mat_c->matriz[i][j] = arrayC[pos++];
            }
        }
    }

    //save the result in file
    if (rank == 0){
        sprintf(filename, "MATRIZ_ThreadC.result");
        fmat = fopen(filename, "w");
        fileout_matriz(p->mat_c, fmat);
        fclose(fmat);
    }

    if (rank == 0){
        printf("\rExecutando multiplicação sequencial em threads .. OK\n");
        fflush(stdout);
    }

    return tempo_MATRIZ_ThreadC;
}


/*
function exec_multi_thread_blocos
Initialize each thread for the block multiplication.
@return NULL
@param *arg, pointer to a param_t object
@param *res, pointer to the result mymatriz object
*/
double exec_multi_thread_blocos(param_t *p, mymatriz* res)
{
    //variable declaration    
    int rank, size;
    int pos;
    int *arrayA, *arrayB, *arrayC, *arrayC_temp;
    int sizeA, sizeB, sizeC;
    int infos[8] = {0,0,0,0,0,0,0,0};

    double start_time, end_time;
    double tempo_MATRIZ_ThreadBlC = 0;

    char filename[100];
    FILE *fmat;

    //identify mpi thread and number of threads (size)
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;

    //calculate the number of elements in each matrix
    sizeA = p[0].mat_bloco_a->matriz->lin * p[0].mat_bloco_a->matriz->col;
    sizeB = p[0].mat_bloco_b->matriz->lin * p[0].mat_bloco_b->matriz->col;
    sizeC = p[0].mat_bloco_c->matriz->lin * p[0].mat_bloco_c->matriz->col;
    arrayA = (int*) malloc( sizeA * sizeof(int*) );
    arrayB = (int*) malloc( sizeB * sizeof(int*) );
    arrayC = (int*) malloc( sizeC * sizeof(int*) );
    arrayC_temp = (int*) calloc( sizeC, sizeof(int*) );

    //thread master
    if (rank == 0){

        printf("\rExecutando multiplicação blocos em threads");
        fflush(stdout);

        //transform the array A into a big vector
        pos = 0;
        for (int i = 0; i < p[rank].mat_bloco_a->matriz->lin; i++) {
            for (int j = 0; j < p[rank].mat_bloco_a->matriz->col; j++){
                arrayA[pos++] = p[rank].mat_bloco_a->matriz->matriz[i][j];
            }
        }

        //transform the array B into a big vector
        pos = 0;
        for (int i = 0; i < p[rank].mat_bloco_b->matriz->lin; i++) {
            for (int j = 0; j < p[rank].mat_bloco_b->matriz->col; j++){
                arrayB[pos++] = p[rank].mat_bloco_b->matriz->matriz[i][j];
            }
        }

        start_time = wtime();
        
        //broadcast array A and B from master thread to the slaves
        MPI_Bcast ( arrayA, sizeA , MPI_INT , 0 , MPI_COMM_WORLD );
        MPI_Bcast ( arrayB, sizeA , MPI_INT , 0 , MPI_COMM_WORLD );

        //send the block configuration to each slave
        for (int i = 0; i < p[rank].ntasks; i++){
            infos[0] = p[i].mat_bloco_a->bloco->lin_inicio;
            infos[1] = p[i].mat_bloco_a->bloco->lin_fim;
            infos[2] = p[i].mat_bloco_a->bloco->col_inicio;
            infos[3] = p[i].mat_bloco_a->bloco->col_fim;
            infos[4] = p[i].mat_bloco_b->bloco->lin_inicio;
            infos[5] = p[i].mat_bloco_b->bloco->lin_fim;
            infos[6] = p[i].mat_bloco_b->bloco->col_inicio;
            infos[7] = p[i].mat_bloco_b->bloco->col_fim;

            MPI_Send(infos,8,MPI_INT,(i+1), 0, MPI_COMM_WORLD);
        }

        //receive the blocks from the threads and sum
        for (int i = 0; i < p[rank].ntasks; i++){
            
            //receive a block from the thread
            MPI_Recv(arrayC_temp,sizeC,MPI_INT, (i+1), 0, MPI_COMM_WORLD, &status);

            //into arrayC sum each position of each block
            for (int p = 0; p < sizeC; p++){
                arrayC[p] += arrayC_temp[p];
            }
        }

        end_time = wtime();
        tempo_MATRIZ_ThreadBlC = end_time - start_time;
        
        //set the big vector into the result matrix
        pos = 0;
        for (int i = 0; i < p[0].mat_bloco_c->matriz->lin; i++) {
            for (int j = 0; j < p[0].mat_bloco_c->matriz->lin; j++){
                res->matriz[i][j] = arrayC[pos++];
            }
        }

        //save the result in file
        sprintf(filename, "MATRIZ_ThreadBlC.result");
        fmat = fopen(filename, "w");
        fileout_matriz(res, fmat);
        fclose(fmat);

        printf("\rExecutando multiplicação blocos em threads .. OK\n");
        fflush(stdout);
        
    }else{

        //receive the broadcast of array A and B from master
        MPI_Bcast ( arrayA, sizeA , MPI_INT , 0 , MPI_COMM_WORLD );
        MPI_Bcast ( arrayB, sizeA , MPI_INT , 0 , MPI_COMM_WORLD );

        //receive the information of the block that will calculate
        MPI_Recv(infos,8,MPI_INT,0, 0, MPI_COMM_WORLD, &status);

        //run the block calculation
        for (int i = infos[0]; i < infos[1]; i++){
            for (int j = infos[6]; j < infos[7]; j++){
                for (int k = infos[2]; k < infos[3]; k++){  
                    p[0].mat_bloco_c->matriz->matriz[i][j] += p[0].mat_bloco_a->matriz->matriz[i][k] * p[0].mat_bloco_b->matriz->matriz[k][j];
                }
            }
        }

        //set the big vector into the result matrix
        pos = 0;
        for (int i = 0; i < p[0].mat_bloco_c->matriz->lin; i++) {
            for (int j = 0; j < p[0].mat_bloco_c->matriz->col; j++){
                arrayC[pos++] = p[0].mat_bloco_c->matriz->matriz[i][j];
            }
        }

        //send the block result to the master thread
        MPI_Send(arrayC,sizeC,MPI_INT,0, 0, MPI_COMM_WORLD);
    }

    return tempo_MATRIZ_ThreadBlC;
}


