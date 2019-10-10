# PPA - Biblioteca de Matrizes

## Objetivo:
- Implementar uma biblioteca de manipulação de matrizes de inteiro em C.
- Implementar uma biblioteca com as operações de soma e multiplicação de matrizes.
- Implementar procedimentos para realizar a multiplicação de matrizes em blocos.
- Paralelizar as implementações de multiplicação de matrizes sequencial e em blocos.

## Arquivos:

A implementação do arquivo main_thread.c segue os passos descritos pelo professor no moodle.

## Implementação:

Importante observar as seguintes variáveis que afetam a execução do programa:
- **ntasks** que define o número de threads;
- **nro_submatrizes**: número de blocos, que deve ser compatível com o número de threads;
- **count_for** que define o número e repetições para executar a média dos tempos (runtime).

O speedup é calculado através da fórmula: TS/TP, sendo TS o tempo que demora para executar em código sequencial e TP o tempo em código paralelizado. Um speedup superior a 1 indica que houve ganho de performance.

O tamanho da matriz é um fator determinante para haver speedup, ao executar a multiplicação com matrizes 5x4 e 4x5 a performance em thread é inferior devido ao overhead, porém para matrizes maiores como 1000x500 e 500x1000 o ganho é significativo. O resultado depende também do número de threads e blocos configurados estaticamente no programa.

[BIBLIOTECAS IMPLEMENTADAS]
- **matrizv3.h**: headers das funções de gerência de matrizes.
- **matrizv3.c**: funções para manipular matrizes.
- **matriz-operacoesv3.h**: headers das funções de operações de matrizes que devem ser implementadas.
- **matriz-operacoesv3.c**: funções para operações de matrizes.
- **matriz-operacoes-threads.h**: headers das funções de multiplicação de matrizes em threads.
- **matriz-operacoes-threads.c**: funções para multiplicação de matrizes em threads.

[ARQUIVOS PARA EXECUÇÃO]
- **main_thread.c**: implementação das funções de multiplicação de matrizes sequencial, sequencial em bloco, em threads e threads em bloco.

[ARQUIVOS AUXILIARES]
- **arquivos .map**: matrizes geradas pela função gmat, que podem ser utilizadas para teste.
- **toolsv3.(c/h)**: biblioteca de leitura/escrita de matrizes em arquivos;
- **gera_matrizv3.c**: fontes do programa de geração de matrizes em arquivo;
- **makefile**: para compilar o arquivo fonte (ver detalhes sobre como gerar os arquivos mais abaixo);

## Compilação:

Para gerar os arquivos para execução é necessário executar o comando abaixo no terminal:

> `make`

Será apresentado em tela:
```
gcc -Wall -c matrizv3.c
gcc -Wall -c toolsv3.c
gcc -Wall matrizv3.o toolsv3.o gera_matrizv3.c -o gmat -pthread 
gcc   -pthread   pthreads-prod.c   -o pthreads-prod
gcc -Wall -c matriz-operacoesv3.c
gcc -Wall -c matriz-operacoes-threads.c
gcc -Wall matriz-operacoesv3.o matrizv3.o toolsv3.o matriz-operacoes-threads.o main_thread.c -o main_thread -pthread 


####### Exemplo de Execução #######
./main_thread 5x4-mat.map 4x5-mat.map
./main_thread 1000x500-mat.map 500x1000-mat.map 10
```

## Execução:

Para executar os arquivos gerados basta executar o comando abaixo (desde que esteja no mesmo diretório):

- Para gmat.c:
> `./gmat <lin> <col>`

Será apresentado em tela:
```
	#0	#1	#2	#3	#4	
0:	[92]	[99]	[43]	[36]	[46]	
1:	[69]	[70]	[4]	[76]	[34]	
2:	[41]	[43]	[30]	[99]	[54]	
3:	[43]	[50]	[64]	[92]	[22]	
4:	[22]	[6]	[31]	[7]	[93]	

		**** PRINT mat_c NxM(5,5) **** 
#####
 Arquivo com a matriz gerada (5x5-mat.map).
#####
	#0	#1	#2	#3	#4	
0:	[92]	[99]	[43]	[36]	[46]	
1:	[69]	[70]	[4]	[76]	[34]	
2:	[41]	[43]	[30]	[99]	[54]	
3:	[43]	[50]	[64]	[92]	[22]	
4:	[22]	[6]	[31]	[7]	[93]	

##### Arquivo 5x5-mat.map: VERIFICADO! #####
```

- Para main_thread.c:
> `./main_thread 1000x500-mat.map 500x1000-mat.map`

O terceiro parâmetro é opcional e identifica o número de threads e blocos.

Será apresentado em tela:
```
Executando multiplicação sequencial 10 de 10
Executando multiplicação sequencial em bloco 10 de 10
Executando multiplicação multithread 10 de 10
Executando multiplicação multithread em bloco 10 de 10

	COMPARAR MATRIZ_SeqC c/ MATRIZ_SeqBlC
	** Matrizes são iguais **

	COMPARAR MATRIZ_SeqC c/ MATRIZ_ThreadC
	** Matrizes são iguais **

	COMPARAR MATRIZ_SeqC c/ MATRIZ_ThreadBlC
	** Matrizes são iguais **

	Tempo Médio MATRIZ_SeqC:		4.107999 sec 
	Tempo Médio MATRIZ_SeqBlC:		5.862923 sec
	Tempo Médio MATRIZ_ThreadC:		2.244046 sec 
	Tempo Médio MATRIZ_ThreadBlC:	3.215806 sec 

	SPEEDUP (MATRIZ_C): 	1.83062 (183.06 %)
	SPEEDUP (MATRIZ_BLC): 	1.82316 (182.32 %)
```

## Análise dinâmica:

Para realizar uma análise dinâmica do código e verificar eventuais problemas, deve-se previamente ter instalado o programa *valgrind* e executar o comando abaixo:

- Para main_thread.c:
> `valgrind ./main_thread 5x4-mat.map 4x5-mat.map `

Será apresentado em tela:
```
==27120== Memcheck, a memory error detector
==27120== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==27120== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==27120== Command: ./main_thread 5x4-mat.map 4x5-mat.map
==27120== 
Executando multiplicação sequencial 10 de 10
Executando multiplicação sequencial em bloco 10 de 10
Executando multiplicação multithread 10 de 10
Executando multiplicação multithread em bloco 10 de 10

	COMPARAR MATRIZ_SeqC c/ MATRIZ_SeqBlC
	** Matrizes são iguais **

	COMPARAR MATRIZ_SeqC c/ MATRIZ_ThreadC
	** Matrizes são iguais **

	COMPARAR MATRIZ_SeqC c/ MATRIZ_ThreadBlC
	** Matrizes são iguais **

	Tempo Médio MATRIZ_SeqC:	0.000597 sec 
	Tempo Médio MATRIZ_SeqBlC:	0.001111 sec
	Tempo Médio MATRIZ_ThreadC:	0.009865 sec 
	Tempo Médio MATRIZ_ThreadBlC:	0.000586 sec 

	SPEEDUP (MATRIZ_C): 	0.06055 (6.06 %)
	SPEEDUP (MATRIZ_BLC): 	1.89550 (189.55 %)

==27120== 
==27120== HEAP SUMMARY:
==27120==     in use at exit: 20,436 bytes in 853 blocks
==27120==   total heap usage: 983 allocs, 130 frees, 51,955 bytes allocated
==27120== 
==27120== LEAK SUMMARY:
==27120==    definitely lost: 4,016 bytes in 131 blocks
==27120==    indirectly lost: 16,420 bytes in 722 blocks
==27120==      possibly lost: 0 bytes in 0 blocks
==27120==    still reachable: 0 bytes in 0 blocks
==27120==         suppressed: 0 bytes in 0 blocks
==27120== Rerun with --leak-check=full to see details of leaked memory
==27120== 
==27120== For counts of detected and suppressed errors, rerun with: -v
==27120== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```