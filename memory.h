/**
 *
 * memory.h
 *
 * Authors : Emiton Alves and Cameron LaFreniere
 *
 * Description: Interface for memory.c
 * */

#ifndef MEMORY_INCLUDED
#define MEMORY_INCLUDED

#include <seq.h>

typedef Seq_T memSpace;

memSpace initializeMemory(int length);
void freeMemory(memSpace *memory);
int memoryLength(memSpace memory);

#endif
