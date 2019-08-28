Disciplina de Programação Paralela Avançada

## Objetivo:
- Implementar uma biblioteca de manipulação de matrizes de inteiro em C.

## Arquivos:

[BIBLIOTECAS IMPLEMENTADAS]
- **matrizv3.h**: headers das funções de gerência de matrizes;
- **matrizv3.c**: funções para manipular matrizes;
- **matriz-operacoesv3.h**: headers das funções de operações de matrizes que devem ser implementadas;
- **matriz-operacoesv3.c**: ainda não implementado;

[ARQUIVOS PARA EXECUÇÃO]
- **main.c**: código para teste simplificado da biblioteca de matrizes;
- **mainEx01.c**: exercício 01, que realiza a leitura de uma matriz de arquivo e exetuca as operações disponíveis na biblioteca de matrizes;
- **mainEx02.c**: exercício 02, ainda não implementado;

[ARQUIVOS AUXILIARES]
- **mat_a3x4.example** e **mat_b4x3.example**: matrizes exemplos A (3x4) e B(4x3);
- **toolsv3.(c/h)**: biblioteca de leitura/escrita de matrizes em arquivos;
- **gera_matrizv3.c**: fontes do programa de geração de matrizes em arquivo;
- **makefile**: para compilar o arquivo fonte (ver detalhes sobre como gerar os arquivos mais abaixo);

## Compilação:

Para gerar os arquivos para execução é necessário executar o comando abaixo:

Para mainEx01.c:
> `make mainEx01`

Para main.c
> `gcc -Wall -O3 -c matrizv3.c`
> `gcc -Wall -O3 matrizv3.o toolsv3.o main.c -o main`

## Execução:

Para executar os arquivos gerados basta executar o comando abaixo (desde que esteja no mesmo diretório):

Para mainEx01.c:
> `./mainEx01 mat_a3x4.example mat_b4x3.example`

Para main.c:
> `./main`

## Análise dinâmica:

Para realizar uma análise dinâmica do código e verificar eventuais problemas, deve-se previamente ter instalado o programa *valgrind* e executar o comando abaixo:

Para análise simplificada:
> `valgrind ./main`

Para análise detalhada:
> `valgrind --leak-check=full ./main`

**Substituir `main` pelo nome do programa + parâmetros.

## Descrição das funções: