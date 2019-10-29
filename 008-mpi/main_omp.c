#include <omp.h>
#include <unistd.h>
#include "matriz-operacoes-omp.h"

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
    multiplicarOMP(p->mat_a, p->mat_b, p->mat_c, p->tid, p->ntasks);
    return NULL;
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

/*
function main
Funcao principal para realizar a multiplicacao de matrizes sequencial, sequencial por thread,
em bloco e em bloco por thread, comparando resultados e mostrando tempo e speedup.
@return 0
@param argv, devem ser informadas a matriz_a e matriz_b e opcionalmente número de threads/blocos
*/
int main(int argc, char *argv[])
{
    // %%%%%%%%%%%%%%%%%%%%%%%% BEGIN %%%%%%%%%%%%%%%%%%%%%%%%
    // Declaração de Variáveis

    //variaveis para armazenar matrizes origem e de resultado
    mymatriz mat_a, mat_b;
    mymatriz *res_matriz_SeqC;
    mymatriz *res_matriz_SeqBlC;
    mymatriz *res_matriz_ThreadC;
    mymatriz *res_matriz_ThreadBlC;

    //variaveis para manipulacao de arquivos no disco
    char filename[100];
    FILE *fmat;
    int nr_line;
    int *vet_line = NULL;
    int N, M, La, Lb;

    //variaveis para controle de blocos
    matriz_bloco_t **Vsubmat_a = NULL;
    matriz_bloco_t **Vsubmat_b = NULL;
    matriz_bloco_t **Vsubmat_c = NULL;
    int nro_submatrizes = 4; //deve ser igual ntasks

    //Variaveis executar calculo da média
    int ntasks = 4; //deve ser igual nro_submatrizes
    int count_for = 10; //numero de repeticoes para média de runtime

    //variaveis para controle de threads
    param_t *args;

    //variaveis para controle de tempo (runtime)
    double start_time, end_time;
    double tempo_MATRIZ_SeqC = 0;
    double tempo_MATRIZ_SeqBlC = 0;
    double tempo_MATRIZ_ThreadC = 0;
    double tempo_MATRIZ_ThreadBlC = 0;
    double speedup_seqC;
    double speedup_BlC;
    // %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%

    if (argc < 3)
    {
        printf("ERRO: Numero de parametros %s <matriz_a> <matriz_b> <threads>\n", argv[0]);
        exit(1);
    }

    if (argv[3] != NULL){
        nro_submatrizes = atoi(argv[3]);
        ntasks = atoi(argv[3]);
    }

    //ajusta o número de tasks para ser proporcional ao número de processadores (otimizacao)
    if ( ntasks % omp_get_num_procs()  > 0 ){
        ntasks = ntasks - ( ntasks % omp_get_num_procs() );
        nro_submatrizes = ntasks;
        printf("task number adjusted automatically to %d \n", ntasks);
    }else{
        //garante que ntasks e nro_submatrizes tenham o mesmo valor
        if ( ntasks != nro_submatrizes)
            nro_submatrizes = ntasks;
    }

    // %%%%%%%%%%%%%%%%%%%%%%%% BEGIN %%%%%%%%%%%%%%%%%%%%%%%%
    //Leitura da Matriz A (arquivo)
    fmat = fopen(argv[1], "r");
    if (fmat == NULL)
    {
        printf("ERRO: na abertura dos arquivos.\n");
        exit(1);
    }
    extrai_parametros_matriz(fmat, &N, &La, &vet_line, &nr_line);
    mat_a.matriz = NULL;
    mat_a.lin = N;
    mat_a.col = La;
    if (malocar(&mat_a))
    {
        printf("ERRO: na alocacao de memoria para mat_a.\n");
    }
    filein_matriz(mat_a.matriz, N, La, fmat, vet_line, nr_line);
    free(vet_line);
    fclose(fmat);
    // %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%

    // %%%%%%%%%%%%%%%%%%%%%%%% BEGIN %%%%%%%%%%%%%%%%%%%%%%%%
    //Leitura da Matriz B (arquivo)
    fmat = fopen(argv[2], "r");
    if (fmat == NULL)
    {
        printf("ERRO: na abertura dos arquivos.\n");
        exit(1);
    }
    extrai_parametros_matriz(fmat, &Lb, &M, &vet_line, &nr_line);
    mat_b.matriz = NULL;
    mat_b.lin = Lb;
    mat_b.col = M;
    if (malocar(&mat_b))
    {
        printf("ERRO: na alocacao de memoria para mat_b.\n");
    }
    filein_matriz(mat_b.matriz, Lb, M, fmat, vet_line, nr_line);
    free(vet_line);
    fclose(fmat);
    // %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%




    // %%%%%%%%%%%%%%%%%%%%%%%% BEGIN %%%%%%%%%%%%%%%%%%%%%%%%
    // Multiplicação Sequencial
    res_matriz_SeqC = (mymatriz *)malloc(sizeof(mymatriz));
    for (int count = 0; count < count_for; count++)
    {   
        printf("\rExecutando multiplicação sequencial %d de %d", count+1, count_for);
        fflush(stdout);

        start_time = wtime();
        res_matriz_SeqC = mmultiplicar(&mat_a, &mat_b, 1);  //1=mais rápido (2.04), 5=mais lento (5.94)
        end_time = wtime();
        tempo_MATRIZ_SeqC += end_time - start_time;
        //printf(" sequencial %d. tempo: %.20f \t avg= %.20f\n",count, end_time - start_time, tempo_MATRIZ_SeqC / (count+1));
    }
    sprintf(filename, "MATRIZ_SeqC.result");
    fmat = fopen(filename, "w");
    fileout_matriz(res_matriz_SeqC, fmat);
    fclose(fmat);
    // %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%




    // %%%%%%%%%%%%%%%%%%%%%%%% BEGIN %%%%%%%%%%%%%%%%%%%%%%%%
    // Multiplicação Sequencial em Bloco
    printf("\n");
    res_matriz_SeqBlC = (mymatriz *)malloc(sizeof(mymatriz));
    for (int count = 0; count < count_for; count++)
    {
        printf("\rExecutando multiplicação sequencial em bloco %d de %d", count+1, count_for);
        fflush(stdout);

        start_time = wtime();
        Vsubmat_a = particionar_matriz(mat_a.matriz, N, La, 1, nro_submatrizes);
        Vsubmat_b = particionar_matriz(mat_b.matriz, Lb, M, 0, nro_submatrizes);
        Vsubmat_c = csubmatrizv2(N, M, nro_submatrizes);

        //multiplicacao de blocos
        for (int i = 0; i < nro_submatrizes; i++){
            multiplicar_submatriz (Vsubmat_a[i], Vsubmat_b[i], Vsubmat_c[i]);
        }

        //soma os blocos separados
        res_matriz_SeqBlC = msomar(Vsubmat_c[0]->matriz,Vsubmat_c[1]->matriz, 1);
        for (int i = 2; i < nro_submatrizes; i++){
            res_matriz_SeqBlC = msomar(res_matriz_SeqBlC,Vsubmat_c[i]->matriz, 1);	
        }

        end_time = wtime();
        tempo_MATRIZ_SeqBlC += end_time - start_time;
        //printf(" bloco %d. tempo: %.20f \t avg= %.20f\n",count, end_time - start_time, tempo_MATRIZ_SeqBlC / (count+1));
    }
    sprintf(filename, "MATRIZ_SeqBlC.result");
    fmat = fopen(filename, "w");
    fileout_matriz(res_matriz_SeqBlC, fmat);
    fclose(fmat);
    // %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%




    // %%%%%%%%%%%%%%%%%%%%%%%% BEGIN %%%%%%%%%%%%%%%%%%%%%%%%
    // Multiplicação MultiThread
    printf("\n");
    res_matriz_ThreadC = (mymatriz *)malloc(sizeof(mymatriz));
    res_matriz_ThreadC = malloc(sizeof(mymatriz));
    res_matriz_ThreadC->matriz = NULL;
    res_matriz_ThreadC->lin = mat_a.lin;
    res_matriz_ThreadC->col = mat_b.col;

    //realiza a alocação de memória para matriz resultado
    if (malocar(res_matriz_ThreadC)) {
        printf("ERRO: na alocacao de memoria para res_matriz_ThreadC.\n");
        exit(1);
    }else{
        mzerar(res_matriz_ThreadC);
    }

    for (int count = 0; count < count_for; count++)
    {
        printf("\rExecutando multiplicação multithread %d de %d", count+1, count_for);
        fflush(stdout);

        mzerar(res_matriz_ThreadC);
        args = (param_t *)malloc(ntasks * sizeof(param_t));
        start_time = wtime();

        int tid;
        int nthreads;
        #pragma omp parallel private(tid,nthreads) num_threads(ntasks) 
        {
            tid = omp_get_thread_num();
            nthreads = omp_get_num_threads();

            args[tid].tid = tid;
            args[tid].ntasks = nthreads;
            args[tid].mat_a = &mat_a;
            args[tid].mat_b = &mat_b;
            args[tid].mat_c = res_matriz_ThreadC;
            exec_multi_thread((void *)(args + tid));
        }
        end_time = wtime();
        tempo_MATRIZ_ThreadC += end_time - start_time;
        //printf(" sequencial thread %d. tempo: %.20f \t avg= %.20f\n",count, end_time - start_time, tempo_MATRIZ_ThreadC / (count+1));
    }
    sprintf(filename, "MATRIZ_ThreadC.result");
    fmat = fopen(filename, "w");
    fileout_matriz(res_matriz_ThreadC, fmat);
    fclose(fmat);
    // %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%




    // %%%%%%%%%%%%%%%%%%%%%%%% BEGIN %%%%%%%%%%%%%%%%%%%%%%%%
    // Multiplicação MultiThreads em Bloco
    printf("\n");
    res_matriz_ThreadBlC = (mymatriz *)malloc(sizeof(mymatriz));
    for (int count = 0; count < count_for; count++)
    {
        printf("\rExecutando multiplicação multithread em bloco %d de %d", count+1, count_for);
        fflush(stdout);

        Vsubmat_a = particionar_matriz(mat_a.matriz, N, La, 1, nro_submatrizes);
        Vsubmat_b = particionar_matriz(mat_b.matriz, Lb, M, 0, nro_submatrizes);
        Vsubmat_c = csubmatrizv2(N, M, nro_submatrizes);

        args = (param_t *)malloc(ntasks * sizeof(param_t));
        start_time = wtime();

        int tid;
        int nthreads;
        #pragma omp parallel num_threads(ntasks) 
        {
            tid = omp_get_thread_num();
            nthreads = omp_get_num_threads();

            args[tid].tid = tid;
            args[tid].ntasks = nthreads;
            args[tid].mat_bloco_a = Vsubmat_a[tid];
            args[tid].mat_bloco_b = Vsubmat_b[tid];
            args[tid].mat_bloco_c = Vsubmat_c[tid];
            exec_multi_thread_blocos((void *)(args + tid));
        }
        
        //soma os blocos separados
        res_matriz_ThreadBlC = msomar(Vsubmat_c[0]->matriz,Vsubmat_c[1]->matriz, 1);
        for (int i = 2; i < nro_submatrizes; i++){
            res_matriz_ThreadBlC = msomar(res_matriz_ThreadBlC,Vsubmat_c[i]->matriz, 1);	
        }

        end_time = wtime();
        tempo_MATRIZ_ThreadBlC += end_time - start_time;
        //printf("bloco thread %d. tempo: %.20f \t avg= %.20f\n",count, end_time - start_time, tempo_MATRIZ_ThreadBlC / (count+1));
    }
    sprintf(filename, "MATRIZ_ThreadBlC.result");
    fmat = fopen(filename, "w");
    fileout_matriz(res_matriz_ThreadBlC, fmat);
    fclose(fmat);
    // %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%




    // %%%%%%%%%%%%%%%%%%%%%%%% BEGIN %%%%%%%%%%%%%%%%%%%%%%%%
    // Impressao dos resultados de tempo
    printf("\n\n\tCOMPARAR MATRIZ_SeqC c/ MATRIZ_SeqBlC\n\t");
    mcomparar(res_matriz_SeqC, res_matriz_SeqBlC);

    printf("\n\tCOMPARAR MATRIZ_SeqC c/ MATRIZ_ThreadC\n\t");
    mcomparar(res_matriz_SeqC, res_matriz_ThreadC);
    
    printf("\n\tCOMPARAR MATRIZ_SeqC c/ MATRIZ_ThreadBlC\n\t");
    mcomparar(res_matriz_SeqC, res_matriz_ThreadBlC);

    printf("\n\tTempo Médio MATRIZ_SeqC:\t%.6f sec \n", tempo_MATRIZ_SeqC / count_for);
    printf("\tTempo Médio MATRIZ_SeqBlC:\t%.6f sec\n", tempo_MATRIZ_SeqBlC / count_for );
    printf("\tTempo Médio MATRIZ_ThreadC:\t%.6f sec \n", tempo_MATRIZ_ThreadC / count_for);
    printf("\tTempo Médio MATRIZ_ThreadBlC:\t%.6f sec \n", tempo_MATRIZ_ThreadBlC / count_for);

    speedup_seqC = (tempo_MATRIZ_SeqC / count_for) / (tempo_MATRIZ_ThreadC / count_for);

    speedup_BlC = (tempo_MATRIZ_SeqBlC / count_for) / (tempo_MATRIZ_ThreadBlC / count_for);
    printf("\n\tSPEEDUP (MATRIZ_C): \t%.5f (%.2f %c)", speedup_seqC, speedup_seqC*100, 37 );
    printf("\n\tSPEEDUP (MATRIZ_BLC): \t%.5f (%.2f %c)\n\n", speedup_BlC, speedup_BlC*100, 37 );

    // %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%




    // %%%%%%%%%%%%%%%%%%%%%%%% BEGIN %%%%%%%%%%%%%%%%%%%%%%%%
    //Liberação de memória
    mliberar(res_matriz_SeqC);
    mliberar(res_matriz_SeqBlC);
    mliberar(res_matriz_ThreadC);
    mliberar(res_matriz_ThreadBlC);

    free(res_matriz_SeqC);
    free(res_matriz_SeqBlC);
    free(res_matriz_ThreadC);
    free(res_matriz_ThreadBlC);

    mliberar(&mat_a);
    mliberar(&mat_b);
    // %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%

    return 0;
}






/*
function teste_reduction
Funcao para testar a performance de utilizar o openmp reduction para paralelizar a multiplicacao
e encontrar uma posicao (m,n) de uma matriz resultado. Os resultados nao foram satisfatórios para
encontrar (m,n) na multiplicação de uma matriz 1000x1000:
- tempo paralelo: 0.006206  resultado: 2406570
- tempo serial:   0.000016  resultado: 2406570
@return 0
@param *mat_a, ponteiro para mymatriz base para multiplicacao
@param *mat_b, ponteiro para mymatriz base para multiplicacao
@param *mat_c, ponteiro para mymatriz resultado
*/
int teste_reduction(mymatriz *mat_a, mymatriz *mat_b, mymatriz *mat_c){
    
    //inicializa variáveis de controle dos for`s
    int j_max = mat_b->lin;
    int m = 0;
    int n = 0;
    double start_time, end_time, all_time;
    int tot = 0;

    //---------
    start_time = wtime();
    #pragma omp parallel for reduction(+:tot) num_threads(4)
        for (int j = 0; j < j_max; j++){
            tot += mat_a->matriz[m][j] * mat_b->matriz[j][n];
            //printf("mat_c->matriz[%d][%d] (%d) = mat_a->matriz[%d][%d] (%d) * mat_b->matriz[%d][%d] (%d) \t thread %d\n",m,n,mat_c->matriz[m][n],m,j,mat_a->matriz[m][j],j,n,mat_b->matriz[j][n],omp_get_thread_num());
        }

    mat_c->matriz[m][n] = tot;
    end_time = wtime();
    all_time = end_time - start_time;
    printf("\ntempo paralelo:\t %.6f resultado: %d\n",all_time,tot);
    
    //---------
    tot = 0;
    start_time = wtime();
    for (int j = 0; j < j_max; j++){
        tot += mat_a->matriz[m][j] * mat_b->matriz[j][n];
        //printf("mat_c->matriz[%d][%d] (%d) = mat_a->matriz[%d][%d] (%d) * mat_b->matriz[%d][%d] (%d)\n",m,n,mat_c->matriz[m][n],m,j,mat_a->matriz[m][j],j,n,mat_b->matriz[j][n];
    }
    mat_c->matriz[m][n] = tot;
    end_time = wtime();
    all_time = end_time - start_time;
    printf("tempo serial:\t %.6f resultado: %d\n",all_time,tot);

    return 0;
}
