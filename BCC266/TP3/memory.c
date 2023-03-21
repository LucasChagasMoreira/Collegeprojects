#include "memory.h"
#include <stdio.h>

void startRAM(RAM *ram, int size) //Os valores inicias da RAM serão  carregados do disco
{
    
    FILE *arq = fopen("disk.dat", "rb");    
    
    ram->blocks = (MemoryBlock *)calloc(sizeof(MemoryBlock), size);
    ram->size = size;

    for (int i = 0; i < size; i++)
    {
        //Leitura do endereço em disco

        int tag; //Address in Disk
        fread(&tag, sizeof(int), 1, arq);
        ram->blocks[i].tag = tag;

        //printf("%d ", tag);

        for (int j = 0; j < WORDS_SIZE; j++)
        {
            int item;

            //Leitura das palavras em cada bloco 

            fread(&item, sizeof(int), 1, arq);
            ram->blocks[i].words[j] = item;
          
            //printf("%d ", ram->blocks[i].words[j]);
        }
        //printf("\n");
    }
    fclose(arq);
}

// Função para criar o disco
void startDisk(int size)
{

    // Cria o arquivo binário
    FILE *arq;
    arq = fopen("disk.dat", "wb");

    // Gera o ID do bloco e os números
    for (int i = 0; i < size; i++)
    {
        // Escreve o ID do Bloco
        fwrite(&i, sizeof(int), 1, arq);

        int v[WORDS_SIZE];
        for (int j = 0; j < WORDS_SIZE; j++)
        {
            v[j] = rand() % 100;
            // Escreve cada int da palavra do bloco
            fwrite(&v[j], sizeof(int), 1, arq);
        }
    }

    // Fecha o arquivo
    fclose(arq);
}

void stopRAM(RAM *ram)
{
    free(ram->blocks);
}

void startCache(Cache *cache, int size)
{
    // cache->lines = (Line*) malloc(sizeof(Line) * size);
    cache->lines = (Line *)calloc(size, sizeof(Line));
    cache->size = size;

    for (int i = 0; i < cache->size; i++)
        cache->lines[i].tag = INVALID_ADD;
}

void stopCache(Cache *cache)
{
    free(cache->lines);
}

/*
void alocaLista(TLista *lista){
    lista->cabeca = (TCelula*) malloc(sizeof(TCelula));
    lista->ultimo = lista->cabeca;
    lista->cabeca->prox = NULL;
}

void desalocaLista(TLista *lista){
    TCelula *aux1, *aux2;
    aux1 = lista->cabeca;
    while(aux1 != NULL)
    {
        aux2 = aux1;
        aux1 = aux1->prox;
        free(aux2);
    }
}

void insereInicioLRU (TLista *lista, TItem x){
    TCelula *aux;
    aux = lista->cabeca;
    while(aux->prox->pos.pos != x.pos) //Deve se parar no elemento anterior ao elemento que será retirado
    {
        aux= aux->prox;
    }

    if(aux == NULL) //Caso em que o elemento ainda não está na lista
    {
        TCelula *new = (TCelula*) malloc(sizeof(TCelula));
        new->pos = x;
        new->prox = lista->cabeca->prox;
        lista->cabeca->prox = new;
        return ;
    }

    //Caso em que o elemento está no meio da lista
    TCelula *new = (TCelula*) malloc (sizeof(TCelula));
    new->pos = x;
    TCelula *celulaARemover;
    celulaARemover = aux->prox;
    aux->prox = aux->prox->prox;
    free(celulaARemover);
    new->prox = lista->cabeca->prox;
    lista->cabeca->prox = new;
    return ;
}

void removeFinalLRU(TLista *lista, TItem x){
    TCelula *aux;
    aux = lista->cabeca;
    while(aux->prox->pos.pos != NULL) //Deve se parar no elemento anterior ao elemento que será retirado
    {
        aux= aux->prox;
    }
    lista->ultimo = aux;
    TCelula *celulaASerRemovida;
    celulaASerRemovida = aux->prox;
    free(celulaASerRemovida);
    lista->ultimo->prox = NULL;
}
*/