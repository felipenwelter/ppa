#include <pthread.h>
#include "matriz-operacoes-threads.h"

typedef struct
{
    int tid;
    int ntasks;
    mymatriz *mat_a;
    mymatriz *mat_b;
    mymatriz *mat_c;
} param_t;

void *exec_multi_thread(void *arg)
{
    param_t *p = (param_t *)arg;
    multiplicarTh(p->mat_a, p->mat_b, p->mat_c, p->tid, p->ntasks);
    return NULL;
}

void *exec_multi_thread_blocos(void *arg)
{
    //param_t *p = (param_t *)arg;

    //sleep(p->ntasks - p->tid);
    //printf("(exec_thread) %d\n", p->tid);
    return NULL;
}

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main(int argc, char *argv[])
{
    // %%%%%%%%%%%%%%%%%%%%%%%% BEGIN %%%%%%%%%%%%%%%%%%%%%%%%
    // DECLARAÇÃO de VARIÁVEIS
    mymatriz mat_a, mat_b;
    mymatriz **mmult_MATRIZ_SeqC;
    mymatriz **mmult_MATRIZ_SeqBlC;
    mymatriz **mmult_MATRIZ_ThreadC;
    mymatriz **mmult_MATRIZ_ThreadBlC;

    char filename[100];
    FILE *fmat;
    int nr_line;
    int *vet_line = NULL;
    int N, M, La, Lb;
    double start_time, end_time;

    matriz_bloco_t **Vsubmat_a = NULL;
    matriz_bloco_t **Vsubmat_b = NULL;
    matriz_bloco_t **Vsubmat_c = NULL;
    int nro_submatrizes = 2;

    //For para executar calculo da média
    int ntasks = 2;
    int count_for = 10;
    param_t *args;
    pthread_t *threads;

    double tempo_MATRIZ_SeqC = 0;
    double tempo_MATRIZ_SeqBlC = 0;
    double MATRIZ_ThreadC = 0;
    double MATRIZ_ThreadBlC = 0;

    // %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%

    if (argc != 3)
    {
        printf("ERRO: Numero de parametros %s <matriz_a> <matriz_b>\n", argv[0]);
        exit(1);
    }

    // %%%%%%%%%%%%%%%%%%%%%%%% BEGIN %%%%%%%%%%%%%%%%%%%%%%%%
    //Leitura da Matriz A (arquivo)
    fmat = fopen(argv[1], "r");
    if (fmat == NULL)
    {
        printf("Error: Na abertura dos arquivos.");
        exit(1);
    }
    extrai_parametros_matriz(fmat, &N, &La, &vet_line, &nr_line);
    mat_a.matriz = NULL;
    mat_a.lin = N;
    mat_a.col = La;
    if (malocar(&mat_a))
    {
        printf("ERROR: Out of memory\n");
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
        printf("Error: Na abertura dos arquivos.");
        exit(1);
    }
    extrai_parametros_matriz(fmat, &Lb, &M, &vet_line, &nr_line);
    mat_b.matriz = NULL;
    mat_b.lin = Lb;
    mat_b.col = M;
    if (malocar(&mat_b))
    {
        printf("ERROR: Out of memory\n");
    }
    filein_matriz(mat_b.matriz, Lb, M, fmat, vet_line, nr_line);
    free(vet_line);
    fclose(fmat);

    // %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%








    // %%%%%%%%%%%%%%%%%%%%%%%% BEGIN %%%%%%%%%%%%%%%%%%%%%%%%
    // Multiplicação Sequencial
    mmult_MATRIZ_SeqC = (mymatriz **)malloc(sizeof(mymatriz *));
    for (int count = 0; count < count_for; count++)
    {   
        start_time = wtime();
        mmult_MATRIZ_SeqC[0] = mmultiplicar(&mat_a, &mat_b, 1);
        end_time = wtime();
        tempo_MATRIZ_SeqC += end_time - start_time;
        printf("sequencial %d. tempo: %.20f\n",count, end_time - start_time);
    }
    sprintf(filename, "MATRIZ_SeqC.result");
    fmat = fopen(filename, "w");
    fileout_matriz(mmult_MATRIZ_SeqC[0], fmat);
    fclose(fmat);
    // %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%








    // %%%%%%%%%%%%%%%%%%%%%%%% BEGIN %%%%%%%%%%%%%%%%%%%%%%%%
    // Multiplicação Sequencial em Bloco
    mmult_MATRIZ_SeqBlC = (mymatriz **)malloc(sizeof(mymatriz *));
    for (int count = 0; count < count_for; count++)
    {
        start_time = wtime();
        Vsubmat_a = particionar_matriz(mat_a.matriz, N, La, 1, 2);
        Vsubmat_b = particionar_matriz(mat_b.matriz, Lb, M, 0, 2);
        Vsubmat_c = csubmatrizv2(N, M, nro_submatrizes);

        multiplicar_submatriz(Vsubmat_a[0], Vsubmat_b[0], Vsubmat_c[0]);
        multiplicar_submatriz(Vsubmat_a[1], Vsubmat_b[1], Vsubmat_c[1]);
        mmult_MATRIZ_SeqBlC[0] = msomar(Vsubmat_c[0]->matriz, Vsubmat_c[1]->matriz, 1);

        end_time = wtime();
        tempo_MATRIZ_SeqBlC += end_time - start_time;
        printf("bloco %d. tempo: %.20f\n",count, end_time - start_time);
    }

    sprintf(filename, "MATRIZ_SeqBlC.result");
    fmat = fopen(filename, "w");
    fileout_matriz(mmult_MATRIZ_SeqBlC[0], fmat);
    fclose(fmat);
    // %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%






    // %%%%%%%%%%%%%%%%%%%%%%%% BEGIN %%%%%%%%%%%%%%%%%%%%%%%%

    // Multiplicação MultiThread
    /*
    LOOP (10x)
            MARCAR_TEMPO INICIO
        MATRIZ_SeqC = MULTIPLICARMULTITHREADS MATRIZ_A x MATRIZ_B
        MARCAR_TEMPO FIM
        GRAVAR_DISCO MATRIZ_ThreadC
    */
   //TODO
    
    //matriz resultado
    mmult_MATRIZ_ThreadC = (mymatriz **)malloc(sizeof(mymatriz *));

    mmult_MATRIZ_ThreadC[0] = malloc(sizeof(mymatriz));
    mmult_MATRIZ_ThreadC[0]->matriz = NULL;
    mmult_MATRIZ_ThreadC[0]->lin = mat_a.lin;
    mmult_MATRIZ_ThreadC[0]->col = mat_b.col;

    //realiza a alocação de memória para matriz resultado
    if (malocar(mmult_MATRIZ_ThreadC[0])) {
        printf ("ERROR: Out of memory\n");
            exit(1);
    }else{
        mzerar(mmult_MATRIZ_ThreadC[0]);
    }

    for (int count = 0; count < count_for; count++)
    {
        mzerar(mmult_MATRIZ_ThreadC[0]);
        threads = (pthread_t *)malloc(ntasks * sizeof(pthread_t));
        args = (param_t *)malloc(ntasks * sizeof(param_t));
        start_time = wtime();
        for (int i = 0; i < ntasks; i++)
        {
            args[i].tid = i;
            args[i].ntasks = ntasks;
            args[i].mat_a = &mat_a;
            args[i].mat_b = &mat_b;
            args[i].mat_c = mmult_MATRIZ_ThreadC[0];
            pthread_create(&threads[i], NULL, exec_multi_thread, (void *)(args + i));
        }

        for (int i = 0; i < ntasks; i++)
        {
            pthread_join(threads[i], NULL);
        }
        end_time = wtime();
        printf("thread %d. tempo: %.20f\n",count, end_time - start_time);
        MATRIZ_ThreadC += end_time - start_time;
    }

    sprintf(filename, "MATRIZ_ThreadC.result");
    fmat = fopen(filename, "w");
    fileout_matriz(mmult_MATRIZ_ThreadC[0], fmat);
    fclose(fmat);

    // %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%







    // %%%%%%%%%%%%%%%%%%%%%%%% BEGIN %%%%%%%%%%%%%%%%%%%%%%%%
    // Multiplicação MultiThreads em Bloco
    /*
	N = mesmo nro de blocos da Sequencial
 LOOP (10x)
	MARCAR_TEMPO INICIO
	PARTICIONAR_MATRIZ em N pedacos
	MATRIZ_SeqBlC = MULTIPLICARBLOCOSMultithreads MATRIZ_A x MATRIZ_B
	MARCAR_TEMPO FIM
	GRAVAR_DISCO MATRIZ_ThreadBlC
    */
   //TODO
    mmult_MATRIZ_ThreadBlC = (mymatriz **)malloc(sizeof(mymatriz *));
    for (int count = 0; count < count_for; count++)
    {
        threads = (pthread_t *)malloc(ntasks * sizeof(pthread_t));
        args = (param_t *)malloc(ntasks * sizeof(param_t));
        start_time = wtime();
        for (int i = 0; i < ntasks; i++)
        {
            args[i].tid = i;
            args[i].ntasks = ntasks;
            //pthread_create(&threads[i], NULL, exec_multi_thread_blocos, (void *)(args + i));
        }

        for (int i = 0; i < ntasks; i++)
        {
            pthread_join(threads[i], NULL);
        }
        end_time = wtime();
        MATRIZ_ThreadBlC += end_time - start_time;
        //printf("\tRuntime : %f\n", end_time - start_time);
    }

    // %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%

    // Comparar resultados e tempos
    /*
    (print) COMPARAR MATRIZ_SeqC c/ MATRIZ_SeqBlC
    (print) COMPARAR MATRIZ_SeqC c/ MATRIZ_ThreadC
	(print) COMPARAR MATRIZ_SeqC c/ MATRIZ_ThreadBlC
	(print) TEMPO_MEDIO MATRIZ_SeqC 
	(print) TEMPO_MEDIO MATRIZ_SeqBlC
	(print) TEMPO_MEDIO MATRIZ_ThreadC
	(print) TEMPO_MEDIO MATRIZ_ThreadBlC
    (print) SPEEDUP (MATRIZ_C)
    (print) SPEEDUP (MATRIZ_BLC)
    */
    printf("\n\t(print) COMPARAR MATRIZ_SeqC c/ MATRIZ_SeqBlC\n\t");
    mcomparar(mmult_MATRIZ_SeqC[0], mmult_MATRIZ_SeqBlC[0]);

    printf("\n\t(print) COMPARAR MATRIZ_SeqC c/ MATRIZ_ThreadC\n\t");
    //TODO
    mcomparar(mmult_MATRIZ_SeqC[0], mmult_MATRIZ_ThreadC[0]);

    printf("\n\t(print) COMPARAR MATRIZ_SeqC c/ MATRIZ_ThreadBlC\n\t");
    //TODO
    //mcomparar(mmult_MATRIZ_SeqC[0], mmult_MATRIZ_ThreadBlC[0]);

    printf("\n\tRuntime Médio tempo_MATRIZ_SeqC: \t%.20f\n", tempo_MATRIZ_SeqC / count_for);
    printf("\tRuntime Médio tempo_MATRIZ_SeqBlC: \t%.20f\n", tempo_MATRIZ_SeqBlC / count_for );
    printf("\tRuntime Médio MATRIZ_ThreadC: \t\t%.20f\n", MATRIZ_ThreadC / count_for);
    printf("\tRuntime Médio MATRIZ_ThreadBlC: %f\n", MATRIZ_ThreadBlC / count_for);

    printf("\n\tSPEEDUP (MATRIZ_C)\n\t");
    //TODO
    printf("\n\tSPEEDUP (MATRIZ_BLC)\n\t");
    //TODO

    // %%%%%%%%%%%%%%%%%%%%%%%% BEGIN %%%%%%%%%%%%%%%%%%%%%%%%

    // LIBERAR MEMÓRIA
    /*
	LIBERAR MATRIZES
	FECHAR ARQUIVOS
    */

    // %%%%%%%%%%%%%%%%%%%%%%%% BEGIN %%%%%%%%%%%%%%%%%%%%%%%%
    //                   Liberação de memória
    //TODO limpar todos os vetores
    mliberar(mmult_MATRIZ_SeqC[0]);
    mliberar(mmult_MATRIZ_SeqBlC[0]);
    mliberar(mmult_MATRIZ_ThreadC[0]);
    //mliberar(mmult_MATRIZ_ThreadBlC[0]);

    free(mmult_MATRIZ_SeqC[0]);
    free(mmult_MATRIZ_SeqBlC[0]);
    free(mmult_MATRIZ_ThreadC[0]);
    //free(mmult_MATRIZ_ThreadBlC[0]);

    mliberar(&mat_a);
    mliberar(&mat_b);

    free(mmult_MATRIZ_SeqC);
    free(mmult_MATRIZ_SeqBlC);
    free(mmult_MATRIZ_ThreadC);
    //free(mmult_MATRIZ_ThreadBlC);
    // %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%
    return 0;
}