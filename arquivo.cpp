#include "arquivo.h"

FILE *abreArquivo(char *nomeArquivo, char *tipo) {
	return fopen(nomeArquivo,tipo);
}

int fechaArquivo(FILE *f) {
	return fclose(f);
}

char *leLinha(char *linha, FILE *f, int *fim){        
	
    char *linhaAux=NULL,c;
    int len=0; /*Len da string*/    
    while(((c = getc(f))!= '\n') && (c != EOF)) {/* Enquanto não chegar 
                                                    ao final do arquivo */
        len++;                              
        linha =  (char *) realloc(linha, (sizeof(char) * len) + 1);
        linha[len] = '\0';
        linha[len-1] = c;        
    }    
    
    if (c==EOF)
        *fim = 1;
    else
        *fim = 0;
    
    return linha;
    
}


int escreveLinha(FILE *f,char *linha) {
	
	if (fprintf(f,"%s\n",linha))
		return 1;
	else
		return 0;
}


