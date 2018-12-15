/*
 * operators.c
 *
 * Authors : Emiton Alves and Cameron LaFreniere
 *
 * Description: This file TODO
 *
 * */
#include <stdint.h>
#include "operators.h"
void conditionalMove(uint32_t *regValues, uint32_t *reg)
{
    uint32_t A = regValues[0],
             B = regValues[1],
             C = regValues[2];

    if(reg[A] != 0) 
    {
        reg[A] = reg[B];
    }
}
void segmentedLoad(uint32_t *regValues, uint32_t *reg, Mem mem)
{
    //includes memory, do later
    //TODO
}
void segmentedStore(uint32_t *regValues, uint32_t *reg, Mem mem)
{
    //TODO
}
void addition(uint32_t *regValues, uint32_t *reg)
{
    uint32_t A = regValues[0],
             B = regValues[1],
             C = regValues[2];
    
    reg[A] = reg[B] + reg[c];

}
void multiplication(uint32_t *regValues, uint32_t *reg)
{
    uint32_t A = regValues[0],
             B = regValues[1],
             C = regValues[2];
    reg[A] = reg[B] * reg[C];
}
void division(uint32_t *regValues, uint32_t *reg)
{
    uint32_t A = regValues[0],
             B = regValues[1],
             C = regValues[2];
    reg[A] = reg[B] / reg[C];
}
void bitwiseNAND(uint32_t *regValues, uint32_t *reg)
{
    uint32_t A = regValues[0],
             B = regValues[1],
             C = regValues[2];
    reg[A] = ~(reg[B] & reg[C]);
}
//TODO:
void halt(Stack_T unmappedSegs, Mem mem)
{
    //must free some portion of the memory before calling freeProg()
    freeProg(unmappedSegs, mem);
    exit(EXIT_SUCCESS);
}
void mapSegment(uint32_t *regValues, uint32_t *reg, Stack_T unmappedSegs, Mem mem)
{
    uint32_t B = regValues[1],
             C = regValues[2];
    //TODO
}
void unmapSegment(uint32_t *regValues, uint32_t *reg, Stack_T unmappedSegs, Mem mem)
{
    //TODO
    uint32_t C = regValues[2];
    //unmap a segment based on an ID
    
}
void output(uint32_t *regValues, uint32_t *reg)
{
    uint32_t C = reg[regValues[2]];
    
    assert(C <= 255); //assert that output is within ASCII range
    assert(C >= 0); 
    putchar(C);
}
void input(uint32_t *regValues, uint32_t *reg)
{
    uint32_t C = regValues[2];
    uint32_t charInput = (uint32_t) getc(stdin);
    
    if(charInput == (uint32_t) EOF)
    {
        reg[C] = (uint32_t) ~0;   
    }
    
    assert(charInput >= 0 && charInput <= 255);
    reg[C] = charInput;
}
void loadProgram(uint32_t *regValues, uint32_t *reg, Mem mem, int* instructionCount, int* counter); // counter and program length?

void loadValue(uint32_t *regValues, uint32_t *reg, uint32_t storedValue)
{
   uint32_t A = regValues[0];
   reg[A] = storedValue;
}

void freeProg(Stack_T unmappedSegs, Mem mem)
{
    // must free the memory somehow free(&mem)
    Stack_free(&unmappedSegs);
}
