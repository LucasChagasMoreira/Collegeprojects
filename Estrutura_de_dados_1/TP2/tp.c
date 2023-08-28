#include "ordenacao.h"

int main(int argc, char const *argv[])
{
    int qtdRotas, qtdPontos;
    scanf("%d %d", &qtdRotas, &qtdPontos);

    Rota *rotas = alocaRota(qtdRotas, qtdPontos);

    lerRotas(rotas, qtdRotas, qtdPontos);

    calcularDistancia(rotas, qtdPontos, qtdRotas);

    calcularDeslocamento(rotas, qtdPontos, qtdRotas);

    ordena(rotas, qtdRotas);

    imprime(rotas, qtdRotas);

    desalocaRota(rotas, qtdRotas);

    return 0;
}
