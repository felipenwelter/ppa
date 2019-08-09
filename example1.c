#include <stdio.h>
#include <stdlib.h>
// Formato de uma função em C;
// <tipo de retorno> <nome_da_função> (<parâmetro1,parâmetro2>)
int funcao (int par1, int par2) {
    int var_local; // válida somente dentro da função;
    var_local = par1 * (int) par2; // cast de float p/ inteiro
    return var_local; // retorno de um inteiro
}
// Formato de um procedimento em C;
// void <nome_da_função> (<parâmetro1,parâmetro2>)
void procedimento (int par1, int par2){
    int var_local; //válida somente dentro da função;
    var_local = par1 * (int) par2;
    printf ("(procedimento) var_local = %d\n", var_local);
}

// Função principal
// argc = número de elementos passados como parâmetro;
// argv =  um vetor com o conteúdo dos parâmetros;
int main(int argc, char **argv) {
    
    if (argc != 3) {
        printf("ERRO: Número de parâmetros deve ser 3.\n");
        return 1; // Indicativo de erro.
    }

    printf("(main) retorno função = %d\n",funcao (atoi(argv[1]),atof(argv[2])));
    procedimento (atoi(argv[1]),atof(argv[2]));

    return 0; // Retorno com sucesso.
}