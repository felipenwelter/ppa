#include <stdio.h>
#include <stdlib.h>


int pass_valor(int **par1){
    *(*par1) = 10;
    //*(*par2) = 10.10;
    return 0;
}

int main(){
    int *p_p1 = NULL;
    //float *p_p2 = NULL;

    int p1 = 5;
    //float p2 = 5.1;

    p_p1 = &(p1);
    
    printf(" p1 %d %p %p\n", p1, &p1, p_p1);
    pass_valor(&p_p1);
    printf(" p1 %d pp %p\n", p1, &p1, p_p1);
    return 0;
}


int teste1(){
    /*int i = 7;
    int *ptr_i = NULL;
    ptr_i = &i;
    i++;

    printf("o endereço %p tem o valor %d\ne está armazenado em %p\n",ptr_i,*ptr_i,&ptr_i);*/
    return 0;
}

int teste2(){
    /*char caractere;
    int inteiro;
    float Float;
    double Double;
    printf("Caractere: %d bytes \t em %p\n", sizeof(caractere), &caractere);
    printf("Inteiro: %d bytes \t em %p\n", sizeof(inteiro), &inteiro);
    printf("Float: %d bytes \t em %p\n", sizeof(Float), &Float);
    printf("Double: %d bytes \t em %p\n", sizeof(Double), &Double);*/
    return 0;
}

int teste3(){
    /*
    int *vet_i;
    vet_i = malloc(sizeof(int)*10);

    for (int fi = 0; fi < 10; fi++){
        vet_i[fi] = fi * 10;
        printf("(for) vet_i[%d] = %d\n", fi,vet_i[fi]);
    }

    //printf("tamanho de um int é %d\n",sizeof(vet_i));
    */
   return 0;
}

int teste4(){
    /*int valor[3] = {10,20,30};
    int *ptr_valor = NULL;

    ptr_valor = &valor[0];
    if(*(++ptr_valor) == valor[1])
        printf("Ok (1)\n");

    ptr_valor = &valor[0];
    printf("%d\n",*ptr_valor);
    if(*(ptr_valor++) == valor[1])
        printf("Ok (2)\n");*/

    return 0;
}