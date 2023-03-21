#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <time.h>

#include "cpu.h"
#include "mmu.h"
#include "constants.h"
#include "generator.h"

//*Função que inicializa os contadores, colocando 0 em todos
void startCont(Cache *cache)
{
        for (int i = 0; i < cache->size; i++)
        {
                cache->lines[i].qtdVezesUsado = 0; //*Como esse contador é incrementado a cada hit na RAM, todos os contadores são inicializados com 0
        }
}

void startContRam(RAM *ram) // Inicializa contador da RAM
{
        for (int i = 0; i < ram->size; i++)
        {
                ram->blocks[i].count = 0;
        }
}

void start(Machine *machine, Instruction *instructions, int *memoriesSize)
{
        startRAM(&machine->ram, memoriesSize[0]);
        startCache(&machine->l1, memoriesSize[1]);
        startCache(&machine->l2, memoriesSize[2]);
        startCache(&machine->l3, memoriesSize[3]);

        machine->instructions = instructions;
        machine->hitL1 = 0;
        machine->hitL2 = 0;
        machine->hitL3 = 0;
        machine->hitRAM = 0;
        machine->hitDisk = 0;
        machine->missL1 = 0;
        machine->missL2 = 0;
        machine->missL3 = 0;
        machine->missRAM = 0;
        machine->totalCost = 0;
        startCont(&machine->l1);
        startCont(&machine->l2);
        startCont(&machine->l3);
        startContRam(&machine->ram);
}

void stop(Machine *machine)
{
        free(machine->instructions);
        stopRAM(&machine->ram);
        stopCache(&machine->l1);
        stopCache(&machine->l2);
        stopCache(&machine->l3);
}


void executaInterrupcoes(Machine *machine)
{
        //Copia as instruções originais

        //Variável para armazenar a quntidade de instruções posteriores a instrução que gerou a interrupção
        int instrucoesQtd = INSTRUCTIONS_QUANTITY + 1;

        //Aloca um vetor de Instruções para salvar as instruções posteiores a da interrupção
        Instruction *todasAsInstrucoes = (Instruction *) malloc(instrucoesQtd * sizeof(Instruction));

        //Copia todas as instruções para o vetor copia
        for (int i = 0; i < instrucoesQtd; i++)
        {
                todasAsInstrucoes[i] = machine->instructions[i];
        }

        //Libera as instruções que foram copiadas da máquina
        free(machine->instructions);

        //Passa as instruções da interrupção para a máquina
        machine->instructions = geraInstructionFoInterruption();

        //Executa as instruções da interupção
        run(machine);

        //Libera as instruções da interrupções que já foram executadas
        free(machine->instructions);

        //Aloca o vetor de instruçoes da maquina
        machine->instructions = (Instruction *) malloc(instrucoesQtd * sizeof(Instruction));

        //Volta com as instruções originais
        for (int i = 0; i < instrucoesQtd; i++)
        {
                machine->instructions[i] = todasAsInstrucoes[i];
        }

        free(todasAsInstrucoes);
}

bool interruptionProbability(){
        
        //Gera um valor entre 0 e 99, com o mais 1, será entre 1 e 100
        int probability = (rand() % 100) + 1;

        //A interrupção será gerada somente se probability for igual a um dos 5 números arbitrarios em 100, ou seja, a probabilidade disso acontecer será de 5%
        if((probability == 10) || (probability == 20) || (probability == 30) || (probability == 40) || (probability == 50)) 
        {
                return true;
        }
        else
        {
                return false;
        }
}

void executeInstruction(Machine *machine, int PC)
{
        Instruction instruction = machine->instructions[PC];
        // Registers
        int word1, word2;

        // Addresses to be consulted
        Address add1 = instruction.add1;
        Address add2 = instruction.add2;
        Address add3 = instruction.add3;

        // Line find in memory
        Line *line;

        switch (instruction.opcode)
        {
        case -1:
                printf("  > Ending execution.\n");
                break;
        case 0:                                           // Taking information to RAM
                line = MMUSearchOnMemorys(add1, machine); /* Searching block on memories */
                word1 = line->block.words[add1.word];
#ifdef PRINT_LOG
                printf("  > MOV BLOCK[%d.%d.%d](%4d) > ", line->cacheHit, add1.block, add1.word, line->block.words[add1.word]);
#endif

                line = MMUSearchOnMemorys(add2, machine); /* Searching block on memories */
#ifdef PRINT_LOG
                printf("BLOCK[%d.%d.%d](%4d|", line->cacheHit, add2.block, add2.word, line->block.words[add2.word]);
#endif

                line->block.words[add2.word] = word1;
                line->updated = true;
#ifdef PRINT_LOG
                printf("%4d).\n", line->block.words[add2.word]);
#endif
               //!INTERRUPÇÕES

                if(interruptionProbability()) //Se a probabilidade bater, as intruções serão executadas
                {
                        printf("EXECUTANDO INTERRUPÇÕES\n");
                        executaInterrupcoes(machine);
                        printf("TERMINANDO DE EXECUTAR INTERRUPÇÕES\n");
                }
                
                break;
        case 1:                                           // Sum
                line = MMUSearchOnMemorys(add1, machine); /* Searching block on memories */
                word1 = line->block.words[add1.word];
#ifdef PRINT_LOG
                printf("  > SUM BLOCK[%d.%d.%d](%4d)", line->cacheHit, add1.block, add1.word, line->block.words[add1.word]);
#endif

                line = MMUSearchOnMemorys(add2, machine); /* Searching block on memories */
                word2 = line->block.words[add2.word];
#ifdef PRINT_LOG
                printf(" + BLOCK[%d.%d.%d](%4d)", line->cacheHit, add2.block, add2.word, line->block.words[add2.word]);
#endif

                line = MMUSearchOnMemorys(add3, machine); /* Searching block on memories */
#ifdef PRINT_LOG
                printf(" > BLOCK[%d.%d.%d](%4d|", line->cacheHit, add3.block, add3.word, line->block.words[add3.word]);
#endif

                line->updated = true;
                line->block.words[add3.word] = word2 + word1;
#ifdef PRINT_LOG
                printf("%4d).\n", line->block.words[add3.word]);
#endif
                break;
        case 2:                                           // Subtract
                line = MMUSearchOnMemorys(add1, machine); /* Searching block on memories */
                word1 = line->block.words[add1.word];
#ifdef PRINT_LOG
                printf("  > SUB BLOCK[%d.%d.%d](%4d)", line->cacheHit, add1.block, add1.word, line->block.words[add1.word]);
#endif

                line = MMUSearchOnMemorys(add2, machine); /* Searching block on memories */
                word2 = line->block.words[add2.word];
#ifdef PRINT_LOG
                printf(" - BLOCK[%d.%d.%d](%4d)", line->cacheHit, add2.block, add2.word, line->block.words[add2.word]);
#endif

                line = MMUSearchOnMemorys(add3, machine); /* Searching block on memories */
#ifdef PRINT_LOG
                printf(" > BLOCK[%d.%d.%d](%4d|", line->cacheHit, add3.block, add3.word, line->block.words[add3.word]);
#endif

                line->updated = true;
                line->block.words[add3.word] = word2 - word1;

#ifdef PRINT_LOG
                printf("%4d).\n", line->block.words[add3.word]);
#endif
                

                break;

        default:
                printf("Invalid instruction.\n");
        }
#ifdef PRINT_INTERMEDIATE_RAM
        printMemories(machine);
#endif
}

void run(Machine *machine)
{
        int PC = 0; // Program Counter
        while (machine->instructions[PC].opcode != -1)
        {
                executeInstruction(machine, PC++);
                printf("\tL1:(%6d, %6d) | L2:(%6d, %6d) | L3:(%6d, %6d) | RAM:(%6d, %6d) | DISK:(%6d) | COST: %d\n",
                       machine->hitL1, machine->missL1,
                       machine->hitL2, machine->missL2,
                       machine->hitL3, machine->missL3,
                       machine->hitRAM,machine->missRAM,
                       machine->hitDisk,
                       machine->totalCost);
        }
}

void printc(char *text, int fieldWidth)
{
        int padlenLeft = floor((fieldWidth - strlen(text)) * 0.5);
        int padlenRight = ceil((fieldWidth - strlen(text)) * 0.5);
        printf("|%*s%s%*s|", padlenLeft, "", text, padlenRight, "");
}

void printcolored(int n, bool updated)
{
        if (updated)
                printf("\x1b[1;37;42m[%5d]\x1b[0m", n); // Green
        else
                printf("\x1b[1;37;41m[%5d]\x1b[0m", n); // Red
}

void printMemories(Machine *machine)
{
        printf("\x1b[0;30;47m     ");
        printc("RAM", WORDS_SIZE * 8 - 1);
        printc("Cache L3", WORDS_SIZE * 8 + 6);
        printc("Cache L2", WORDS_SIZE * 8 + 6);
        printc("Cache L1", WORDS_SIZE * 8 + 6);
        printf("\x1b[0m\n");
        for (int i = 0; i < machine->ram.size; i++)
        {
                printf("\x1b[0;30;47m%5d|\x1b[0m", machine->ram.blocks[i].tag);

                for (int j = 0; j < WORDS_SIZE; j++) // Printa a RAM
                        printf(" %5d |", machine->ram.blocks[i].words[j]);
                if (i < machine->l3.size)
                {
                        printf("|");
                        printcolored(machine->l3.lines[i].tag, machine->l3.lines[i].updated); // Printa a L3
                        for (int j = 0; j < WORDS_SIZE; j++)
                                printf(" %5d |", machine->l3.lines[i].block.words[j]);

                        if (i < machine->l2.size)
                        {
                                printf("|");
                                printcolored(machine->l2.lines[i].tag, machine->l2.lines[i].updated); // Printa a L2
                                for (int j = 0; j < WORDS_SIZE; j++)
                                        printf(" %5d |", machine->l2.lines[i].block.words[j]);
                                if (i < machine->l1.size)
                                {
                                        printf("|");
                                        printcolored(machine->l1.lines[i].tag, machine->l1.lines[i].updated); // Printa a L1
                                        for (int j = 0; j < WORDS_SIZE; j++)
                                                printf(" %5d |", machine->l1.lines[i].block.words[j]);
                                }
                        }
                }
                printf("\n");
        }
}
