# PPA - Biblioteca de Matrizes

## Objetivo:
- Implementar uma biblioteca de manipulação de matrizes de inteiro em C.
- Implementar uma biblioteca com as operações de soma e multiplicação de matrizes.
- Implementar procedimentos para realizar a multiplicação de matrizes em blocos.

## Arquivos:

A implementação do arquivo main.c segue o exemplo disponibilizado no moodle. A implementação de mainEx01 e mainEx02 também segue a estrutura original. O arquivo mainEx03 teve pequenas alterações a partir do exemplo disponibilizado pelo professor.

[BIBLIOTECAS IMPLEMENTADAS]
- **matrizv3.h**: headers das funções de gerência de matrizes;
- **matrizv3.c**: funções para manipular matrizes;
- **matriz-operacoesv3.h**: headers das funções de operações de matrizes que devem ser implementadas;
- **matriz-operacoesv3.c**: funções para operações de matrizes;

[ARQUIVOS PARA EXECUÇÃO]
- **main.c**: código para teste simplificado da biblioteca de matrizes, seguindo a estrutura do moodle;
- **mainEx01.c**: exercício 01, que realiza a leitura de uma matriz de arquivo e executa as operações disponíveis na biblioteca de matrizes. Segue implementação original disponibilizada pelo professor;
- **mainEx02.c**: exercício 02, que realiza a soma e multiplicação de matrizes.
- **mainEx03.c**: exercício 03, que realiza a multiplicação de matrizes em blocos.

[ARQUIVOS AUXILIARES]
- **mat_a3x4.example** e **mat_b4x3.example**: matrizes exemplos A (3x4) e B(4x3);
- **arquivos .map**: matrizes geradas pela função gmat, que podem ser utilizadas para teste.
- **toolsv3.(c/h)**: biblioteca de leitura/escrita de matrizes em arquivos;
- **gera_matrizv3.c**: fontes do programa de geração de matrizes em arquivo;
- **makefile**: para compilar o arquivo fonte (ver detalhes sobre como gerar os arquivos mais abaixo);

## Compilação:

Para gerar os arquivos para execução é necessário executar o comando abaixo no terminal:

> `make`

Será apresentado em tela:
```
gcc -Wall -O3 matrizv3.o toolsv3.o mainEx01.c -o mainEx01 
gcc -Wall -O3 matriz-operacoesv3.o matrizv3.o toolsv3.o mainEx02.c -o mainEx02 
gcc -Wall -O3 matriz-operacoesv3.o matrizv3.o toolsv3.o mainEx03.c -o mainEx03 


####### Exemplo de Execução #######
./mainEx01 mat_a3x4.example mat_b4x3.example
./mainEx02 5x5-mat.map 5x5-mat.map
./mainEx03 5x5-mat.map 5x5-mat.map
```

## Execução:

Para executar os arquivos gerados basta executar o comando abaixo (desde que esteja no mesmo diretório):

- Para gmat.c:
> `./gmat <lin> <col>`

Será apresentado em tela:
```
	#0	#1	#2	#3	#4	
0:	[84]	[44]	[69]	[28]	[45]	
1:	[47]	[46]	[34]	[29]	[38]	
2:	[10]	[2]	[25]	[94]	[72]	
3:	[56]	[87]	[34]	[98]	[27]	
4:	[31]	[73]	[9]	[83]	[79]	

		**** PRINT mat_c NxM(5,5) **** 
#####
 Arquivo com a matriz gerada (5x5-mat.map).
#####
	#0	#1	#2	#3	#4	
0:	[84]	[44]	[69]	[28]	[45]	
1:	[47]	[46]	[34]	[29]	[38]	
2:	[10]	[2]	[25]	[94]	[72]	
3:	[56]	[87]	[34]	[98]	[27]	
4:	[31]	[73]	[9]	[83]	[79]	

##### Arquivo 5x5-mat.map: VERIFICADO! #####
```

- Para main.c:
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

- Para mainEx01.c:
> `./mainEx01 mat_a3x4.example mat_b4x3.example`

Será apresentado em tela:
```
 ##### Comparação dos resultados das matrizes #####
[mat_a vs mat_b]	** Erro: Matrizes tem tamanhos diferentes **
```

A mensagem acima é apresentada porque as matrizes tem tamanhos diferentes e não podem ser comparadas. Caso a chamada seja feita com matrizes do mesmo tamanho será impresso se são iguais ou diferentes.

- Para mainEx02.c:
> `./mainEx02 5x5-mat.map 5x5-mat.map`

Será apresentado em tela:
```

 ##### somar_t0 de Matrizes #####
        #0      #1      #2      #3      #4
0:      [4]     [2]     [6]     [14]    [6]
1:      [4]     [4]     [4]     [14]    [0]
2:      [16]    [12]    [8]     [4]     [14]
3:      [8]     [10]    [18]    [6]     [2]
4:      [4]     [14]    [6]     [8]     [0]

        Runtime: 0.000004

 ##### somar_t1 de Matrizes #####
        #0      #1      #2      #3      #4
0:      [4]     [2]     [6]     [14]    [6]
1:      [4]     [4]     [4]     [14]    [0]
2:      [16]    [12]    [8]     [4]     [14]
3:      [8]     [10]    [18]    [6]     [2]
4:      [4]     [14]    [6]     [8]     [0]

        Runtime: 0.000004

%%%%%%%%

 ##### multiplicar_t0 de Matrizes #####
        #0      #1      #2      #3      #4
0:      [128]   [156]   [184]   [120]   [68]
1:      [104]   [106]   [162]   [106]   [54]
2:      [164]   [206]   [182]   [280]   [108]
3:      [208]   [180]   [176]   [188]   [156]
4:      [116]   [108]   [136]   [162]   [62]

        Runtime: 0.000005

 ##### multiplicar_t1 de Matrizes #####
        #0      #1      #2      #3      #4
0:      [128]   [156]   [184]   [120]   [68]
1:      [104]   [106]   [162]   [106]   [54]
2:      [164]   [206]   [182]   [280]   [108]
3:      [208]   [180]   [176]   [188]   [156]
4:      [116]   [108]   [136]   [162]   [62]

        Runtime: 0.000004

 ##### multiplicar_t2 de Matrizes #####
        #0      #1      #2      #3      #4
0:      [128]   [156]   [184]   [120]   [68]
1:      [104]   [106]   [162]   [106]   [54]
2:      [164]   [206]   [182]   [280]   [108]
3:      [208]   [180]   [176]   [188]   [156]
4:      [116]   [108]   [136]   [162]   [62]

        Runtime: 0.000004

 ##### multiplicar_t3 de Matrizes #####
        #0      #1      #2      #3      #4
0:      [128]   [156]   [184]   [120]   [68]
1:      [104]   [106]   [162]   [106]   [54]
2:      [164]   [206]   [182]   [280]   [108]
3:      [208]   [180]   [176]   [188]   [156]
4:      [116]   [108]   [136]   [162]   [62]

        Runtime: 0.000003

 ##### multiplicar_t4 de Matrizes #####
        #0      #1      #2      #3      #4
0:      [128]   [156]   [184]   [120]   [68]
1:      [104]   [106]   [162]   [106]   [54]
2:      [164]   [206]   [182]   [280]   [108]
3:      [208]   [180]   [176]   [188]   [156]
4:      [116]   [108]   [136]   [162]   [62]

        Runtime: 0.000003

 ##### multiplicar_t5 de Matrizes #####
        #0      #1      #2      #3      #4
0:      [128]   [156]   [184]   [120]   [68]
1:      [104]   [106]   [162]   [106]   [54]
2:      [164]   [206]   [182]   [280]   [108]
3:      [208]   [180]   [176]   [188]   [156]
4:      [116]   [108]   [136]   [162]   [62]

        Runtime: 0.000003

 ##### Comparação dos resultados da adição de matrizes #####
[soma_t0 vs soma_t1]    ** Matrizes são iguais **

 ##### Comparação dos resultados da Multiplicação de matrizes #####
[mult_t0 vs mult_t1]    ** Matrizes são iguais **
[mult_t0 vs mult_t2]    ** Matrizes são iguais **
[mult_t0 vs mult_t3]    ** Matrizes são iguais **
[mult_t0 vs mult_t4]    ** Matrizes são iguais **
[mult_t0 vs mult_t5]    ** Matrizes são iguais **
```

- Para mainEx03.c:
> `./mainEx03 5x5-mat.map 5x5-mat.map`

Será apresentado em tela:
```
 ##### multiplicar_t1 de Matrizes #####
	#0	#1	#2	#3	#4	
0:	[112]	[63]	[130]	[63]	[119]	
1:	[174]	[95]	[194]	[105]	[179]	
2:	[83]	[48]	[112]	[89]	[106]	
3:	[56]	[30]	[66]	[48]	[69]	
4:	[134]	[81]	[168]	[113]	[154]	

	Runtime: 0.000006

 ##### multiplicar_t1 de Matrizes #####
	#0	#1	#2	#3	#4	
0:	[112]	[63]	[130]	[63]	[119]	
1:	[174]	[95]	[194]	[105]	[179]	
2:	[83]	[48]	[112]	[89]	[106]	
3:	[56]	[30]	[66]	[48]	[69]	
4:	[134]	[81]	[168]	[113]	[154]	

	Runtime: 0.000009

 ##### Comparação dos resultados da Multiplicação de matrizes #####
[mult_t0 vs multbloco_t0]	** Matrizes são iguais **
```

## Análise dinâmica:

Para realizar uma análise dinâmica do código e verificar eventuais problemas, deve-se previamente ter instalado o programa *valgrind* e executar o comando abaixo:

- Para main.c:
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

- Para mainEx01.c:
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

- Para mainEx02.c:
> `valgrind ./mainEx02 5x5-mat.map 5x5-mat.map`

Será apresentado em tela:
```
==13473== Memcheck, a memory error detector
==13473== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==13473== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==13473== Command: ./mainEx02 5x5-mat.map 5x5-mat.map
==13473== 

 ##### somar_t0 de Matrizes #####
        #0      #1      #2      #3      #4
0:      [4]     [2]     [6]     [14]    [6]
1:      [4]     [4]     [4]     [14]    [0]
2:      [16]    [12]    [8]     [4]     [14]
3:      [8]     [10]    [18]    [6]     [2]
4:      [4]     [14]    [6]     [8]     [0]

        Runtime: 0.004757

 ##### somar_t1 de Matrizes #####
        #0      #1      #2      #3      #4
0:      [4]     [2]     [6]     [14]    [6]
1:      [4]     [4]     [4]     [14]    [0]
2:      [16]    [12]    [8]     [4]     [14]
3:      [8]     [10]    [18]    [6]     [2]
4:      [4]     [14]    [6]     [8]     [0]

        Runtime: 0.000787

%%%%%%%%

 ##### multiplicar_t0 de Matrizes #####
        #0      #1      #2      #3      #4
0:      [128]   [156]   [184]   [120]   [68]
1:      [104]   [106]   [162]   [106]   [54]
2:      [164]   [206]   [182]   [280]   [108]
3:      [208]   [180]   [176]   [188]   [156]
4:      [116]   [108]   [136]   [162]   [62]

        Runtime: 0.009095

 ##### multiplicar_t1 de Matrizes #####
        #0      #1      #2      #3      #4
0:      [128]   [156]   [184]   [120]   [68]
1:      [104]   [106]   [162]   [106]   [54]
2:      [164]   [206]   [182]   [280]   [108]
3:      [208]   [180]   [176]   [188]   [156]
4:      [116]   [108]   [136]   [162]   [62]

        Runtime: 0.003601

 ##### multiplicar_t2 de Matrizes #####
        #0      #1      #2      #3      #4
0:      [128]   [156]   [184]   [120]   [68]
1:      [104]   [106]   [162]   [106]   [54]
2:      [164]   [206]   [182]   [280]   [108]
3:      [208]   [180]   [176]   [188]   [156]
4:      [116]   [108]   [136]   [162]   [62]

        Runtime: 0.002786

 ##### multiplicar_t3 de Matrizes #####
        #0      #1      #2      #3      #4
0:      [128]   [156]   [184]   [120]   [68]
1:      [104]   [106]   [162]   [106]   [54]
2:      [164]   [206]   [182]   [280]   [108]
3:      [208]   [180]   [176]   [188]   [156]
4:      [116]   [108]   [136]   [162]   [62]

        Runtime: 0.002810

 ##### multiplicar_t4 de Matrizes #####
        #0      #1      #2      #3      #4
0:      [128]   [156]   [184]   [120]   [68]
1:      [104]   [106]   [162]   [106]   [54]
2:      [164]   [206]   [182]   [280]   [108]
3:      [208]   [180]   [176]   [188]   [156]
4:      [116]   [108]   [136]   [162]   [62]

        Runtime: 0.001898

 ##### multiplicar_t5 de Matrizes #####
        #0      #1      #2      #3      #4
0:      [128]   [156]   [184]   [120]   [68]
1:      [104]   [106]   [162]   [106]   [54]
2:      [164]   [206]   [182]   [280]   [108]
3:      [208]   [180]   [176]   [188]   [156]
4:      [116]   [108]   [136]   [162]   [62]

        Runtime: 0.001875

 ##### Comparação dos resultados da adição de matrizes #####
[soma_t0 vs soma_t1]    ** Matrizes são iguais **

 ##### Comparação dos resultados da Multiplicação de matrizes #####
[mult_t0 vs mult_t1]    ** Matrizes são iguais **
[mult_t0 vs mult_t2]    ** Matrizes são iguais **
[mult_t0 vs mult_t3]    ** Matrizes são iguais **
[mult_t0 vs mult_t4]    ** Matrizes são iguais **
[mult_t0 vs mult_t5]    ** Matrizes são iguais **
==13473== 
==13473== HEAP SUMMARY:
==13473==     in use at exit: 0 bytes in 0 blocks
==13473==   total heap usage: 179 allocs, 179 frees, 50,536 bytes allocated
==13473== 
==13473== All heap blocks were freed -- no leaks are possible
==13473== 
==13473== For counts of detected and suppressed errors, rerun with: -v
==13473== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

- Para mainEx03.c:
> `valgrind ./mainEx02 5x5-mat.map 5x5-mat.map`

Será apresentado em tela:
```
==13801== Memcheck, a memory error detector
==13801== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==13801== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==13801== Command: ./mainEx03 5x5-mat.map 5x5-mat.map
==13801== 

%%%%%%%%

 ##### multiplicar_t1 de Matrizes #####
	#0	#1	#2	#3	#4	
0:	[112]	[63]	[130]	[63]	[119]	
1:	[174]	[95]	[194]	[105]	[179]	
2:	[83]	[48]	[112]	[89]	[106]	
3:	[56]	[30]	[66]	[48]	[69]	
4:	[134]	[81]	[168]	[113]	[154]	

	Runtime: 0.006377

 ##### multiplicar_t1 de Matrizes #####
	#0	#1	#2	#3	#4	
0:	[112]	[63]	[130]	[63]	[119]	
1:	[174]	[95]	[194]	[105]	[179]	
2:	[83]	[48]	[112]	[89]	[106]	
3:	[56]	[30]	[66]	[48]	[69]	
4:	[134]	[81]	[168]	[113]	[154]	

	Runtime: 0.008335

 ##### Comparação dos resultados da Multiplicação de matrizes #####
[mult_t0 vs multbloco_t0]	** Matrizes são iguais **
==13801== 
==13801== HEAP SUMMARY:
==13801==     in use at exit: 680 bytes in 31 blocks
==13801==   total heap usage: 154 allocs, 123 frees, 22,328 bytes allocated
==13801== 
==13801== LEAK SUMMARY:
==13801==    definitely lost: 48 bytes in 3 blocks
==13801==    indirectly lost: 632 bytes in 28 blocks
==13801==      possibly lost: 0 bytes in 0 blocks
==13801==    still reachable: 0 bytes in 0 blocks
==13801==         suppressed: 0 bytes in 0 blocks
==13801== Rerun with --leak-check=full to see details of leaked memory
==13801== 
==13801== For counts of detected and suppressed errors, rerun with: -v
==13801== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```





aluno7@ppa-1 ~/new/ppa/004-pthreads-prod $ ./main_thread 1000x500-mat.map 500x1000-mat.map 
sequencial 0. tempo: 4.05869293212890625000 	 avg= 4.05869293212890625000
sequencial 1. tempo: 4.10863494873046875000 	 avg= 4.08366394042968750000
sequencial 2. tempo: 3.98025298118591308594 	 avg= 4.04919362068176269531
sequencial 3. tempo: 4.02726697921752929688 	 avg= 4.04371196031570434570
sequencial 4. tempo: 3.99447417259216308594 	 avg= 4.03386440277099644902
sequencial 5. tempo: 4.01588010787963867188 	 avg= 4.03086702028910348616
sequencial 6. tempo: 4.14142608642578125000 	 avg= 4.04666117259434265918
sequencial 7. tempo: 4.11794400215148925781 	 avg= 4.05557152628898620605
sequencial 8. tempo: 4.11861491203308105469 	 avg= 4.06257634692721936176
sequencial 9. tempo: 4.04954910278320312500 	 avg= 4.06127362251281720518
bloco 0. tempo: 5.81681895256042480469 	 avg= 5.81681895256042480469
bloco 1. tempo: 5.68663692474365234375 	 avg= 5.75172793865203857422
bloco 2. tempo: 5.89545702934265136719 	 avg= 5.79963763554890920915
bloco 3. tempo: 5.81967902183532714844 	 avg= 5.80464798212051391602
bloco 4. tempo: 5.88615489006042480469 	 avg= 5.82094936370849591611
bloco 5. tempo: 5.73336911201477050781 	 avg= 5.80635265509287545882
bloco 6. tempo: 5.84224104881286621094 	 avg= 5.81147956848144531250
bloco 7. tempo: 5.71471500396728515625 	 avg= 5.79938399791717529297
bloco 8. tempo: 5.85206794738769531250 	 avg= 5.80523777008056640625
bloco 9. tempo: 5.64535498619079589844 	 avg= 5.78924949169158953310
sequencial thread 0. tempo: 1.97798800468444824219 	 avg= 1.97798800468444824219
sequencial thread 1. tempo: 1.98022007942199707031 	 avg= 1.97910404205322265625
sequencial thread 2. tempo: 2.08857703208923339844 	 avg= 2.01559503873189305168
sequencial thread 3. tempo: 1.95125889778137207031 	 avg= 1.99951100349426269531
sequencial thread 4. tempo: 1.98005795478820800781 	 avg= 1.99562039375305166899
sequencial thread 5. tempo: 1.96867394447326660156 	 avg= 1.99112931887308763912
sequencial thread 6. tempo: 1.95239400863647460938 	 avg= 1.98559570312500000000
sequencial thread 7. tempo: 1.96841311454772949219 	 avg= 1.98344787955284118652
sequencial thread 8. tempo: 1.98397898674011230469 	 avg= 1.98350689146253800210
sequencial thread 9. tempo: 2.00685596466064453125 	 avg= 1.98584179878234867722
bloco thread 0. tempo: 2.82130002975463867188 	 avg= 2.82130002975463867188
bloco thread 1. tempo: 2.87486195564270019531 	 avg= 2.84808099269866943359
bloco thread 2. tempo: 2.83456707000732421875 	 avg= 2.84357635180155421395
bloco thread 3. tempo: 2.84349203109741210938 	 avg= 2.84355527162551879883
bloco thread 4. tempo: 2.83368396759033203125 	 avg= 2.84158101081848135649
bloco thread 5. tempo: 2.86688804626464843750 	 avg= 2.84579885005950927734
bloco thread 6. tempo: 2.83127093315124511719 	 avg= 2.84372343335832855615
bloco thread 7. tempo: 2.85855197906494140625 	 avg= 2.84557700157165527344
bloco thread 8. tempo: 2.82501792907714843750 	 avg= 2.84329266018337678545
bloco thread 9. tempo: 2.82446002960205078125 	 avg= 2.84140939712524431826

	COMPARAR MATRIZ_SeqC c/ MATRIZ_SeqBlC
	** Matrizes são iguais **

	COMPARAR MATRIZ_SeqC c/ MATRIZ_ThreadC
	** Matrizes são iguais **

	COMPARAR MATRIZ_SeqC c/ MATRIZ_ThreadBlC
	** Matrizes são diferentes **

	Tempo Médio tempo_MATRIZ_SeqC:		4.06127362251281720518
	Tempo Médio tempo_MATRIZ_SeqBlC:	5.78924949169158953310
	Tempo Médio MATRIZ_ThreadC:		1.98584179878234867722
	Tempo Médio MATRIZ_ThreadBlC:		2.84140939712524431826

	SPEEDUP (MATRIZ_C): 	2.04511 (204.51 %)
	SPEEDUP (MATRIZ_BLC): 	2.03746 (203.75 %)
