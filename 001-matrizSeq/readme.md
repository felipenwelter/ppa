Disciplina de Programação Paralela Avançada

## Objetivo:
- Implementar uma biblioteca de manipulação de matrizes de inteiro em C.


## Arquivos:

A implementação do arquivo main.c segue o exemplo disponibilizado no moodle. A implementação de mainEx01 também segue a estrutura original.

[BIBLIOTECAS IMPLEMENTADAS]
- **matrizv3.h**: headers das funções de gerência de matrizes;
- **matrizv3.c**: funções para manipular matrizes;
- **matriz-operacoesv3.h**: headers das funções de operações de matrizes que devem ser implementadas;
- **matriz-operacoesv3.c**: ainda não implementado;

[ARQUIVOS PARA EXECUÇÃO]
- **main.c**: código para teste simplificado da biblioteca de matrizes, seguindo a estrutura do moodle;
- **mainEx01.c**: exercício 01, que realiza a leitura de uma matriz de arquivo e exetuca as operações disponíveis na biblioteca de matrizes. Segue implementação original disponibilizada pelo professor;
- **mainEx02.c**: exercício 02, ainda não implementado;

[ARQUIVOS AUXILIARES]
- **mat_a3x4.example** e **mat_b4x3.example**: matrizes exemplos A (3x4) e B(4x3);
- **toolsv3.(c/h)**: biblioteca de leitura/escrita de matrizes em arquivos;
- **gera_matrizv3.c**: fontes do programa de geração de matrizes em arquivo;
- **makefile**: para compilar o arquivo fonte (ver detalhes sobre como gerar os arquivos mais abaixo);

## Compilação:

Para gerar os arquivos para execução é necessário executar o comando abaixo no terminal:

Para main.c
> `make main`

Será apresentado em tela:
```
gcc -Wall -O3 matrizv3.o toolsv3.o main.c -o main 
```

Para mainEx01.c:
> `make mainEx01`

Será apresentado em tela:
```
gcc -Wall -O3 matrizv3.o toolsv3.o mainEx01.c -o mainEx01
```

## Execução:

Para executar os arquivos gerados basta executar o comando abaixo (desde que esteja no mesmo diretório):

Para main.c:
> `./main`

Será apresentado em tela:
```
	#0	#1	#2	#3	#4	#5	#6	#7	#8	#9	
0:	[0]	[0]	[0]	[0]	[0]	[0]	[0]	[0]	[0]	[0]	
1:	[0]	[0]	[0]	[0]	[0]	[0]	[0]	[0]	[0]	[0]	
2:	[0]	[0]	[0]	[0]	[0]	[0]	[0]	[0]	[0]	[0]	
3:	[0]	[0]	[0]	[0]	[0]	[0]	[0]	[0]	[0]	[0]	
4:	[0]	[0]	[0]	[0]	[0]	[0]	[0]	[0]	[0]	[0]	
5:	[0]	[0]	[0]	[0]	[0]	[0]	[0]	[0]	[0]	[0]	
6:	[0]	[0]	[0]	[0]	[0]	[0]	[0]	[0]	[0]	[0]	
7:	[0]	[0]	[0]	[0]	[0]	[0]	[0]	[0]	[0]	[0]	
8:	[0]	[0]	[0]	[0]	[0]	[0]	[0]	[0]	[0]	[0]	
9:	[0]	[0]	[0]	[0]	[0]	[0]	[0]	[0]	[0]	[0]	

	#0	#1	#2	#3	#4	#5	#6	#7	#8	#9	
0:	[0]	[0]	[0]	[0]	[0]	[0]	[0]	[0]	[0]	[0]	
1:	[0]	[0]	[0]	[0]	[0]	[0]	[0]	[0]	[0]	[0]	
2:	[0]	[0]	[0]	[0]	[0]	[0]	[0]	[0]	[0]	[0]	
3:	[0]	[0]	[0]	[0]	[0]	[0]	[0]	[0]	[0]	[0]	
4:	[0]	[0]	[0]	[0]	[0]	[0]	[0]	[0]	[0]	[0]	
5:	[0]	[0]	[0]	[0]	[0]	[0]	[0]	[0]	[0]	[0]	
6:	[0]	[0]	[0]	[0]	[0]	[0]	[0]	[0]	[0]	[0]	
7:	[0]	[0]	[0]	[0]	[0]	[0]	[0]	[0]	[0]	[0]	
8:	[0]	[0]	[0]	[0]	[0]	[0]	[0]	[0]	[0]	[0]	
9:	[0]	[0]	[0]	[0]	[0]	[0]	[0]	[0]	[0]	[0]	

	#0	#1	#2	#3	#4	#5	#6	#7	#8	#9	
0:	[44]	[28]	[95]	[76]	[97]	[2]	[91]	[63]	[17]	[60]	
1:	[34]	[52]	[65]	[54]	[60]	[92]	[46]	[31]	[98]	[35]	
2:	[86]	[37]	[93]	[35]	[73]	[77]	[93]	[27]	[87]	[74]	
3:	[15]	[31]	[2]	[10]	[59]	[51]	[65]	[2]	[15]	[34]	
4:	[62]	[1]	[39]	[28]	[55]	[51]	[72]	[53]	[82]	[70]	
5:	[40]	[21]	[60]	[34]	[8]	[33]	[63]	[1]	[60]	[2]	
6:	[27]	[75]	[85]	[81]	[38]	[96]	[33]	[55]	[99]	[48]	
7:	[41]	[13]	[1]	[80]	[93]	[56]	[31]	[66]	[61]	[66]	
8:	[36]	[1]	[39]	[96]	[35]	[47]	[29]	[50]	[1]	[89]	
9:	[52]	[28]	[17]	[89]	[10]	[7]	[86]	[95]	[14]	[85]	
```

Para mainEx01.c:
> `./mainEx01 mat_a3x4.example mat_b4x3.example`

Será apresentado em tela:
```
 ##### Comparação dos resultados das matrizes #####
[mat_a vs mat_b]	** Erro: Matrizes tem tamanhos diferentes **
```

A mensagem acima é apresentada porque as matrizes tem tamanhos diferentes e não podem ser comparadas. Caso a chamada seja feita com matrizes do mesmo tamanho, nenhuma mensagem será apresentada.


## Análise dinâmica:

Para realizar uma análise dinâmica do código e verificar eventuais problemas, deve-se previamente ter instalado o programa *valgrind* e executar o comando abaixo:

Para análise simplificada:
> `valgrind ./main`

Será apresentado em tela:
```
==20635== Memcheck, a memory error detector
==20635== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==20635== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==20635== Command: ./main
==20635== 

...

==20635== 
==20635== HEAP SUMMARY:
==20635==     in use at exit: 0 bytes in 0 blocks
==20635==   total heap usage: 12 allocs, 12 frees, 1,504 bytes allocated
==20635== 
==20635== All heap blocks were freed -- no leaks are possible
==20635== 
==20635== For counts of detected and suppressed errors, rerun with: -v
==20635== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

Para análise detalhada:
> `valgrind --leak-check=full ./main`

Será apresentado em tela:
```
==20845== Memcheck, a memory error detector
==20845== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==20845== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==20845== Command: ./main
==20845== 

...

==20845== 
==20845== HEAP SUMMARY:
==20845==     in use at exit: 0 bytes in 0 blocks
==20845==   total heap usage: 12 allocs, 12 frees, 1,504 bytes allocated
==20845== 
==20845== All heap blocks were freed -- no leaks are possible
==20845== 
==20845== For counts of detected and suppressed errors, rerun with: -v
==20845== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```


Para análise simplificada:
> `valgrind ./mainEx01 mat_a3x4.example mat_b4x3.example`

Será apresentado em tela:
```
==20862== Memcheck, a memory error detector
==20862== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==20862== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==20862== Command: ./mainEx01 mat_a3x4.example mat_b4x3.example
==20862== 

 ##### Comparação dos resultados das matrizes #####
[mat_a vs mat_b]	** Erro: Matrizes tem tamanhos diferentes **
==20862== 
==20862== HEAP SUMMARY:
==20862==     in use at exit: 0 bytes in 0 blocks
==20862==   total heap usage: 70 allocs, 70 frees, 11,301 bytes allocated
==20862== 
==20862== All heap blocks were freed -- no leaks are possible
==20862== 
==20862== For counts of detected and suppressed errors, rerun with: -v
==20862== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

Para análise detalhada:
> `valgrind --leak-check=full ./mainEx01 mat_a3x4.example mat_b4x3.example`

Será apresentado em tela:
```
==20893== Memcheck, a memory error detector
==20893== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==20893== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==20893== Command: ./mainEx01 mat_a3x4.example mat_b4x3.example
==20893== 

 ##### Comparação dos resultados das matrizes #####
[mat_a vs mat_b]	** Erro: Matrizes tem tamanhos diferentes **
==20893== 
==20893== HEAP SUMMARY:
==20893==     in use at exit: 0 bytes in 0 blocks
==20893==   total heap usage: 70 allocs, 70 frees, 11,301 bytes allocated
==20893== 
==20893== All heap blocks were freed -- no leaks are possible
==20893== 
==20893== For counts of detected and suppressed errors, rerun with: -v
==20893== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```