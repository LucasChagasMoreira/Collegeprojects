#ifndef __FUNCTIONS__
#define __FUNCTIONS__
#include <stdio.h>
#include <stdlib.h>

typedef struct automatocelular AutomatoCelular;

void zeramatriz(AutomatoCelular **M,int size);
AutomatoCelular **Reticuladoarq(FILE *arq,int size);
AutomatoCelular **alocarReticulado(int ordem);
void desalocaReticulado(AutomatoCelular ***M, int ordem);
void LeituraReticulado(AutomatoCelular **M, int ordem);
void imprimeReticulado(AutomatoCelular **M,int size);
void evoluirReticulado(AutomatoCelular **M,int size);
int verifica(AutomatoCelular **M,int size,int row,int col);

#endif  
