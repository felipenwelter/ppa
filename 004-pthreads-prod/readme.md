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
- **5x4-mat.map** e **4x5-mat.map**: matrizes exemplos A (5x4) e B(4x5).
- **1000x500-mat.map** e **500x1000-mat.map**: matrizes exemplos A (1000x500) e B(500x1000)
- **arquivos .map**: matrizes geradas pela função gmat, que podem ser utilizadas para teste.
- **toolsv3.(c/h)**: biblioteca de leitura/escrita de matrizes em arquivos;
- **gera_matrizv3.c**: fontes do programa de geração de matrizes em arquivo;
- **makefile**: para compilar o arquivo fonte (ver detalhes sobre como gerar os arquivos mais abaixo);

## Compilação:

Para gerar os arquivos para execução é necessário executar o comando abaixo no terminal:

> `make`

Será apresentado em tela:
```
gcc -Wall matriz-operacoesv3.o matrizv3.o toolsv3.o matriz-operacoes-threads.o main_thread.c -o main_thread -pthread 

####### Exemplo de Execução #######
./main_thread 5x4-mat.map 4x5-mat.map
./main_thread 1000x500-mat.map 500x1000-mat.map
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

	Tempo Médio tempo_MATRIZ_SeqC:		4.107999 sec 
	Tempo Médio tempo_MATRIZ_SeqBlC:	5.862923 sec
	Tempo Médio MATRIZ_ThreadC:		2.244046 sec 
	Tempo Médio MATRIZ_ThreadBlC:		3.215806 sec 

	SPEEDUP (MATRIZ_C): 	1.83062
	SPEEDUP (MATRIZ_BLC): 	1.82316
```

## Análise dinâmica:

Para realizar uma análise dinâmica do código e verificar eventuais problemas, deve-se previamente ter instalado o programa *valgrind* e executar o comando abaixo:

- Para main_thread.c:
> `valgrind ./main_thread 1000x500-mat.map 500x1000-mat.map`

Será apresentado em tela:
```
==22881== Memcheck, a memory error detector
==22881== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==22881== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==22881== Command: ./main_thread 4x5-mat.map 5x4-mat.map
==22881== 
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

	Tempo Médio tempo_MATRIZ_SeqC:		0.000598 sec 
	Tempo Médio tempo_MATRIZ_SeqBlC:	0.001338 sec
	Tempo Médio MATRIZ_ThreadC:		0.018183 sec 
	Tempo Médio MATRIZ_ThreadBlC:		0.000918 sec 

	SPEEDUP (MATRIZ_C): 	0.03288
	SPEEDUP (MATRIZ_BLC): 	1.45714

==22881== 
==22881== HEAP SUMMARY:
==22881==     in use at exit: 35,728 bytes in 1,506 blocks
==22881==   total heap usage: 1,634 allocs, 128 frees, 67,615 bytes allocated
==22881== 
==22881== LEAK SUMMARY:
==22881==    definitely lost: 8,176 bytes in 171 blocks
==22881==    indirectly lost: 27,552 bytes in 1,335 blocks
==22881==      possibly lost: 0 bytes in 0 blocks
==22881==    still reachable: 0 bytes in 0 blocks
==22881==         suppressed: 0 bytes in 0 blocks
==22881== Rerun with --leak-check=full to see details of leaked memory
==22881== 
==22881== For counts of detected and suppressed errors, rerun with: -v
==22881== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```