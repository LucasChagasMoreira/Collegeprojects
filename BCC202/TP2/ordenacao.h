#ifndef ORDENACAO_H
#define ORDENACAO_H

// Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// Structs
typedef struct ponto Ponto;
typedef struct rota Rota;

Ponto *alocaPonto(int);
void desalocaPontos(Ponto *);
Rota *alocaRota(int, int);
void desalocaRota(Rota *, int);
void lerRotas(Rota *, int, int);
void calcularDistancia(Rota *, int, int);
void calcularDeslocamento(Rota *, int, int);
void imprime(Rota *, int);
//Ordenação
void ordenaDistancia(Rota *, int, int);
void ordenaDeslocamento(Rota *, int, int);
void ordenaNome(Rota *, int, int);
void ordena(Rota *, int);

#endif