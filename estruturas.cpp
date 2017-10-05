#include "estruturas.h"

char OBJ_ARQ[25] = "objetos.txt";


/*Carrega o objeto na estrutura definida*/
tObj carregaObjeto (char *strLinha, int *carregou) {

    tObj objeto;
    float xIni,xFim, yIni, yFim, zIni, zFim;
    if (strLinha[0]!='#') {
        sscanf(strLinha, "%f;%f;%f;%f;%f;%f", &xIni, 
            &yIni, &zIni, &xFim, &yFim,
            &zFim);

        objeto.pIniX = xIni;
        objeto.pFimX = xFim;
        objeto.pIniY = yIni;
        objeto.pFimY = yFim;
        objeto.pIniZ = zIni;
        objeto.pFimZ = zFim;
        *carregou = 1;
    } else
        *carregou = 0;    
    
    return objeto;
    
}

/*Carrega os objetos do arquivo texto para a estrutura definida*/
tObj *carregaObjetos(tObj *objetos, int *qtd) {
    
    tObj objeto;
    int fim, carregou;
    char *strLinha=(char *) malloc(sizeof(char));/*Uma nova string*/    
    ARQUIVO *arq = abreArquivo(OBJ_ARQ, "r");
    
    *qtd = 0;    
    /*Processa as linhas do arquivo*/
    strLinha = leLinha(strLinha, arq, &fim);
    objeto = carregaObjeto(strLinha, &carregou);/*Processa a linha*/
    if (carregou) {
        (*qtd)++;
        objetos =  (tObj *) realloc(objetos, (sizeof(tObj)) * (*qtd));
        objetos[(*qtd)-1] = objeto;
    }
    while (!fim) {        
        strLinha = (char *) malloc(sizeof(char));
        strLinha = leLinha(strLinha, arq, &fim);
        objeto = carregaObjeto(strLinha, &carregou);
        if (carregou) {
            (*qtd)++;
            objetos =  (tObj *) realloc(objetos, (sizeof(tObj)) * (*qtd));
            objetos[(*qtd)-1] = objeto;
        }
    }
    
    return objetos;
}
