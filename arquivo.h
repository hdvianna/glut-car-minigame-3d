
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef ARQUIVO /*Caso o biblioteca não tenha sido compilada*/
		
	#define ARQUIVO FILE

	ARQUIVO *abreArquivo(char *nomeArquivo, char *tipo);
    char *leLinha(char *linha, FILE *f, int *fim);
	int escreveLinha(ARQUIVO *f,char *linha);
	int fechaArquivo(ARQUIVO *f);

#endif


