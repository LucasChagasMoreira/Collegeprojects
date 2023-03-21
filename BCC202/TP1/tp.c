#include "automato.h"
#include <stdio.h>
#include <stdlib.h>



int main(){
    int tamanho;

    scanf("%d",&tamanho);
    
    AutomatoCelular **reticulado = alocarReticulado(tamanho);

    LeituraReticulado(reticulado,tamanho);

    evoluirReticulado(reticulado,tamanho);
    
    imprimeReticulado(reticulado,tamanho);

    desalocaReticulado(&reticulado,tamanho);
    
    return 0;
}
