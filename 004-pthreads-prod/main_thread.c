#include <pthread.h>
#include "matriz-operacoes-threads.h"

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
    multiplicarTh(p->mat_a, p->mat_b, p->mat_c, p->tid, p->ntasks);
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
    multiplicarThblocos(p->mat_bloco_a, p->mat_bloco_b, p->mat_bloco_c);
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
    int nro_submatrizes = 2; //deve ser igual ntasks

    //Variaveis executar calculo da média
    int ntasks = 2; //deve ser igual nro_submatrizes
    int count_for = 10; //numero de repeticoes para média de runtime

    //variaveis para controle de threads
    param_t *args;
    pthread_t *threads;

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
        //printf("sequencial %d. tempo: %.20f \t avg= %.20f\n",count, end_time - start_time, tempo_MATRIZ_SeqC / (count+1));
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
        //printf("bloco %d. tempo: %.20f \t avg= %.20f\n",count, end_time - start_time, tempo_MATRIZ_SeqBlC / (count+1));
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
        threads = (pthread_t *)malloc(ntasks * sizeof(pthread_t));
        args = (param_t *)malloc(ntasks * sizeof(param_t));
        start_time = wtime();
        for (int i = 0; i < ntasks; i++)
        {
            args[i].tid = i;
            args[i].ntasks = ntasks;
            args[i].mat_a = &mat_a;
            args[i].mat_b = &mat_b;
            args[i].mat_c = res_matriz_ThreadC;
            pthread_create(&threads[i], NULL, exec_multi_thread, (void *)(args + i));
        }

        for (int i = 0; i < ntasks; i++)
        {
            pthread_join(threads[i], NULL);
        }
        end_time = wtime();
        tempo_MATRIZ_ThreadC += end_time - start_time;
        //printf("sequencial thread %d. tempo: %.20f \t avg= %.20f\n",count, end_time - start_time, tempo_MATRIZ_ThreadC / (count+1));
        
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

        threads = (pthread_t *)malloc(ntasks * sizeof(pthread_t));
        args = (param_t *)malloc(ntasks * sizeof(param_t));
        start_time = wtime();
        for (int i = 0; i < ntasks; i++)
        {
            args[i].tid = i;
            args[i].ntasks = ntasks;
            args[i].mat_bloco_a = Vsubmat_a[i];
            args[i].mat_bloco_b = Vsubmat_b[i];
            args[i].mat_bloco_c = Vsubmat_c[i];
            pthread_create(&threads[i], NULL, exec_multi_thread_blocos, (void *)(args + i));
        }

        for (int i = 0; i < ntasks; i++)
        {
            pthread_join(threads[i], NULL);
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

    printf("\n\tTempo Médio tempo_MATRIZ_SeqC:\t\t%.6f sec \n", tempo_MATRIZ_SeqC / count_for);
    printf("\tTempo Médio tempo_MATRIZ_SeqBlC:\t%.6f sec\n", tempo_MATRIZ_SeqBlC / count_for );
    printf("\tTempo Médio MATRIZ_ThreadC:\t\t%.6f sec \n", tempo_MATRIZ_ThreadC / count_for);
    printf("\tTempo Médio MATRIZ_ThreadBlC:\t\t%.6f sec \n", tempo_MATRIZ_ThreadBlC / count_for);

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