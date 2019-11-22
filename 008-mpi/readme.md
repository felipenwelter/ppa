# PPA - Biblioteca de Matrizes

## Objetivo:
- Implementar uma biblioteca de manipulação de matrizes de inteiro em C.
- Implementar uma biblioteca com as operações de soma e multiplicação de matrizes.
- Implementar procedimentos para realizar a multiplicação de matrizes em blocos.
- Paralelizar as implementações de multiplicação de matrizes sequencial e em blocos utilizando MPI.

## Arquivos:

Implementação no arquivo main_mpi.c.

## Implementação:

Importante observar as seguintes condições que afetam a execução do programa:
- o programa está configurado para trabalhar com multiplicação de matrizes quadradas (em especial o processo de scatter e gather na multiplicação em threads);
- o número de linhas/colunas da matriz deve ser divisível pelo número de threads, por exemplo: para matriz 100x100 pode utilizar 2 ou 4 threads, mas não 3.
- caso venha a executar o programa utilizando mais de uma máquina, é importante realizar um ssh em cada uma das máquinas para garantir que estão se comunicando, além de copiar o arquivo de execução entre elas. As configurações ficam no arquivo (hostfile) mp.

O speedup é calculado através da fórmula: TS/TP, sendo TS o tempo que demora para executar em código sequencial e TP o tempo em código paralelizado. Um speedup superior a 1 indica que houve ganho de performance.

O tamanho da matriz é um fator determinante para haver speedup, ao executar a multiplicação entre matrizes 4x4 a performance em thread é inferior devido ao overhead, porém para matrizes maiores como 1000x1000 pode se perceber ganho. O resultado depende também do número de threads e blocos configurados no programa.

[BIBLIOTECAS IMPLEMENTADAS]
- **matrizv3.h**: headers das funções de gerência de matrizes.
- **matrizv3.c**: funções para manipular matrizes.
- **matriz-operacoesv3.h**: headers das funções de operações de matrizes que devem ser implementadas.
- **matriz-operacoesv3.c**: funções para operações de matrizes.
- **matriz-operacoes-mpi.h**: headers das funções de multiplicação de matrizes usando OpenMP.
- **matriz-operacoes-mpi.c**: funções para multiplicação de matrizes usando OpenMP.

[ARQUIVOS PARA EXECUÇÃO]
- **main_mpi.c**: implementação das funções de multiplicação de matrizes sequencial, sequencial em bloco, em threads (usando MPI) e threads em bloco (usando MPI).

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
mpicc -Wall -O3 -c matrizv3.c
mpicc -Wall -O3 -c toolsv3.c
mpicc -Wall -O3 matrizv3.o toolsv3.o gera_matrizv3.c -o gmat 
mpicc -Wall -O3 -c matriz-operacoesv3.c
mpicc -Wall -O3 -c matriz-operacoes-mpi.c
mpicc -Wall -O3 matriz-operacoesv3.o matrizv3.o toolsv3.o matriz-operacoes-mpi.o main_mpi.c -o main_mpi 


####### Exemplo de Execução #######
mpirun -np 4 --hostfile mp main_mpi 1000x1000-mat.map 1000x1000-mat.map
```

## Execução:

Para executar os arquivos gerados basta executar o comando abaixo (desde que esteja no mesmo diretório):

- Para gmat.c:
> `./gmat <lin> <col>`

Será apresentado em tela:
```
	#0	#1	#2	#3	#4	
0:	[92]	[99]	[43]	[36]	[46]	
1:	[69]	[70]	[42]	[76]	[34]	
2:	[41]	[43]	[30]	[99]	[54]	
3:	[43]	[50]	[64]	[92]	[22]	
4:	[22]	[61]	[31]	[72]	[93]	

		**** PRINT mat_c NxM(5,5) **** 
#####
 Arquivo com a matriz gerada (5x5-mat.map).
#####
	#0	#1	#2	#3	#4	
0:	[92]	[99]	[43]	[36]	[46]	
1:	[69]	[70]	[42]	[76]	[34]	
2:	[41]	[43]	[30]	[99]	[54]	
3:	[43]	[50]	[64]	[92]	[22]	
4:	[22]	[61]	[31]	[72]	[93]	

##### Arquivo 5x5-mat.map: VERIFICADO! #####
```

- Para main_mpi.c:
> `mpirun -np 4 --hostfile mp main_mpi 1000x1000-mat.map 1000x1000-mat.map`

Será apresentado em tela:
```
Executando multiplicação sequencial  .. OK
Executando multiplicação em blocos  .. OK
Executando multiplicação sequencial em threads .. OK
Executando multiplicação blocos em threads .. OK

	COMPARAR MATRIZ_SeqC c/ MATRIZ_SeqBlC
	** Matrizes são iguais **

	COMPARAR MATRIZ_SeqC c/ MATRIZ_ThreadC
	** Matrizes são iguais **

	COMPARAR MATRIZ_SeqC c/ MATRIZ_ThreadBlC
	** Matrizes são iguais **

	Tempo Médio MATRIZ_SeqC:		10.101747 sec 
	Tempo Médio MATRIZ_SeqBlC:		21.454070 sec
	Tempo Médio MATRIZ_ThreadC:		4.615389 sec 
	Tempo Médio MATRIZ_ThreadBlC:	6.105211 sec 

	SPEEDUP (MATRIZ_C): 	2.18871 (218.87 %)
	SPEEDUP (MATRIZ_BLC): 	3.51406 (351.41 %)
```