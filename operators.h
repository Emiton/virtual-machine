/*
 * operators.h
 *
 * Authors: Emiton Alves and Cameron LaFreniere
 *
 * Description: Interface for operators.c 
 */

#ifndef OPERATORS_INCLUDED
#define OPERATORS_INCLUDED

#include "execute.h"
#include "segment.h"
#include "memory.h"
#include <stdlib.h>
#include <stack.h>

void conditionalMove(uint32_t A, uint32_t B, uint32_t C, uint32_t *reg);
void segmentedLoad(uint32_t A, uint32_t B, uint32_t C, uint32_t *reg, memSpace memory);
void segmentedStore(uint32_t A, uint32_t B, uint32_t C, uint32_t *reg, memSpace memory);
void addition(uint32_t A, uint32_t B, uint32_t C, uint32_t *reg);
void multiplication(uint32_t A, uint32_t B, uint32_t C, uint32_t *reg);
void division(uint32_t A, uint32_t B, uint32_t C, uint32_t *reg);
void bitwiseNAND(uint32_t A, uint32_t B, uint32_t C, uint32_t *reg);
void halt(Stack_T unmappedSegs, memSpace memory);
void mapSegment(uint32_t B, uint32_t C, uint32_t *reg, Stack_T unmappedSegs, memSpace memory);
void unmapSegment(uint32_t C, uint32_t *reg, Stack_T unmappedSegs, memSpace memory);
void output(uint32_t C, uint32_t *reg);
void input(uint32_t C, uint32_t *reg);
void loadProgram(uint32_t B, uint32_t C, uint32_t *reg, memSpace memory, int* instructionCount, int* counter);
void loadValue(uint32_t A, uint32_t *reg, uint32_t storedValue);

#endif
