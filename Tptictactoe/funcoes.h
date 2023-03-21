#ifndef FUNCOES_C
#define FUNCOES_C
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
/////Lucas Chagas Moreira
/////Sala 32
/////matricula 22.1.4109
typedef struct{
	char nome[60];
	int vitoria;
	int empate;
	int derrota;
	
}jogadores;
//funçoes auxiliares
int comandos(char *comando);
void liberamatriz(char ***matriz);
int verificavitoria(char **matriz);
void marcar(char ***matriz,char *comando,int *jogador,int *valida);
void limpamatriz(char ***);
void imprimetabuleiro(char**matriz);
//////////////////////////////////////
// funçoes de aquivo
void salvarjogo(char *nome1, char *nome2, char **tabuleiro,int qtdjogadores,char *comando,int jogada);
void velhaini(jogadores *saves, int ini);
void ordena(jogadores *saves,int ini);
int verificacopia(jogadores *saves,char *nome,int ini);
void marcavitoria(jogadores *saves, char* nome,int *ini);
void marcaderrota(jogadores *saves, char* nome,int *ini);
void marcaempate(jogadores *saves, char* nome,int *ini);
void RANKING(jogadores *saves,int ini);
/////////////////////
////funçoes principais
void carregajogo(char *temp,int *ini,jogadores *saves);
void bot(char ***matriz,int contjogada);
void pve(char *nome1,int *ini,jogadores *saves);
void pvp(char *nome1,char *nome2,int *ini,jogadores *saves);





#endif
