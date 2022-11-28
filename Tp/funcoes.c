#include "funcoes.h"
/////Lucas Chagas Moreira
/////Sala 32
/////matricula 22.1.4109
#define TAM 20
//#################### FUNCOES AUXILIARES ##########################
// funçao para limpar o tabuleiro
void limpamatriz(char ***matriz){
	for(int i = 0; i<3;i++){
		for(int j = 0;j<3;j++){
			(*matriz)[i][j] = ' ';
		}
	}
}

//visualizador do tabuleiro.
void imprimetabuleiro(char**matriz){
	printf("  | 1 | 2 | 3 |\n");
	for(int j = 0;j<3;j++){
		printf("|%d|",j+1);
		for(int i = 0;i<3;i++){
			printf(" %c |",matriz[j][i]);
		}
		printf("\n");
	}
}
void liberamatriz(char ***matriz){
	for(int i = 0; i<3;i++){
		free((*matriz)[i]);
	}
	free(*matriz);
	return;
}
int verificavitoria(char **matriz){
	int cont = 0;
	int aux;
	//verificando vitorias horizontais e verticais
	for(int i = 0;i<3;i++){
		aux = matriz[i][0];
		for(int j = 0;j<3;j++){
			if(matriz[i][j] == aux && aux != ' '){
				cont++;
			}
		}
		if(cont == 3){
			return 1;
		}
		cont = 0;
		aux = matriz[0][i];
		for(int j = 0;j<3;j++){
			if(matriz[j][i] == aux && aux != ' '){
				cont++;
			}			
		}
		if(cont == 3){
			return 1;
		}
		cont = 0;
	}
	//verificando vitorias diagonais
	aux = matriz[2][0];
	for(int j = 0;j<3;j++){
		if(matriz[2-j][j] == aux && aux != ' '){
			cont++;
		}
	}
	if(cont == 3){
		return 1;
	}
	cont = 0;
	aux = matriz[0][0];
	for(int j = 0;j<3;j++){
		if(matriz[j][j] == aux && aux != ' '){
			cont++;
		}			
	}
	if(cont == 3){
		return 1;
	}
		cont = 0;
	
	
	return 0;
}
int comandos(char *comando){
	char palavra[6] = "marcar";
	char palavra2[6] = "salvar";
	int cont = 0;
	int cont2 = 0;
	for(int i=0;i<5;i++){
		if(comando[i] == palavra[i]){
			cont++;
		}
	}
	for(int i=0; i < 5;i++){
		if(comando[i] == palavra2[i]){
			cont2++;
		}
	}
	if(cont == 5){
		return 1;	
	}else if(cont2 == 5){
		return 2;
	}
	else{
		printf("comando invalido\n");	
		return 0;	
	}
}
void marcar(char ***matriz,char *comando,int *jogador,int *valida){
	char x[3];
		int inteiro;
		x[0]=comando[7];
		x[1]=comando[8];
		x[2]='\0';
		inteiro = atoi(x);
		if( ((inteiro/10)) < 1 || ((inteiro/10)) > 3 || ((inteiro%10)) < 1 || ((inteiro%10)) > 3){
			printf("valor invalido\n");
			return;
		} 
		if((*matriz)[(inteiro/10)-1][(inteiro%10)-1] != ' ' || ((inteiro%10)-1)>2 || ((inteiro/10)-1)>2){
			printf("jogada ja feita ou cordenada inexistente\n");
			return;
		}
		if(*jogador == 1){
			(*matriz)[(inteiro/10)-1][(inteiro%10)-1] = 'X';
			*valida = 0;
		}else{
			(*matriz)[(inteiro/10)-1][(inteiro%10)-1] = 'O';
			*valida = 0;
		}
		system("clear");
		imprimetabuleiro(*matriz);
}



//XXXXXXXXXXXXXXXXXXXXXXXXXX FUNCOES DE ARQUIVO XXXXXXXXXXXXXXXXXXXXXXXXX
void salvarjogo(char *nome1, char *nome2, char **tabuleiro,int qtdjogadores,char *comando,int jogada){
	char nomearq[30];
	int cont=0;
	for(int i = 7;comando[i] != '\0';i++){
		nomearq[i-7] = comando[i];
		cont++;
	}
	nomearq[cont] = '\0';
	FILE *arq = fopen(nomearq,"w");
	
	fprintf(arq,"%d\n",qtdjogadores);
	if(qtdjogadores == 2){
		fprintf(arq,"%s\n%s\n",nome1,nome2);
	}else{
		fprintf(arq,"%s\n",nome1);
	}
	for(int i = 0;i<3;i++){
		for(int j = 0;j<3;j++){
			if(tabuleiro[i][j] == ' '){
				fprintf(arq,"- ");
			}else{
				fprintf(arq,"%c ",tabuleiro[i][j]);
			}
		}
		fprintf(arq,"\n");
	}
	fprintf(arq,"%d",jogada);
	fclose(arq);
	printf("Jogo salvo!!!!!!\n");
	return;
}
void velhaini(jogadores *saves, int ini){
	FILE *arq = fopen("velha.ini","w");
	
	if(ini >= 10){
		ini = 10;	
	}
	fprintf(arq,"%d\n",ini);
	for(int i = 0; i<(ini); i++){
		fprintf(arq,"%s\n",saves[i].nome);
		fprintf(arq,"%d ",saves[i].vitoria);
		fprintf(arq,"%d ",saves[i].empate);
		fprintf(arq,"%d\n",saves[i].derrota);
	}
	fclose(arq);
	return;
}
void marcavitoria(jogadores *saves, char* nome,int *ini){
	strcpy(saves[(*ini)].nome,nome);
	saves[(*ini)].vitoria = saves[(*ini)].vitoria + 1;
	*ini += 1;
	return;
}
void marcaderrota(jogadores *saves, char* nome,int *ini){
	strcpy(saves[(*ini)].nome,nome);
	saves[(*ini)].derrota = saves[(*ini)].derrota + 1;
	*ini += 1;
	return;
}
void marcaempate(jogadores *saves, char* nome,int *ini){
	strcpy(saves[(*ini)].nome,nome);
	saves[(*ini)].empate = saves[(*ini)].empate + 1;
	*ini += 1;
	return;
}
int verificacopia(jogadores *saves,char *nome,int ini){
	for(int i = 0;i<ini;i++){
		if(strcmp(saves[i].nome,nome)==0){
			return i;
		}
	}
	return -1;
}
void ordena(jogadores *saves,int ini){
	int auxint;
	char auxchar[30];
	for(int i = 0; i<ini;i++){
		for(int j = 0;j<ini;j++){
			if(saves[i].vitoria > saves[j].vitoria){
				auxint = saves[j].vitoria;
				saves[j].vitoria = saves[i].vitoria;
				saves[i].vitoria = auxint;
				
				auxint = saves[j].derrota;
				saves[j].derrota = saves[i].derrota;
				saves[i].derrota = auxint;
				
				auxint = saves[j].empate;
				saves[j].empate = saves[i].empate;
				saves[i].empate = auxint;
				
				strcpy(auxchar,saves[j].nome);
				strcpy(saves[j].nome,saves[i].nome);
				strcpy(saves[i].nome,auxchar);
			}else if(saves[i].vitoria == saves[j].vitoria){
				if(saves[i].empate > saves[j].empate){
					auxint = saves[j].vitoria;
					saves[j].vitoria = saves[i].vitoria;
					saves[i].vitoria = auxint;
					
					auxint = saves[j].derrota;
					saves[j].derrota = saves[i].derrota;
					saves[i].derrota = auxint;
					
					auxint = saves[j].empate;
					saves[j].empate = saves[i].empate;
					saves[i].empate = auxint;
					
					strcpy(auxchar,saves[j].nome);
					strcpy(saves[j].nome,saves[i].nome);
					strcpy(saves[i].nome,auxchar);
				}
			}
		}
	}
	if(ini >= 10){
		int cont = 0;
		for(int i = 0;i<10;i++){
			if(strcmp(saves[i].nome,"computador") == 0){
				cont = 1;
			}
		}
		if(cont == 0){
			for(int i = 0;i<ini;i++){
				if(strcmp(saves[ini].nome,"computador") == 0){
					auxint = saves[9].vitoria;
					saves[9].vitoria = saves[i].vitoria;
					saves[i].vitoria = auxint;
						
					auxint = saves[9].derrota;
					saves[9].derrota = saves[i].derrota;
					saves[i].derrota = auxint;
						
					auxint = saves[9].empate;
					saves[9].empate = saves[i].empate;
					saves[i].empate = auxint;
						
					strcpy(auxchar,saves[9].nome);
					strcpy(saves[9].nome,saves[i].nome);
					strcpy(saves[i].nome,auxchar);
					return;
				}
			}
			saves[9].vitoria = 0;
			saves[9].derrota = 0;
			saves[9].empate = 0;
			strcpy(saves[9].nome,"computador");
		}
	}
	return;
}
//OOOOOOOOOOOOOOOOOOOOOOOOOO FUNCOES PRINCIPAIS OOOOOOOOOOOOOOOOOOOOOOOOOOOOO
//jogo pvp
void pvp(char *nome1,char *nome2,int *ini,jogadores *saves){
	char comando[30];
	int jogador=1;
	char **tabuleiro;
	int valida;
	int contjogada = 0;
	//alocando tabuleiro
	tabuleiro = malloc(3*sizeof(int*));
	for(int i = 0;i< 3;i++){
		tabuleiro[i]=malloc(3*sizeof(int));
	}
	limpamatriz(&tabuleiro);
	
	//inicio do jogo
	system("clear");
	imprimetabuleiro(tabuleiro);
	while(1){
		
		if(jogador == 1){
			valida = 1;
			while(valida == 1){
				
				printf("%s, digite o comando: ",nome1);
				scanf(" %[^\n]",comando);
				if((strcmp(comando,"voltar"))==0){
					salvarjogo(nome1,nome2,tabuleiro,2,"salvar temp.txt",jogador);
					liberamatriz(&tabuleiro);
					return;
				}
				if(comandos(comando)==1){
					marcar(&tabuleiro,comando,&jogador,&valida);
				}else if(comandos(comando) == 2){
					salvarjogo(nome1,nome2,tabuleiro,2,comando,jogador);
				}
			}
			
			
			
			//verificaçao de vitoria do player 1 
			if(contjogada >= 2 && verificavitoria(tabuleiro)==1){
				printf("Vitoria do jogador %s\n",nome1);
				printf("digite qualquer coisa para voltar\n");
				liberamatriz(&tabuleiro);
				//algoritimo que ira salvar os participantes em uma struct 
				if((verificacopia(saves,nome1,*ini))==-1){
					if(*ini < TAM){
						marcavitoria(saves,nome1,ini);
					}
				}else{
					saves[verificacopia(saves,nome1,*ini)].vitoria = saves[verificacopia(saves,nome1,*ini)].vitoria + 1;
				}
				if((verificacopia(saves,nome2,*ini))==-1){
					if(*ini < TAM){
						marcaderrota(saves,nome2,ini);
					}
				}else{
					saves[verificacopia(saves,nome2,*ini)].derrota = saves[verificacopia(saves,nome2,*ini)].vitoria + 1;
				}
				//////////////////////////////////////////////////////////
				scanf("%s",comando);
				return;
			}
			contjogada++;
			jogador =2;
		}
		jogador = 2;
		if(contjogada >= 9){
			printf("Dama!!!\n");
			printf("digite qualquer coisa para voltar\n");
			//algoritimo que ira salvar os participantes em uma struct
			if((verificacopia(saves,nome1,*ini))==-1){
				if(*ini < TAM){
					marcaempate(saves,nome1,ini);
				}
				
			}else{
				saves[verificacopia(saves,nome1,*ini)].empate = saves[verificacopia(saves,nome1,*ini)].empate + 1;
			}
			if((verificacopia(saves,nome2,*ini))==-1){
				if(*ini < TAM){
					marcaempate(saves,nome2,ini);
				}
			}else{
				saves[verificacopia(saves,nome2,*ini)].empate = saves[verificacopia(saves,nome2,*ini)].empate + 1;
			}
			///////////////////////////////////////////////////////////
			scanf("%s",comando);
			liberamatriz(&tabuleiro);
			return;
		}
		if(jogador == 2){
			valida = 1;
			while(valida ==	 1){
				
				printf("%s, digite o comando: ",nome2);
				scanf(" %[^\n]",comando);
				if((strcmp(comando,"voltar"))==0){
					salvarjogo(nome1,nome2,tabuleiro,2,"salvar temp.txt",jogador);
					liberamatriz(&tabuleiro);
					return;
				}
				if(comandos(comando)==1){
					marcar(&tabuleiro,comando,&jogador,&valida);
				}else if(comandos(comando) == 2){
					salvarjogo(nome1,nome2,tabuleiro,2,comando,jogador);
				}
				
			}
			//verificaçao de vitoria do player 2
			if(contjogada >= 2 && verificavitoria(tabuleiro)==1){
				printf("Vitoria do jogador: %s\n",nome2);
				printf("digite qualquer coisa para voltar\n");
				//algoritimo que ira salvar os participantes em uma struct 
				if((verificacopia(saves,nome2,*ini))==-1){
					if(*ini < TAM){
						marcavitoria(saves,nome2,ini);
					}
				}else{
					saves[verificacopia(saves,nome2,*ini)].vitoria = saves[verificacopia(saves,nome2,*ini)].vitoria + 1;
				}
				if((verificacopia(saves,nome1,*ini))==-1){
					if(*ini < TAM){
						marcaderrota(saves,nome1,ini);
					}
				}else{
					saves[verificacopia(saves,nome1,*ini)].derrota = saves[verificacopia(saves,nome1,*ini)].derrota + 1;
				}
				//////////////////////////////////////////////////////////
				scanf("%s",comando);
				return;
			}
			contjogada++;
			jogador = 1;
		}
		if(contjogada >= 9){
			printf("Dama!!!\n");
			printf("digite qualquer coisa para voltar\n");
			//algoritimo que ira salvar os participantes em uma struct
			if((verificacopia(saves,nome1,*ini))==-1){
				if(*ini < TAM){
					marcaempate(saves,nome1,ini);
				}
				
			}else{
				saves[verificacopia(saves,nome1,*ini)].empate = saves[verificacopia(saves,nome1,*ini)].empate + 1;
			}
			if((verificacopia(saves,nome2,*ini))==-1){
				if(*ini < TAM){
					marcaempate(saves,nome2,ini);
				}
			}else{
				saves[verificacopia(saves,nome2,*ini)].empate = saves[verificacopia(saves,nome2,*ini)].empate + 1;
			}
			/////////////////////////////////////////////////////////
			scanf("%s",comando);
			liberamatriz(&tabuleiro);
			return;
		}
		
	}
	//liberando a matriz
	liberamatriz(&tabuleiro);
	return;
}
void pve(char *nome1,int *ini,jogadores *saves){
	char comando[30];
	char **tabuleiro;
	int valida;
	int jogador = 1;
	int contjogada = 0;
	//alocando tabuleiro
	tabuleiro = malloc(3*sizeof(int*));
	for(int i = 0;i< 3;i++){
		tabuleiro[i]=malloc(3*sizeof(int));
	}
	limpamatriz(&tabuleiro);
	
	//inicio do jogo
	system("clear");
	imprimetabuleiro(tabuleiro);
	while(1){
		valida = 1;
		while(valida == 1){
				
			printf("%s, digite o comando: ",nome1);
			scanf(" %[^\n]",comando);
			if((strcmp(comando,"voltar"))==0){
				salvarjogo(nome1," ",tabuleiro,1,"salvar temp.txt",jogador);
				liberamatriz(&tabuleiro);
				return;
			}
			if(comandos(comando)==1){
				marcar(&tabuleiro,comando,&jogador,&valida);
			}else if(comandos(comando) == 2){
				salvarjogo(nome1," ",tabuleiro,1,comando,jogador);
			}

		}
			
			
		//verificaçao de vitoria do player 1 
		if(contjogada >= 2 && verificavitoria(tabuleiro)==1){
			printf("Vitoria do jogador %s\n",nome1);
			printf("digite qualquer coisa para voltar\n");
			//algoritimo que ira salvar os participantes em uma struct
			if((verificacopia(saves,nome1,*ini))==-1){
				if(*ini < TAM){
					marcavitoria(saves,nome1,ini);
				}
			}else{
				saves[verificacopia(saves,nome1,*ini)].vitoria = saves[verificacopia(saves,nome1,*ini)].vitoria + 1;
			}
			if((verificacopia(saves,"computador",*ini))==-1){
				if(*ini < TAM){
					marcaderrota(saves,"computador",ini);
				}
			}else{
				saves[verificacopia(saves,"computador",*ini)].derrota = saves[verificacopia(saves,"computador",*ini)].derrota + 1;
			}
			//////////////////////////////////////////////////////////
			liberamatriz(&tabuleiro);
			scanf("%s",comando);
			return;
		}
		contjogada++;
		
		bot(&tabuleiro,contjogada);
		printf("jogada do bot\n");
		imprimetabuleiro(tabuleiro);
		if(contjogada >= 2 && verificavitoria(tabuleiro)==1){
			printf("Vitoria do computador\n");
			printf("digite qualquer coisa para voltar\n");
			//algoritimo que ira salvar os participantes em uma struct
			if((verificacopia(saves,nome1,*ini))==-1){
				if(*ini < TAM){
					marcaderrota(saves,nome1,ini);
				}
			}else{
				saves[verificacopia(saves,nome1,*ini)].derrota = saves[verificacopia(saves,nome1,*ini)].derrota + 1;
			}
			if((verificacopia(saves,"computador",*ini))==-1){
				if(*ini < TAM){
					marcavitoria(saves,"computador",ini);
				}
			}else{
				saves[verificacopia(saves,"computador",*ini)].vitoria = saves[verificacopia(saves,"computador",*ini)].vitoria + 1;
			}
			///////////////////////////////////////////////////////////
			liberamatriz(&tabuleiro);
			scanf("%s",comando);
			return;
		}
		contjogada++;
		if(contjogada >= 9){
			printf("Dama!!!\n");
			printf("digite qualquer coisa para voltar\n");
			//algoritimo que ira salvar os participantes em uma struct
			if((verificacopia(saves,nome1,*ini))==-1){
				if(*ini < TAM){
					marcaempate(saves,nome1,ini);
				}
			}else{
				saves[verificacopia(saves,nome1,*ini)].empate = saves[verificacopia(saves,nome1,*ini)].empate + 1;
			}
			if((verificacopia(saves,"computador",*ini))==-1){
				if(*ini < TAM){
					marcaempate(saves,"computador",ini);
				}
			}else{
				saves[verificacopia(saves,"computador",*ini)].empate = saves[verificacopia(saves,"computador",*ini)].empate + 1;
			}
			//////////////////////////////////////////////////////////
			scanf("%s",comando);
			liberamatriz(&tabuleiro);
			return;
		}
	}
	
	//liberando a matriz
	liberamatriz(&tabuleiro);
	return;
}
void carregajogo(char *temp,int *ini,jogadores *saves){
	FILE *arq = fopen(temp,"r");
	if(arq == NULL){
		printf("arquivo inexistente\n");
		return;
	}
	char nome1[20];
	char nome2[20];
	int qtd;
	char **tabuleiro;
	int jogador;
	char comando[30];
	int contjogada = 0;
	int valida = 1;
	
	tabuleiro = malloc(3*sizeof(int*));
	for(int i = 0;i< 3;i++){
		tabuleiro[i]=malloc(3*sizeof(int));
	}
	limpamatriz(&tabuleiro);
	
	fscanf(arq,"%d",&qtd);
	if(qtd == 1){
		fscanf(arq,"%s",nome1);
	}else if(qtd == 2){
		fscanf(arq,"%s",nome1);
		fscanf(arq,"%s",nome2);
	}
	for(int i = 0;i<3;i++){
		for(int j = 0;j<3;j++){
			fscanf(arq," %c",&tabuleiro[i][j]);
		}
	}
	for(int i = 0;i<3;i++){
		for(int j = 0;j<3;j++){
			if(tabuleiro[i][j] == '-'){
				tabuleiro[i][j] = ' ';
			}else{
				contjogada++;
			}
		}
	}
	fscanf(arq,"%d",&jogador);
	if(qtd == 2){
		system("clear");
		imprimetabuleiro(tabuleiro);
		while(1){

			if(jogador == 1){
				valida = 1;
				while(valida == 1){
					printf("%s, digite o comando: ",nome1);
					scanf(" %[^\n]",comando);
					if((strcmp(comando,"voltar"))==0){
						salvarjogo(nome1,nome2,tabuleiro,2,"salvar temp.txt",jogador);
						liberamatriz(&tabuleiro);
						return;
					}
					if(comandos(comando)==1){
						marcar(&tabuleiro,comando,&jogador,&valida);
					}else if(comandos(comando) == 2){
						salvarjogo(nome1,nome2,tabuleiro,2,comando,jogador);
					}
				}
				
				
				
				//verificaçao de vitoria do player 1 
				if(contjogada >= 2 && verificavitoria(tabuleiro)==1){
					printf("Vitoria do jogador %s\n",nome1);
					printf("digite qualquer coisa para voltar\n");
					//algoritimo que ira salvar os participantes em uma struct 
					if((verificacopia(saves,nome1,*ini))==-1){
						if(*ini < TAM){
							marcavitoria(saves,nome1,ini);
						}
					}else{
						saves[verificacopia(saves,nome1,*ini)].vitoria = saves[verificacopia(saves,nome1,*ini)].vitoria + 1;
					}
					if((verificacopia(saves,nome2,*ini))==-1){
						if(*ini < TAM){
							marcaderrota(saves,nome2,ini);
						}
					}else{
						saves[verificacopia(saves,nome2,*ini)].derrota = saves[verificacopia(saves,nome2,*ini)].vitoria + 1;
					}
					///////////////////////////////////////////////////////////
					liberamatriz(&tabuleiro);
					scanf("%s",comando);
					return;
				}
				contjogada++;
				jogador =2;
			}
			jogador = 2;
			if(contjogada >= 9){
				printf("Dama!!!\n");
				printf("digite qualquer coisa para voltar\n");
				//algoritimo que ira salvar os participantes em uma struct 
				if((verificacopia(saves,nome1,*ini))==-1){
					if(*ini < TAM){
						marcaempate(saves,nome1,ini);
					}
				}else{
					saves[verificacopia(saves,nome1,*ini)].empate = saves[verificacopia(saves,nome1,*ini)].empate + 1;
				}
				if((verificacopia(saves,nome2,*ini))==-1){
					if(*ini < TAM){
						marcaempate(saves,nome2,ini);
					}
				}else{
					saves[verificacopia(saves,nome2,*ini)].empate = saves[verificacopia(saves,nome2,*ini)].empate + 1;
				}
				///////////////////////////////////////////////////////////
				scanf("%s",comando);
				liberamatriz(&tabuleiro);
				return;
			}
			if(jogador == 2){
				valida = 1;
				while(valida ==	 1){
					
					printf("%s, digite o comando: ",nome2);
					scanf(" %[^\n]",comando);
					if((strcmp(comando,"voltar"))==0){
						salvarjogo(nome1,nome2,tabuleiro,2,"salvar temp.txt",jogador);
						liberamatriz(&tabuleiro);
						return;
					}
					if(comandos(comando)==1){
						marcar(&tabuleiro,comando,&jogador,&valida);
					}else if(comandos(comando) == 2){
						salvarjogo(nome1,nome2,tabuleiro,2,comando,jogador);
					}
					
				}
				//verificaçao de vitoria do player 2
				if(contjogada >= 2 && verificavitoria(tabuleiro)==1){
					printf("Vitoria do jogador: %s\n",nome2);
					printf("digite qualquer coisa para voltar\n");
					//algoritimo que ira salvar os participantes em uma struct 
					if((verificacopia(saves,nome2,*ini))==-1){
						if(*ini < TAM){
							marcavitoria(saves,nome2,ini);
						}
					}else{
						saves[verificacopia(saves,nome2,*ini)].vitoria = saves[verificacopia(saves,nome2,*ini)].vitoria + 1;
					}
					if((verificacopia(saves,nome1,*ini))==-1){
						if(*ini < TAM){
							marcaderrota(saves,nome1,ini);
						}
					}else{
						saves[verificacopia(saves,nome1,*ini)].derrota = saves[verificacopia(saves,nome1,*ini)].derrota + 1;
					}
					//////////////////////////////////////////////////////////
					liberamatriz(&tabuleiro);
					scanf("%s",comando);
					return;
				}
				contjogada++;
				
			}
			if(contjogada >= 9){
				printf("Dama!!!\n");
				printf("digite qualquer coisa para voltar\n");
				//algoritimo que ira salvar os participantes em uma struct 
				if((verificacopia(saves,nome1,*ini))==-1){
					if(*ini < TAM){
						marcaempate(saves,nome1,ini);
					}
					
				}else{
					saves[verificacopia(saves,nome1,*ini)].empate = saves[verificacopia(saves,nome1,*ini)].empate + 1;
				}
				if((verificacopia(saves,nome2,*ini))==-1){
					if(*ini < TAM){
						marcaempate(saves,nome2,ini);
					}
				}else{
					saves[verificacopia(saves,nome2,*ini)].empate = saves[verificacopia(saves,nome2,*ini)].empate + 1;
				}
				//////////////////////////////////////////////////////////
				scanf("%s",comando);
				liberamatriz(&tabuleiro);
				return;
			}
			jogador = 1;
		}
		//liberando a matriz
		liberamatriz(&tabuleiro);
		return;
	}else{
		system("clear");
		imprimetabuleiro(tabuleiro);
		while(1){
			valida = 1;
			while(valida == 1){
					
				printf("%s, digite o comando: ",nome1);
				scanf(" %[^\n]",comando);
				if((strcmp(comando,"voltar"))==0){
					salvarjogo(nome1," ",tabuleiro,1,"salvar temp.txt",jogador);
					liberamatriz(&tabuleiro);
					return;
				}
				if(comandos(comando)==1){
					marcar(&tabuleiro,comando,&jogador,&valida);
				}else if(comandos(comando) == 2){
					salvarjogo(nome1," ",tabuleiro,1,comando,jogador);
				}

			}
				
				
			//verificaçao de vitoria do player 1 
			if(contjogada >= 2 && verificavitoria(tabuleiro)==1){
				printf("Vitoria do jogador %s\n",nome1);
				printf("digite qualquer coisa para voltar\n");
				//algoritimo que ira salvar os participantes em uma struct
				if((verificacopia(saves,nome1,*ini))==-1){
					if(*ini < TAM){
						marcavitoria(saves,nome1,ini);
					}
				}else{
					saves[verificacopia(saves,nome1,*ini)].vitoria = saves[verificacopia(saves,nome1,*ini)].vitoria + 1;
				}
				if((verificacopia(saves,"computador",*ini))==-1){
					if(*ini < TAM){
						marcaderrota(saves,"computador",ini);
					}
				}else{
					saves[verificacopia(saves,"computador",*ini)].derrota = saves[verificacopia(saves,"computador",*ini)].derrota + 1;
				}
				//////////////////////////////////////////////////////////
				liberamatriz(&tabuleiro);
				scanf("%s",comando);
				return;
			}
			contjogada++;
			
			bot(&tabuleiro,contjogada);
			printf("jogada do bot\n");
			imprimetabuleiro(tabuleiro);
			//verificando vitoria do bot
			if(contjogada >= 2 && verificavitoria(tabuleiro)==1){
				printf("Vitoria do computador\n");
				printf("digite qualquer coisa para voltar\n");
				//algoritimo que ira salvar os participantes em uma struct
				if((verificacopia(saves,nome1,*ini))==-1){
					if(*ini < TAM){
						marcaderrota(saves,nome1,ini);
					}
				}else{
					saves[verificacopia(saves,nome1,*ini)].derrota = saves[verificacopia(saves,nome1,*ini)].derrota + 1;
				}
				if((verificacopia(saves,"computador",*ini))==-1){
					if(*ini < TAM){
						marcavitoria(saves,"computador",ini);
					}
				}else{
					saves[verificacopia(saves,"computador",*ini)].vitoria = saves[verificacopia(saves,"computador",*ini)].vitoria + 1;
				}
				//////////////////////////////////////////////////////////
				liberamatriz(&tabuleiro);
				scanf("%s",comando);
				return;
			}
			contjogada++;
			//verificando possibilidade de empate
			if(contjogada >= 9){
				printf("Dama!!!\n");
				printf("digite qualquer coisa para voltar\n");
				//algoritimo que ira salvar os participantes em uma struct
				if((verificacopia(saves,nome1,*ini))==-1){
					if(*ini < TAM){
						marcaempate(saves,nome1,ini);
					}
				}else{
					saves[verificacopia(saves,nome1,*ini)].empate = saves[verificacopia(saves,nome1,*ini)].empate + 1;
				}
				if((verificacopia(saves,"computador",*ini))==-1){
					if(*ini < TAM){
						marcaempate(saves,"computador",ini);
					}
				}else{
					saves[verificacopia(saves,"computador",*ini)].empate = saves[verificacopia(saves,"computador",*ini)].empate + 1;
				}
				//////////////////////////////////////////////////////////
				scanf("%s",comando);
				liberamatriz(&tabuleiro);
				return;
			}
		}
	
	//liberando a matriz
	liberamatriz(&tabuleiro);
	return;
	}
}
void bot(char ***matriz,int contjogada){

	if((*matriz)[1][1] == ' '){
		(*matriz)[1][1] = 'O';
		return;
	}
	int cont = 0;
	/////////////////////////////////////////////////////
	//verificando possibilidades de vitoria na horizontal
	/////////////////////////////////////////////////////
	for(int i = 0;i<3;i++){
		for(int j = 0;j<3;j++){
			if((*matriz)[i][j] == 'O'){
				cont++;
			}else if((*matriz)[i][j] == 'X'){
				cont = 0;
			}
		}
		if(cont == 2){
			for(int j = 0;j<3;j++){
				if((*matriz)[i][j] == ' '){
					(*matriz)[i][j] = 'O';
					return;	
				}
			}
		}
		cont = 0;
	}
	/////////////////////////////////////////////////////
	//verificando possibilidades de vitoria na vertical
	/////////////////////////////////////////////////////
	cont = 0;
	for(int i = 0;i<3;i++){
		cont = 0;		
		for(int j = 0;j<3;j++){
			if((*matriz)[j][i] == 'O'){
				cont++;
			}else if((*matriz)[j][i] == 'X'){
				cont = 0;
			}			
		}
		if(cont == 2){
			for(int j = 0;j<3;j++){
				if((*matriz)[j][i] == ' '){
					(*matriz)[j][i] = 'O';
					return;	
				}
			}
		}
		cont = 0;
	}
	///////////////////////////////////////////////////
	//verificando possibilidades de vitoria na diagonal
	///////////////////////////////////////////////////
	cont = 0;
	for(int j = 0;j<3;j++){
		if((*matriz)[2-j][j] == 'O'){
			cont++;
		}else if((*matriz)[2-j][j] == 'X'){
				cont = 0;
		}
	}
	if(cont == 2){
		for(int j = 0;j<3;j++){
			if((*matriz)[2-j][j] == ' '){
				(*matriz)[2-j][j] = 'O';
				return;	
			}
		}
	}
	cont = 0;
	for(int j = 0;j<3;j++){
		if((*matriz)[j][j] == 'O'){
			cont++;
		}else if((*matriz)[j][j] == 'X'){
				cont = 0;
		}			
	}
	if(cont == 2){
		for(int j = 0;j<3;j++){
			if((*matriz)[j][j] == ' '){
				(*matriz)[j][j] = 'O';
				return;	
			}
		}
	}
	//verificando possibilidades de derrota
	/////////////////////////////////////////////////////
	//verificando possibilidades de derrota na horizontal
	/////////////////////////////////////////////////////
	cont = 0;
	for(int i = 0;i<3;i++){
		for(int j = 0;j<3;j++){
			if((*matriz)[i][j] == 'X'){
				cont++;
			}else if((*matriz)[i][j] == 'O'){
				cont = 0;
			}
		}
		if(cont == 2){
			for(int j = 0;j<3;j++){
				if((*matriz)[i][j] == ' '){
					(*matriz)[i][j] = 'O';
					return;	
				}
			}
		}
		cont = 0;
	}
	/////////////////////////////////////////////////////
	//verificando possibilidades de derrota na vertical
	/////////////////////////////////////////////////////
	cont = 0;
	for(int i = 0;i<3;i++){
		for(int j = 0;j<3;j++){
			if((*matriz)[j][i] == 'X'){
				cont++;
			}else if((*matriz)[j][i] == 'O'){
				cont = 0;
			}
		}
		if(cont == 2){
			for(int j = 0;j<3;j++){
				if((*matriz)[j][i] == ' '){
					(*matriz)[j][i] = 'O';
					return;	
				}
			}
		}
		cont = 0;
	}
	/////////////////////////////////////////////////////
	//verificando possibilidades de derrota na diagonal
	/////////////////////////////////////////////////////
	cont = 0;
	for(int j = 0;j<3;j++){
		if((*matriz)[2-j][j] == 'X'){
			cont++;
		}else if((*matriz)[2-j][j] == 'O'){
			cont = 0;
		}
	}
	if(cont == 2){
		for(int j = 0;j<3;j++){
			if((*matriz)[2-j][j] == ' '){
				(*matriz)[2-j][j] = 'O';
				return;	
			}
		}
	}
	cont = 0;
	for(int j = 0;j<3;j++){
		if((*matriz)[j][j] == 'X'){
			cont++;
		}else if((*matriz)[j][j] == 'O'){
			cont = 0;
		}
	}
	if(cont == 2){
		for(int j = 0;j<3;j++){
			if((*matriz)[j][j] == ' '){
				(*matriz)[j][j] = 'O';
				return;	
			}
		}
	}
	//marcando casa aleatoria caso nao haja condiçoes de vitoria ou derrota
	if(contjogada >= 9){
		return;
	}
	srand(time(NULL));
	int x;
	int y;
	
	if( (((*matriz)[0][0] == 'X' && (*matriz)[1][1] == 'O' && (*matriz)[2][2]=='X')||((*matriz)[2][0] == 'X' && (*matriz)[1][1] == 'O' && (*matriz)[0][2]=='X'))&&contjogada==3){
		(*matriz)[2][1] = 'O';
		return;
	}
	
	if((*matriz)[0][0] == ' '){
	
		(*matriz)[0][0] = 'O';
		return;
		
	}else if((*matriz)[0][2] == ' '){
	
		(*matriz)[0][2] = 'O';
		return;
		
	}else if((*matriz)[2][0] == ' '){
	
		(*matriz)[2][0] = 'O';
		return;
		
	}else if((*matriz)[2][2] == ' '){
	
		(*matriz)[2][2] = 'O';
		return;
	}
	
	while(1){
		x = rand() % 3;
		y = rand() % 3;
		if((*matriz)[x][y] == ' '){
			(*matriz)[x][y] = 'O';
			return;
		}
	}
	return;
}
void RANKING(jogadores *saves,int ini){
	printf ("    ----------- Ranking -------------\n");
	printf(	"  | Vitorias | Empates | Derrotas | Nomes\n");
	for(int i = 0;i<ini;i++){
		printf("%dº| %d        | %d       | %d        | %s\n",(i+1),saves[i].vitoria,saves[i].empate,saves[i].derrota,saves[i].nome);
	}
	printf("Aperte qualquer coisa para retornar ao menu\n");
	char saida[68];
	scanf("%s",saida);
	return;		      
}
