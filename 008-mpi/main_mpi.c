#include <unistd.h>
#include "matriz-operacoes-mpi.h"
#include <mpi.h>

//Variaveis executar calculo da média
int ntasks = 4; //deve ser igual nro_submatrizes
int nro_submatrizes = 4; //deve ser igual ntasks
int count_for = 10; //numero de repeticoes para média de runtime

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
    int num = 0;
    int name_len;
    int start = 0;

    MPI_Status status;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (p->tid == 0){
        
        //p->mat_b->matriz[0][2] = 91;
        //printf("[%d] Sending the new value %d\n", p->tid, p->mat_b->matriz[0][2]);
        MPI_Bcast(&(p->mat_b->matriz[0][0]), p->mat_b->col, MPI_INT, 0, MPI_COMM_WORLD);

        for (int y = 1; y < size; y++) {
            start = y-1;
            MPI_Send(&start,1,MPI_INT,y,0,MPI_COMM_WORLD);
            //start += (p->mat_a->lin / (size-1) );
        }

    }else{

        printf("[%d] Slave called\n", p->tid);
        //printf("[%d] I have the values %d %d %d\n", p->tid, p->mat_b->matriz[0][0], p->mat_b->matriz[0][1], p->mat_b->matriz[0][2]);
        MPI_Bcast(&(p->mat_b->matriz[0][0]), p->mat_b->col, MPI_INT, 0, MPI_COMM_WORLD);
        //printf("[%d] Just received the value %d %d %d\n", p->tid, p->mat_b->matriz[0][0], p->mat_b->matriz[0][1], p->mat_b->matriz[0][2]) ;

        MPI_Recv(&start,1,MPI_INT,0,0,MPI_COMM_WORLD, &status);
        printf("[%d] received the lin value equals %d and will jump %d\n", p->tid, start, (p->ntasks-1) );

        multiplicarOMP(p->mat_a, p->mat_b, p->mat_c, start, (p->ntasks - 1) );


    }

    return 0;
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
    mymatriz res_matriz_SeqC;
    mymatriz res_matriz_SeqBlC;
    mymatriz res_matriz_ThreadC;
    

    double tempo_MATRIZ_SeqC = 0;
    double tempo_MATRIZ_SeqBlC = 0;

    //variaveis para controle de threads
    param_t *args;

	int rank, size;//,i;
	//int tag=0;
    int name_len;

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

    MPI_Finalize();


    return 0;
}








