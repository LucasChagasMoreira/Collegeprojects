#ifndef GENERATOR_H
#define GENERATOR_H

#include "cpu.h"

Instruction* generateRandomInstructions(int);
Instruction* readInstructions(char*, int*);
Instruction *geraInstructionFoInterruption();

#endif // !GENERATOR_H