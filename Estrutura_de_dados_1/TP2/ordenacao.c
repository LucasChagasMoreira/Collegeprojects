#include "ordenacao.h"
#define MAXTAM 1000
struct ponto
{
    int x;
    int y;
};

struct rota
{
    Ponto *pontos;
    char id[5];
    float distancia;
    float deslocamento;
};

Ponto *alocaPonto(int ordem)
{
    Ponto *vetponto = calloc(ordem, sizeof(Ponto));
    return vetponto;
}
void desalocaPontos(Ponto *vetor)
{
    free(vetor);
}

Rota *alocaRota(int qtdRotas, int nPontos)
{
    int i = 0;
    Rota *rotas = (Rota *)malloc(qtdRotas * sizeof(Rota));
    for (; i < qtdRotas; i++)
    {
        rotas[i].pontos = alocaPonto(nPontos);
    }
    return rotas;
}

void desalocaRota(Rota *rotas, int qtdRotas)
{
    int i = 0;
    for (; i < qtdRotas; i++)
    {
        desalocaPontos(rotas[i].pontos);
    }

    free(rotas);
}

void lerRotas(Rota *rotas, int qtdRotas, int qtdPontos)
{
    int i = 0;

    for (; i < qtdRotas; i++)
    {
        scanf("%s", rotas[i].id);

        int j = 0;
        for (; j < qtdPontos; j++)
        {
            scanf("%d", &rotas[i].pontos[j].x);
            scanf("%d", &rotas[i].pontos[j].y);
        }
    }
}

void calcularDistancia(Rota *rota, int qtdPontos, int qtdRotas)
{
    int j = 0;
    for (; j < qtdRotas; j++)
    {
        float soma = 0;
        int i = 0;
        for (; i < qtdPontos - 1; i++)
        {
            soma += (float)sqrt(pow(rota[j].pontos[i].x - rota[j].pontos[i + 1].x, 2) + (pow(rota[j].pontos[i].y - rota[j].pontos[i + 1].y, 2)));
        }
        soma = round(soma * 100) / 100;
        rota[j].distancia = soma;
    }
};

void calcularDeslocamento(Rota *rota, int qtdPontos, int qtdRotas)
{
    int i = 0;
    for (; i < qtdRotas; i++)
    {
        rota[i].deslocamento = sqrt(pow(rota[i].pontos[0].x - rota[i].pontos[qtdPontos - 1].x, 2) + pow(rota[i].pontos[0].y - rota[i].pontos[qtdPontos - 1].y, 2));
    }
}

void imprime(Rota *rotas, int qtdRotas)
{
    int i = 0;
    for (; i < qtdRotas; i++)
    {
        printf("%s %.2f %.2f\n", rotas[i].id, rotas[i].distancia, rotas[i].deslocamento);
    }
}

void ordenaDistancia(Rota *rotas, int inicio, int final)
{
    int esquerda, direita, pivo;
    Rota aux;
    pivo = inicio;
    esquerda = inicio;
    direita = final;

    while (esquerda <= direita)
    {
        while ((esquerda < final) && (rotas[esquerda].distancia > rotas[pivo].distancia))
        {
            esquerda++;
        }

        while ((direita > inicio) && (rotas[direita].distancia < rotas[pivo].distancia))
        {
            direita--;
        }

        if (esquerda <= direita)
        {
            aux = rotas[esquerda];
            rotas[esquerda] = rotas[direita];
            rotas[direita] = aux;
            esquerda++;
            direita--;
        }
    }
    if (direita > inicio)
    {
        ordenaDistancia(rotas, inicio, direita);
    }

    if (esquerda < final)
    {
        ordenaDistancia(rotas, esquerda, final);
    }
}

void ordenaDeslocamento(Rota *rotas, int inicio, int final)
{
    int esquerda, direita, pivo;
    Rota aux;
    pivo = inicio;
    esquerda = inicio;
    direita = final;

    while (esquerda <= direita)
    {
        while ((esquerda < final) && (rotas[esquerda].deslocamento < rotas[pivo].deslocamento))
        {
            esquerda++;
        }

        while ((direita > inicio) && (rotas[direita].deslocamento > rotas[pivo].deslocamento))
        {
            direita--;
        }

        if (esquerda <= direita)
        {
            aux = rotas[esquerda];
            rotas[esquerda] = rotas[direita];
            rotas[direita] = aux;
            esquerda++;
            direita--;
        }
    }
    if (direita > inicio)
    {
        ordenaDeslocamento(rotas, inicio, direita);
    }
    if (esquerda < final)
    {
        ordenaDeslocamento(rotas, esquerda, final);
    }
}

void ordenaNome(Rota *rotas, int inicio, int final)
{
    int esquerda, direita, pivo;
    Rota aux;
    pivo = inicio;
    esquerda = inicio;
    direita = final;

    while (esquerda <= direita)
    {
        while ((esquerda < final) && (strcmp(rotas[esquerda].id, rotas[pivo].id) < 0))
        {
            esquerda++;
        }

        while ((direita > inicio) && (strcmp(rotas[direita].id, rotas[pivo].id) > 0))
        {
            direita--;
        }

        if (esquerda <= direita)
        {
            // Troca posição
            aux = rotas[esquerda];
            rotas[esquerda] = rotas[direita];
            rotas[direita] = aux;

            esquerda++;
            direita--;
        }
    }

    // Chamadas recursivas
    if (direita > inicio)
    {
        ordenaNome(rotas, inicio, direita);
    }
    if (esquerda < final)
    {
        ordenaNome(rotas, esquerda, final);
    }
}
void ordena(Rota *rotas, int qtdRotas)
{
    int i;
    // Primeiro critério: ordem decresente da distância
    ordenaDistancia(rotas, 0, qtdRotas - 1);

   
    // Segundo critério, caso as distâncias sejam iguais, deve-se analisar o deslocamento na ordem crescente
    for (i = 0; i < qtdRotas - 1; i++)
    {
        if (rotas[i].distancia == rotas[i + 1].distancia)
        {
            int novoFinal = i;
            while ((novoFinal < qtdRotas)&&(rotas[i].distancia == rotas[novoFinal].distancia))
            {
                novoFinal++;
            }
            novoFinal--;
            // Ordena em relação ao deslocamento na ordem crescente
            ordenaDeslocamento(rotas, i, novoFinal);
            i = novoFinal;
        }
    }

    
    // Terceiro critério, caso as distâncias e o deslocamento sejam iguais, deve-se analisar o id em ordem alfabética crescente
    for (i = 0; i < qtdRotas - 1; i++)
    {
        if ((rotas[i].distancia == rotas[i + 1].distancia) && (rotas[i].deslocamento == rotas[i + 1].deslocamento))
        {
            int novoFinal = i;
            while ((novoFinal < qtdRotas) && (rotas[i].distancia == rotas[novoFinal].distancia) && (rotas[i].deslocamento == rotas[novoFinal].deslocamento))
            {
                novoFinal++;
            }
            novoFinal--;
            // Ordena em relação ao nome (ID) na ordem crescente
            ordenaNome(rotas, i, novoFinal);
            i = novoFinal;
        }
    }
    
}
