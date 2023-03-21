#include "memory.h"

void startRAM(RAM* ram, int size) {
    ram->blocks = (MemoryBlock*) malloc(sizeof(MemoryBlock) * size);
    ram->size = size;

    for (int i=0;i<size;i++) {
        for (int j=0;j<WORDS_SIZE;j++)
            ram->blocks[i].words[j] = rand() % 100;            
    }
}

void stopRAM(RAM *ram) {
    free(ram->blocks);
}


void startCache(Cache* cache, int size) {
    //cache->lines = (Line*) malloc(sizeof(Line) * size);
    cache->lines = (Line*) calloc(sizeof(Line), size);
    cache->size = size;

    for (int i=0;i<size;i++)
        cache->lines[i].tag = INVALID_ADD;
}

void stopCache(Cache *cache) {
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