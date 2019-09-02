#include "matrizv3.h"
#include "toolsv3.h"

mymatriz res; //auxiliar, grava resultado da soma

mymatriz *msomar (mymatriz *mat_a, mymatriz *mat_b, int tipo){
    

    
	res.matriz = NULL;
	res.lin = mat_a->lin;
	res.col = mat_a->col;

    if (malocar(&res)) {
		printf ("ERROR: Out of memory\n");
	}
    mzerar(&res);
    mimprimir(&res);

    printf(" ** called msomar\n");
    
    printf("1 - %p \n", mat_a);
    printf("2 - %p \n", mat_b);

    printf("**\n");



    for (int i = 0; i < mat_a->lin; i++){
        for (int j = 0; j < mat_a->col; j++){
            printf("%d ", mat_a->matriz[i][j] );
            //res[i][j] = mat_a[i][j] + mat_b[i][j];        

        }
    }
    printf("\n");


    mimprimir(&res);

    printf("\n");

    return &res;
}

mymatriz *mmultiplicar (mymatriz *mat_a, mymatriz *mat_b, int tipo){
    printf(" ** called mmultiplicar\n");
    return NULL;
}