#include "automato.h"

struct automatocelular
{
    //variaveis para fazer a troca entre as geraÃ§oes do reticulado
    int estadoatual;
    int estadofuturo;

};

//funçao para alocar uma matriz
AutomatoCelular **alocarReticulado(int ordem) {
    AutomatoCelular **mat = malloc(ordem * sizeof(AutomatoCelular*));
	
    for (int i=0;i<ordem;i++)
    {
        mat[i] = malloc(ordem * sizeof(AutomatoCelular*));
    }
    
    zeramatriz(mat, ordem);
    
    return mat;
}
//funçao extra
void zeramatriz(AutomatoCelular **M,int size){
    for(int i = 0;i<size;i++){
		for(int j = 0;j<size;j++){
			M[i][j].estadofuturo = 0;
			M[i][j].estadoatual = 0;
		}
	}
}
//funçao para desalocar uma matriz
void desalocaReticulado(AutomatoCelular ***M, int ordem) {
	for(int i = 0; i < ordem; i++){
		free((*M)[i]);
	}
	free(*M);
}

//funçao de leitura de arquivo(retorna um ponteiro para uma matriz)
AutomatoCelular **Reticuladoarq(FILE *arq,int size){
    if(arq == NULL){
		printf("arquivo inexistente\n");
		return 0;
	}else{
        
        AutomatoCelular **reticulado = malloc(size * sizeof(AutomatoCelular*));

        for (int i=0;i<size;i++)
        {
            reticulado[i] = malloc(size * sizeof(AutomatoCelular*));
        
        }
        for(int i = 0;i<size;i++){
		    for(int j = 0;j<size;j++){
			    fscanf(arq,"%d",&reticulado[i][j].estadoatual);
		    }
        }
        return reticulado;
	}
}

//funçao para o usuario preencher uma matriz    
void LeituraReticulado(AutomatoCelular **M, int ordem) {
	for(int i = 0;i<ordem;i++){
		for(int j = 0;j<ordem;j++){
			scanf("%d",&M[i][j].estadoatual);
		}
	}
}

//funçao para exibir a matriz
void imprimeReticulado(AutomatoCelular **M,int size){
    for(int i = 0;i<size;i++){
		for(int j = 0;j<size;j++){
			printf("%d ",M[i][j].estadoatual);
		}
        printf("\n");
	}
}
//funçao que com base em uma posiçao de uma matriz, retorna a quantidade de casas ao redor possuem o valor 1 em relaçao a posiçao dada
int verifica(AutomatoCelular**M,int size,int row,int col){
    int count = 0;
    for(int i = row-1 ; i<=row+1 ; i++){
        for(int j = col-1 ; j<=col+1 ; j++){
            if((i == row && j == col) || (i<0||j<0) || (i>=size || j>=size)){
                continue;
            }
            else if(M[i][j].estadoatual==1){
                count++;
            }
        }
    }
    return count;
}
//funçao responsavel por atualizar um reticulado(matriz) em sua proxima geraçao
void evoluirReticulado(AutomatoCelular **M,int size){
    int aux;
    for(int i = 0; i<size;i++){
        for(int j = 0; j<size;j++){
            aux = verifica(M,size,i,j);
            //condicional de vida de uma celula
            if( (M[i][j].estadoatual == 1) && (aux == 2||aux == 3) ){
                M[i][j].estadofuturo = 1;
            }
            //condicional de morte de uma celula
            else if( (M[i][j].estadoatual == 1) && (aux > 3||aux<2)){
                M[i][j].estadofuturo = 0;
            }
            //condicional de ressurreiçao de uma celula
            else if((M[i][j].estadoatual == 0) && (aux == 3)){
                M[i][j].estadofuturo = 1;
            }
        }
        
    }

    //loop para atualizar as geraçoes
    for(int i = 0; i<size;i++){
        for(int j = 0; j<size;j++){
            M[i][j].estadoatual = M[i][j].estadofuturo;
        }
        
    }
    
}
