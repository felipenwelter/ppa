# PPA - Biblioteca de Matrizes

## Objetivo:
- Implementar uma biblioteca de manipulação de matrizes de inteiro em C.
- Implementar uma biblioteca com as operações de soma e multiplicação de matrizes.
- Implementar procedimentos para realizar a multiplicação de matrizes em blocos.
- Paralelizar as implementações de multiplicação de matrizes sequencial e em blocos utilizando OpenMP.

## Arquivos:

A implementação do arquivo main_omp.c segue os passos descritos pelo professor no moodle.

## Implementação:

Importante observar as seguintes variáveis que afetam a execução do programa:
- **ntasks** que define o número de threads;
- **nro_submatrizes**: número de blocos, que deve ser compatível com o número de threads;
- **count_for** que define o número e repetições para executar a média dos tempos (runtime).

O speedup é calculado através da fórmula: TS/TP, sendo TS o tempo que demora para executar em código sequencial e TP o tempo em código paralelizado. Um speedup superior a 1 indica que houve ganho de performance.

O tamanho da matriz é um fator determinante para haver speedup, ao executar a multiplicação com matrizes 5x4 e 4x5 a performance em thread é inferior devido ao overhead, porém para matrizes maiores como 1000x500 e 500x1000 o ganho é significativo. O resultado depende também do número de threads e blocos configurados estaticamente no programa. Outro fator a considerar é o aninhamento de for's na multiplicação das matrizes, que segue a mesma estrutura tanto nas operações sequenciais quato paralelas, já otimizada. Em testes realizados com aninhamentos ikj (consultar função mmultiplicar), foi possível obter melhora de mais de 100% em relação ao aninhamento jki.

[BIBLIOTECAS IMPLEMENTADAS]
- **matrizv3.h**: headers das funções de gerência de matrizes.
- **matrizv3.c**: funções para manipular matrizes.
- **matriz-operacoesv3.h**: headers das funções de operações de matrizes que devem ser implementadas.
- **matriz-operacoesv3.c**: funções para operações de matrizes.
- **matriz-operacoes-omp.h**: headers das funções de multiplicação de matrizes usando OpenMP.
- **matriz-operacoes-omp.c**: funções para multiplicação de matrizes usando OpenMP.

[ARQUIVOS PARA EXECUÇÃO]
- **main_omp.c**: implementação das funções de multiplicação de matrizes sequencial, sequencial em bloco, em threads (usando OpenMP) e threads em bloco (usando OpenMP).

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
gcc -Wall matrizv3.o toolsv3.o gera_matrizv3.c -o gmat -fopenmp
gcc -Wall -c matriz-operacoesv3.c
gcc -Wall -c matriz-operacoes-omp.c
gcc -Wall matriz-operacoesv3.o matrizv3.o toolsv3.o matriz-operacoes-omp.o main_omp.c -o main_omp -fopenmp

####### Exemplo de Execução #######
./main_omp 5x4-mat.map 4x5-mat.map
./main_omp 1000x500-mat.map 500x1000-mat.map 10
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
> `./main_omp 1000x1000-mat.map 1000x1000-mat.map`

O terceiro parâmetro é opcional e identifica o número de threads e blocos.

Será apresentado em tela:
```Executando multiplicação sequencial 10 de 10
Executando multiplicação sequencial em bloco 10 de 10
Executando multiplicação multithread 10 de 10
Executando multiplicação multithread em bloco 10 de 10

	COMPARAR MATRIZ_SeqC c/ MATRIZ_SeqBlC
	** Matrizes são iguais **

	COMPARAR MATRIZ_SeqC c/ MATRIZ_ThreadC
	** Matrizes são iguais **

	COMPARAR MATRIZ_SeqC c/ MATRIZ_ThreadBlC
	** Matrizes são iguais **

	Tempo Médio MATRIZ_SeqC:	8.256238 sec 
	Tempo Médio MATRIZ_SeqBlC:	11.441760 sec
	Tempo Médio MATRIZ_ThreadC:	4.234516 sec 
	Tempo Médio MATRIZ_ThreadBlC:	6.078120 sec 

	SPEEDUP (MATRIZ_C): 	1.94975 (194.97 %)
	SPEEDUP (MATRIZ_BLC): 	1.88245 (188.25 %)
```

## Análise dinâmica:

Para realizar uma análise dinâmica do código e verificar eventuais problemas, deve-se previamente ter instalado o programa *valgrind* e executar o comando abaixo:

- Para main_thread.c:
> `valgrind ./main_omp 100x100-mat.map 100x100-mat.map `

Será apresentado em tela:
```
==7394== Memcheck, a memory error detector
==7394== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==7394== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==7394== Command: ./main_omp 100x100-mat.map 100x100-mat.map
==7394== 
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

	Tempo Médio MATRIZ_SeqC:	0.158191 sec 
	Tempo Médio MATRIZ_SeqBlC:	0.243473 sec
	Tempo Médio MATRIZ_ThreadC:	0.136051 sec 
	Tempo Médio MATRIZ_ThreadBlC:	0.225305 sec 

	SPEEDUP (MATRIZ_C): 	1.16273 (116.27 %)
	SPEEDUP (MATRIZ_BLC): 	1.08064 (108.06 %)

==7394== 
==7394== HEAP SUMMARY:
==7394==     in use at exit: 6,021,888 bytes in 15,605 blocks
==7394==   total heap usage: 36,647 allocs, 21,042 frees, 6,861,290 bytes allocated
==7394== 
==7394== LEAK SUMMARY:
==7394==    definitely lost: 7,536 bytes in 151 blocks
==7394==    indirectly lost: 6,011,040 bytes in 15,447 blocks
==7394==      possibly lost: 864 bytes in 3 blocks
==7394==    still reachable: 2,448 bytes in 4 blocks
==7394==         suppressed: 0 bytes in 0 blocks
==7394== Rerun with --leak-check=full to see details of leaked memory
==7394== 
==7394== For counts of detected and suppressed errors, rerun with: -v
==7394== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```