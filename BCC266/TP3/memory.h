#ifndef MEMORY_H
#define MEMORY_H

#include <stdlib.h>
#include <stdbool.h>

#include "constants.h"
#include <stdio.h>

typedef struct {
    int words[WORDS_SIZE];
    int tag; //Adress in disk
    int count;
} MemoryBlock;

typedef struct {
    MemoryBlock* blocks;
    int size;
} RAM;

typedef struct {
    MemoryBlock block;
    int tag; /* Address of the block in memory RAM */
    bool updated;
    int cost;
    int cacheHit;
    int qtdVezesUsado;
} Line;

typedef struct {
    Line* lines;
    int size;
} Cache;

void startCache(Cache*, int);
void stopCache(Cache*);

void startRAM(RAM*, int);
void stopRAM(RAM*);

void startDisk(int size);

#endif // !MEMORY_H