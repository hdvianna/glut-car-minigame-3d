/*Este header especifica o uso das funções para
leitura de arquivo e estruturas para armazenamento dos 
objetos do universo*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arquivo.h"

#ifndef ESTRUTURAS /*Caso o biblioteca não tenha sido compilada*/
    
    #define ESTRUTURAS 1
    
    
    typedef struct sObj {
        double pIniX ;
        double pIniY;
        double pIniZ;
        double pFimX;
        double pFimY;
        double pFimZ;
    } tObj;

    tObj carregaObjeto(char *strLinha, int *carregou);/*Carrega o objeto*/
    tObj *carregaObjetos(tObj *objetos, int *qtd); /*Retorna diferente a coleção de objetos*/

#endif


