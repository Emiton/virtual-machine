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
#include <assert.h>
#include <stdio.h>

void conditionalMove(uint32_t *regValues, uint32_t *reg)
{
    uint32_t A = regValues[0],
             B = regValues[1],
             C = regValues[2];

    if(reg[C] != 0) 
    {
        reg[A] = reg[B];
    }
}
void segmentedLoad(uint32_t *regValues, uint32_t *reg, memSpace memory)
{
    uint32_t A = regValues[0],
             B = regValues[1],
             C = regValues[2];

    reg[A] = getValue(memory, reg[B], reg[C]);
}
void segmentedStore(uint32_t *regValues, uint32_t *reg, memSpace memory)
{
    uint32_t A = regValues[0],
             B = regValues[1],
             C = regValues[2];
    
    storeValue(memory, reg[A], reg[B], reg[C]);
}
void addition(uint32_t *regValues, uint32_t *reg)
{
    uint32_t A = regValues[0],
             B = regValues[1],
             C = regValues[2];
    
    reg[A] = reg[B] + reg[C];

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
void halt(Stack_T unmappedSegs, memSpace memory)
{
    //must free some portion of the memory before calling freeProg()
    for(int i = 0; i < memoryLength(memory); i++)
    {
        if(getSegment(memory, i) != NULL)
        {
            unmap_seg(memory, i);
        }
    } 
    Stack_free(&unmappedSegs);
    freeMemory(&memory);
    //freeProg(unmappedSegs, memory);
    exit(EXIT_SUCCESS);
}

void mapSegment(uint32_t *regValues, uint32_t *reg, Stack_T unmappedSegs, memSpace memory)
{
    uint32_t B = regValues[1],
             C = regValues[2];
        
    if(Stack_empty(unmappedSegs) != 1)
    {
        uint32_t segID = (uint32_t)(uintptr_t) Stack_pop(unmappedSegs);
        reg[B] = map_seg(memory, segID, reg[C]); 
    }
    else
    {
        uint32_t segID = memoryLength(memory);
        reg[B] = map_seg(memory, segID, reg[C]);
    }
}
void unmapSegment(uint32_t *regValues, uint32_t *reg, Stack_T unmappedSegs, memSpace memory)
{
    uint32_t C = regValues[2];
    unmap_seg(memory, reg[C]);
    Stack_push(unmappedSegs, (void*)(uintptr_t) reg[C]); 
}

void output(uint32_t *regValues, uint32_t *reg)
{
    printf("C: %u\n", regValues[2]); 
    uint32_t C = regValues[2];
    
    //assert(C <= 255); //assert that output is within ASCII range
    putchar(reg[C]);
}

void input(uint32_t *regValues, uint32_t *reg)
{
    uint32_t C = regValues[2];
    uint32_t charInput = (uint32_t) getc(stdin);
    
    if(charInput == (uint32_t) EOF)
    {
        reg[C] = (uint32_t) ~0;   
    }
    
    assert(charInput <= 255);
    reg[C] = charInput;
}

void loadProgram(uint32_t *regValues, uint32_t *reg, memSpace memory, int* instructionCount, int* counter)
{
    uint32_t B = regValues[1],
             C = regValues[2];  
    
    *instructionCount = reg[C] - 1;
    if(reg[B] != 0)
    {
        int replacementProgramLength = program_load(memory, reg[B]);
        *counter = replacementProgramLength;
        
    }  
}

void loadValue(uint32_t *regValues, uint32_t *reg, uint32_t storedValue)
{
   uint32_t A = regValues[0];
   reg[A] = storedValue;
}

/*
void freeProg(Stack_T unmappedSegs, memSpace memory)
{
    Stack_free(&unmappedSegs);
    freeMemory(&memory);
}*/
