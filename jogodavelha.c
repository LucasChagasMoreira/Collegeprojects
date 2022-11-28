#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "funcoes.h"

/////Lucas Chagas Moreira
/////Sala 32
/////matricula 22.1.4109

int main(){
	jogadores *saves = malloc(sizeof(jogadores)*20);
	char temp[100];
	int ini = 0;
	
	
	FILE *arq = fopen("velha.ini","r");
	if(arq == NULL){
	printf("uiui");
		for(int i = 0;i<10;i++){
			saves[i].vitoria = 0;
			saves[i].derrota = 0;
			saves[i].empate = 0;
		}
		
	}else{
		fscanf(arq,"%d",&ini);
		for(int i = 0;i<ini;i++){
			fscanf(arq,"%s",saves[i].nome);
			fscanf(arq,"%d",&saves[i].vitoria);
			fscanf(arq,"%d",&saves[i].empate);
			fscanf(arq,"%d",&saves[i].derrota);
		}
		fclose(arq);
	}
	
	printf("Bem vindo ao Jogo da Velha\n");
	char escolha[64];
	while(1){
		
		printf("0. Sair do Jogo\n"
			"1. Começar um novo jogo\n"
			"2. Continuar um jogo salvo\n"
			"3. Continuar o jogo atual\n"
			"4. Exibir o ranking\n"
			"Durante o jogo digite “voltar” para retornar ao menu.\n"
			"Escolha a opcão:");
		scanf("%s",escolha);
		if(strcmp(escolha,"0")==0){
			velhaini(saves,ini);
			free(saves);
			return 0;
		}
		else if(strcmp(escolha,"1")==0){
				char escolha[6];
				char nome1[30];
				char nome2[30];
				
				
				//loop de validaçao.
				while(1){
					system("clear");
					printf("Digite o número de jogadores (1 ou 2)\n");
					scanf("%s",escolha);
					if(strcmp(escolha,"1")==0){
						printf("Digite o nome do jogador 1:");
						scanf(" %s",nome1);
						pve(nome1,&ini,saves);
						ordena(saves,ini);
					}else if(strcmp(escolha,"2")==0){
						printf("Digite o nome do jogador 1:");
						scanf(" %s",nome1);
						printf("Digite o nome do jogador 2:");
						scanf(" %s",nome2);
						pvp(nome1,nome2,&ini,saves);
						ordena(saves,ini);	
					}else if(strcmp(escolha,"voltar")==0){
						break;
					}else{
						printf("Valor invalido\n\n");
			       		}
					break;
				}			
		}
		else if(strcmp(escolha,"2")==0){
			system("clear");
			printf("digite o aqrquivo do jogo: \n");
			scanf("%s",temp);
			carregajogo(temp,&ini,saves);
			ordena(saves,ini);
			
		}
		else if(strcmp(escolha,"3")==0){
			system("clear");
			carregajogo("temp.txt",&ini,saves);
			ordena(saves,ini);
		}
		else if(strcmp(escolha,"4")==0){
			system("clear");
			RANKING(saves,ini);
			
		}else{
			printf("valor invalido\n");
		}
	}
	free(saves);
	return 0;
}


