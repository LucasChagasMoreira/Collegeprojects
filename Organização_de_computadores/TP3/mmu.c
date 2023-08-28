#include "mmu.h"

#include <stdio.h>

bool canOnlyReplaceBlock(Line line)
{
    // Or the block is empty or
    // the block is equal to the one in memory RAM and can be replaced
    if (line.tag == INVALID_ADD || (line.tag != INVALID_ADD && !line.updated))
        return true;
    return false;
}

int memoryCacheMapping(int address, Cache *cache)
{
#ifdef DIRECT_MAPPING
    return address % cache->size;
#endif

#ifdef ASSOCIATIVE_MAPPING //! Função que verifica se o bloco já está em alguma linha da cache - um for percorre a cache
    for (int i = 0; i < cache->size; i++)
    {
        if (address == cache->lines[i].tag) //*Caso o bloco seja encontrado na cache, a posição da linha, que contém o bloco, na cache é retornada
        {
            return i;
        }
    }

    return 0; //* Caso o bloco não esteja na cache o valor 0 é retornado por padrão
#endif
}

int memoryRAMMapping(int address, RAM *ram)
{
    int pos = 0;
    for (int i = 0; i < ram->size; i++)
    {
        if (address == ram->blocks[i].tag) // Caso o endereço passao seja igual a tag do bloco da ram, retorna a posição no vetor de memoryblocks
        {
            pos = i;
        }
    }
    return pos; // Caso o endereço não esteja na RAM, 0 é retornado
}

int blockFromRAMWillBeRemoved(RAM *ram)
{
#ifdef LFU
    int pos = rand() % ram->size;
    MemoryBlock menor = ram->blocks[pos];

    for (int i = 0; i < ram->size; i++)
    {
        if (menor.count > ram->blocks[i].count)
        {
            menor = ram->blocks[i];
            pos = i;
        }
    }

    return pos;
#endif

#ifdef RANDOM
    return rand() % ram->size;
#endif

#ifdef FIFO
    int pos = rand() % ram->size;
    MemoryBlock maior = ram->blocks[pos];

    for (int i = 0; i < ram->size; i++)
    {
        if (maior.count < ram->blocks[i].count)
        {
            maior = ram->blocks[i];
            pos = i;
        }
    }

    return pos;
#endif

    return 0;
}

#if defined LRU || defined FIFO
void atualizaLRUorFIFO(Cache *cache, int pos)
{

    for (int i = 0; i < cache->size; i++)
    {
        if (cache->lines[i].tag != INVALID_ADD) //*Soma mais um em posições não-vazias, ou seja, block != -1
        {
            cache->lines[i].qtdVezesUsado += 1; //*Incrementa as posições não-vazias
        }
    }

#ifdef LRU
    cache->lines[pos].qtdVezesUsado = 0; //*Zera o elemento que acabou de ser acessado. No LRU, ele vai remover a linha que tem o maior valor no contador, ou seja, que não foi zerado a um certo tempo, que é o que foi usado com menos frequência
#endif
}
#endif

int blockWillBeRemoved(Cache *cache) //! Função que definirá a posição do bloco que irá sair | Segue os critérios de implementação do LRU, LFU ou FIFO
{
#if defined LRU || defined LFU || defined FIFO
    //*Todas as comparações iniciarão com a posição 1 da cache
    Line lessUsed = cache->lines[0];
    int pos = 0;
#endif

    //*Primeiro, verificamos se não há nenhuma posição vazia, caso haja, ela será o "bloco removido"
    for (int i = 0; i < cache->size; i++)
    {
        if (cache->lines[i].tag == -1)
        {
            return i; //* Retorna a posição da linha na cache
        }
    }

#ifdef LFU
    //*Caso não tenha posições vazias, a posição o menos utilizado (método LFU) será retornado
    for (int i = 1; i < cache->size; i++)
    {
        if (cache->lines[i].qtdVezesUsado < lessUsed.qtdVezesUsado) //*O critério para decidir qual bloco será escolhido é o que foi menos utilizado (menor valor no contador)
        {
            lessUsed = cache->lines[i];
            pos = i;
        }
    }

    return pos;
#endif

#if defined LRU || defined FIFO
    //*O Bloco que será removido será o que tiver o maior número. No caso do LRU, corresponderia a linha que foi menos utilizada recentemente. No caso do FIFO, seria a primeira linha que entrou na cache
    for (int i = 1; i < cache->size; i++)
    {
        if (cache->lines[i].qtdVezesUsado > lessUsed.qtdVezesUsado)
        {
            lessUsed = cache->lines[i];
            pos = i;
        }
    }

    return pos;
#endif

#ifdef RANDOM
    int posRandom = rand() % cache->size; //! Uma posição aleatória da cache será retornada para ser removida, pois o critério utilizado é aleatoriedade.
    return posRandom;
#endif

    return 0;
}

void zeraQtdVezesUsado(Cache *cache, int posLine) //*Zera o contador da linha
{
    cache->lines[posLine].qtdVezesUsado = 0;
}

void updateMachineInfos(Machine *machine, int hitmiss, int cost)
{
    switch (hitmiss)
    {
    case 1:
        machine->hitL1 += 1;
        break;

    case 2:
        machine->hitL2 += 1;
        machine->missL1 += 1;
        break;

    case 3:
        machine->missL1 += 1;
        machine->missL2 += 1;
        machine->hitL3 += 1;
        break;
    case 4:
        machine->missL1 += 1;
        machine->missL2 += 1;
        machine->missL3 += 1;
        machine->hitRAM += 1;
        break;
    case 5:
        machine->missL1 += 1;
        machine->missL2 += 1;
        machine->missL3 += 1;
        machine->missRAM += 1;
        machine->hitDisk += 1;
        break;
    }
    machine->totalCost += cost;
}
/*
void AtualizaDisco(MemoryBlock *ram)
{
    FILE *arq = fopen("disk.dat", "rb");
    // Copia do disco para um vetor
    MemoryBlock disco[SIZE_DISK];
    for (int i = 0; i < SIZE_DISK; i++)
    {
        int id;
        int v[WORDS_SIZE];
        fread(&id, sizeof(int), 1, arq);
        fread(v, sizeof(int), WORDS_SIZE, arq);
        disco[i].tag = id;
        for (int j = 0; j < WORDS_SIZE; j++)
        {
            disco[i].words[j] = v[j];
        }
    }
    fclose(arq);

    FILE *arq2 = fopen("diskTemp.dat", "wb");
    // Grava todos os registros anteriores ao que será alterado
    for (int i = 0; i < ram->tag; i++)
    {
        fwrite(&disco[i].tag, sizeof(int), 1, arq2);
        fwrite(disco[i].words, sizeof(int), WORDS_SIZE, arq2);
    }
    // Grava o novo registro
    fwrite(&ram->tag, sizeof(int), 1, arq2);
    fwrite(ram->words, sizeof(int), WORDS_SIZE, arq2);

    // Grava os demais registros posteriores
    for (int i = ram->tag + 1; i < SIZE_DISK; i++)
    {
        fwrite(&disco[i].tag, sizeof(int), 1, arq2);
        fwrite(disco[i].words, sizeof(int), WORDS_SIZE, arq2);
    }

    remove("disk.dat");
    rename("diskTemp.dat", "disk.dat");

    fclose(arq2);
}
*/
int VerificaRamDisk(MemoryBlock *ram, Address address, int *ramPos, RAM *ramMachine)
{

    // Caso em que o endereço está na ram
    if (ramMachine->blocks[*ramPos].tag == address.block)
    {
        ramMachine->blocks[*ramPos].count++;
        return 4; // Custo: Acessar a ram
    }

    // Caso em que o endereço está no disco
    *ramPos = blockFromRAMWillBeRemoved(ramMachine); // Posição do bloco que saiŕa da ram

    // Armazenando bloco que sairá da ram
    MemoryBlock aux;
    aux.count = ramMachine->blocks[*ramPos].count;
    aux.tag = ramMachine->blocks[*ramPos].tag;
    for (int j = 0; j < WORDS_SIZE; j++)
    {
        aux.words[j] = ramMachine->blocks[*ramPos].words[j];
    }

    // Obtendo endereço do disco
    FILE *arq = fopen("disk.dat", "rb");

    int id;
    int v[WORDS_SIZE];

    for (int i = 0; i <= address.block; i++)
    {
        fread(&id, sizeof(int), 1, arq);
        for (int j = 0; j < WORDS_SIZE; j++)
        {
            fread(&v[j], sizeof(int), 1, arq);
        }
    }

    fclose(arq);

    // Passando do disco para ram
    ramMachine->blocks[*ramPos].tag = address.block;
    for (int i = 0; i < WORDS_SIZE; i++)
    {
        ramMachine->blocks[*ramPos].words[i] = v[i];
    }

    // Passando o bloco que sairá da RAM para o disco
    FILE *arq2 = fopen("disk.dat", "ab+");

    int idAux;
    int vAux[WORDS_SIZE];

    for (int i = 0; i < *ramPos; i++)
    {
        fread(&idAux, sizeof(int), 1, arq2);
        for (int j = 0; j < WORDS_SIZE; j++)
        {
            fread(&vAux[j], sizeof(int), 1, arq2);
        }
    }

    fwrite(&aux.tag, sizeof(int), 1, arq2);
    for (int j = 0; j < WORDS_SIZE; j++)
    {
        fwrite(&aux.words[j], sizeof(int), 1, arq2);
    }

    fclose(arq2);

    return 5; // Custo: Acessar o disco
}

void atualizaLRUorFIFOforRAM(RAM *ram)
{
    for (int i = 0; i < ram->size; i++)
    {
        // Acrescenta mais um no contador de todos os blocos da RAM
        ram->blocks[i].count++;
    }
}

Line *MMUSearchOnMemorys(Address add, Machine *machine)
{
    Line *cache1 = machine->l1.lines;
    Line *cache2 = machine->l2.lines;
    Line *cache3 = machine->l3.lines;
    MemoryBlock *ram = machine->ram.blocks;

    //*Verifica se o bloco do disco está em uma das linhas da cache (mapeamento associativo). Caso esteja, vai retornar a posição da linha na cache. Senão retorna 0.
    int l1pos = memoryCacheMapping(add.block, &machine->l1);
    int l2pos = memoryCacheMapping(add.block, &machine->l2);
    int l3pos = memoryCacheMapping(add.block, &machine->l3);
    int rampos = memoryRAMMapping(add.block, &machine->ram);

//*Soma mais um em todos os elementos das caches, para preservar a diferença no tempo de entrada de cada um para saber quem entrou primeiro (Critério do FIFO - Primeiro a entrar, primeiro a sair)
#ifdef FIFO
    atualizaLRUorFIFO(&machine->l1, l1pos);
    atualizaLRUorFIFO(&machine->l2, l2pos);
    atualizaLRUorFIFO(&machine->l3, l3pos);
    atualizaLRUorFIFOforRAM((&machine->ram));
#endif

    //*IFs que verificam se o bloco está nas posições da cache
    if (cache1[l1pos].tag == add.block)
    {
        /* Block is in memory cache L1 */
        cache1[l1pos].cost = COST_ACCESS_L1;
        cache1[l1pos].cacheHit = 1;
#ifdef LFU
        cache1[l1pos].qtdVezesUsado += 1;
#endif

#ifdef LRU
        atualizaLRUorFIFO(&machine->l1, l1pos);
#endif
    }
    else if (cache2[l2pos].tag == add.block)
    {
        /* Block is in memory cache L2 */
        // cache2[l2pos].updated = false; //Não foi atualizado
        cache2[l2pos].cost = COST_ACCESS_L1 + COST_ACCESS_L2;
        cache2[l2pos].cacheHit = 2;
#ifdef LFU
        cache2[l2pos].qtdVezesUsado += 1;
#endif

#ifdef LRU
        atualizaLRUorFIFO(&machine->l2, l2pos);
#endif

        updateMachineInfos(machine, cache2[l2pos].cacheHit, cache2[l2pos].cost); // atualiza as informações referentes a cachemiss e cachehit
        return &(cache2[l2pos]);
    }
    else if (cache3[l3pos].tag == add.block)
    {
        cache3[l3pos].cost = COST_ACCESS_L1 + COST_ACCESS_L2 + COST_ACCESS_L3;
        cache3[l3pos].cacheHit = 3;

#ifdef LFU
        cache3[l3pos].qtdVezesUsado += 1;
#endif

#ifdef LRU
        atualizaLRUorFIFO(&machine->l3, l3pos);
#endif

        updateMachineInfos(machine, cache3[l3pos].cacheHit, cache3[l3pos].cost); // atualiza as informações referentes a cachemiss e cachehit
        return &(cache3[l3pos]);                                                 // retorna a linha
    }
    else
    {
        /* Block only in memory RAM, need to bring it to cache and manipulate the blocks */
        //*Decidirá a posição com base nos critérios - LRU, LFU, FIFO ou Random
        l3pos = blockWillBeRemoved(&machine->l3);
        l2pos = blockWillBeRemoved(&machine->l2);
        l1pos = blockWillBeRemoved(&machine->l1);
        int cacheHit = 4;
        if (!canOnlyReplaceBlock(cache1[l1pos]))
        {
            /* The block on cache L1 cannot only be replaced, the memories must be updated */
            if (!canOnlyReplaceBlock(cache2[l2pos]))
            {
                /* The block on cache L2 cannot only be replaced, the memories must be updated */
                if (!canOnlyReplaceBlock(cache3[l3pos]))
                {
                    // Caso em que não pode susbtituir direto na L3

                    // Se o bloco estiver no disco, a função passara para RAM
                    cacheHit = VerificaRamDisk(ram, add, &rampos, &(machine->ram));

                    // Passa da L3 para RAM
                    int ramposWillBeRemoved = blockFromRAMWillBeRemoved(&(machine->ram));

                    ram[ramposWillBeRemoved].tag = cache3[l3pos].tag;
                    for (int i = 0; i < WORDS_SIZE; i++)
                    {
                        ram[ramposWillBeRemoved].words[i] = cache3[l3pos].block.words[i];
                    }
                    ram[ramposWillBeRemoved].count = 0; // Zera contador
                }
                cache3[l3pos] = cache2[l2pos];          // pega do l2 e passa pro l3
                zeraQtdVezesUsado(&machine->l3, l3pos); // zera o contador do bloco movido
            }
            cache2[l2pos] = cache1[l1pos];          // pega do l1 e passa pro l2
            zeraQtdVezesUsado(&machine->l2, l2pos); // zera o contador do bloco movido
        }

        // Verifica RAM e disco
        cacheHit = VerificaRamDisk(ram, add, &rampos, &(machine->ram));

        // Custo de acessp as memórias
        int costAcess;
        if (cacheHit == 4)
        {
            costAcess = COST_ACCESS_L1 + COST_ACCESS_L2 + COST_ACCESS_L3 + COST_ACCESS_RAM;
        }
        else
        {
            costAcess = COST_ACCESS_L1 + COST_ACCESS_L2 + COST_ACCESS_L3 + COST_ACCESS_RAM + COST_ACCESS_DISK;
        }

        // PEGA DA RAM E BOTA NO L1
        // Passa da RAM para L1
        // cacheHit = VerificaRamDisk(ram, add, &rampos, &(machine->ram));
        for (int i = 0; i < WORDS_SIZE; i++) // Passa as palavras para a L3
        {
            cache1[l1pos].block.words[i] = ram[rampos].words[i];
        }
        // Passa da RAM para L1
        cache1[l1pos].tag = add.block;
        cache1[l1pos].updated = false;
        cache1[l1pos].cost = costAcess;
        cache1[l1pos].cacheHit = cacheHit;
        zeraQtdVezesUsado(&machine->l1, l1pos); // zera o contador do bloco movido
    }
    updateMachineInfos(machine, cache1[l1pos].cacheHit, cache1[l1pos].cost);
    return &(cache1[l1pos]);
}

// se a linha estiver com valores diferentes na chache diferente do da RAM, ela deve ser movida para L2 e consequentemente

// mapeamento associativo é um for para ver qual linha está com os valores iguais da ram e substituir nele

// MAPEAMENTO ASSOCIATIVO  FAZ UM FOR E VÊ QUAL ESTÁ ATUALIZADA (VALOR IGUAL DA RAM E DA CACHE) E A SUBSTITUI