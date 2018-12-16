/*
 * operators.c
 *
 * Authors : Emiton Alves and Cameron LaFreniere
 *
 * Description: This file holds the implementation of all operators which
 *              in almost all cases (except for halt) perform a computation
 *              upon a register. An operator has at most three registers
 *              that it will operate on, but some include only two, one,
 *              or zero (for halt). 
 *
 *
 * */
#include <stdint.h>
#include "operators.h"
#include <assert.h>
#include <stdio.h>

/**
 * This function performs a conditional move operation upon the registers,
 * effectively setting values of register B to be the value of register A.
 * @param: A - an index of register array
 *         B - an index of register array
 *         C - an index of register array
 *       reg - register array 
 **/
void conditionalMove(uint32_t A, uint32_t B,uint32_t C, uint32_t *reg)
{
    assert(A <= 7 && B <= 7 && C <= 7);
    assert(reg != NULL);
    if(reg[C] != 0) 
    {
        reg[A] = reg[B];
    }
}

/**
 * This function loads a value  from memory into a register. Register B
 * holds the segment index and register C holds the offset of word to be loaded.
 * @param: A - an index of register array
 *         B - an index of register array
 *         C - an index of register array
 *       reg - register array 
 *    memory - memory of universal machine
 **/
void segmentedLoad(uint32_t A, uint32_t B,uint32_t C, uint32_t *reg, memSpace memory)
{
    assert(A <= 7 && B <= 7 && C <= 7);
    assert(reg != NULL);
    reg[A] = getValue(memory, reg[B], reg[C]);
}

/**
 * This function stores a value from register C into the memory location at
 * segment held by register A and the offset held by register B.
 * @param: A - an index of register array
 *         B - an index of register array
 *         C - an index of register array
 *       reg - register array
 *    memory - memory of universal machine
 *
 **/
void segmentedStore(uint32_t A, uint32_t B,uint32_t C, uint32_t *reg, memSpace memory)
{
    assert(A <= 7 && B <= 7 && C <= 7);
    assert(reg != NULL);
    assert(memory != NULL);
    storeValue(memory, reg[A], reg[B], reg[C]);
}

/**
 * This function stores a value in register A throught the summation of
 * the value stored in register B with the value stored in register C.
 * @param: A - an index of register array
 *         B - an index of register array
 *         C - an index of register array
 *       reg - register array 
 **/
void addition(uint32_t A, uint32_t B,uint32_t C, uint32_t *reg)
{
    assert(A <= 7 && B <= 7 && C <= 7);
    assert(reg != NULL);
    reg[A] = reg[B] + reg[C];
}

/**
 * This function stores a value in register A through the multiplication of
 * the value stored in register B and the value stored in register C. 
 * @param: A - an index of register array
 *         B - an index of register array
 *         C - an index of register array
 *       reg - register array 
 **/
void multiplication(uint32_t A, uint32_t B,uint32_t C, uint32_t *reg)
{
    assert(A <= 7 && B <= 7 && C <= 7);
    assert(reg != NULL);
    reg[A] = reg[B] * reg[C];
}

/**
 * This function performs a conditional move operation upon the registers,
 * effectively setting values of register B to be the value of register A.
 * @param: A - an index of register array
 *         B - an index of register array
 *         C - an index of register array
 *       reg - register array 
 **/
void division(uint32_t A, uint32_t B,uint32_t C, uint32_t *reg)
{
    assert(A <= 7 && B <= 7 && C <= 7);
    assert(reg != NULL);
    reg[A] = reg[B] / reg[C];
}

/**
 * This function performs a bitwise NOT and a bitwise AND upon values
 * in registers B & C which is stored as the value in register A.
 * @param: A - an index of register array
 *         B - an index of register array
 *         C - an index of register array
 *       reg - register array 
 **/
void bitwiseNAND(uint32_t A, uint32_t B,uint32_t C, uint32_t *reg)
{
    assert(A <= 7 && B <= 7 && C <= 7);
    assert(reg != NULL);
    reg[A] = ~(reg[B] & reg[C]);
}

/**
 * This function halts the program, freeing all memory before doing so.
 * The loop will unmap each segment in the memory that hasn't been unmapped yet.
 * It will then free the stack that now includes all segments and free the
 * memory. 
 * @params: unmappedSegs - stack storing segments that were previously mapped 
 *                memory - memory of the universal machine
 **/
void halt(Stack_T unmappedSegs, memSpace memory)
{
    assert(unmappedSegs != NULL);
    assert(memory != NULL);
    // No need to include an assert on memory since
    // Seq_T will throw a checked runtime error if
    // passing a null T to a Seq function. 
    for(int i = 0; i < memoryLength(memory); i++)
    {
        if(getSegment(memory, i) != NULL)
        {
            unmap_seg(memory, i);
        }
    } 
    
    Stack_free(&unmappedSegs);
    freeMemory(&memory);
    exit(EXIT_SUCCESS);
}

/**
 * This function will create a new segment with the number of words being the
 * value of register C. This new segment is mapped in memory with the segment
 * index of the value of register B.
 * @params:       B - an index of register array
 *                C - an index of register array
 *              reg - register array
 *     unmappedSegs - stack storing segments that were previously mapped 
 *           memory - memory of the universal machine
 **/
void mapSegment(uint32_t B, uint32_t C, uint32_t *reg, Stack_T unmappedSegs, memSpace memory)
{
    assert(B <= 7 && C <= 7); 
    assert(unmappedSegs != NULL && memory != NULL);
    if(!Stack_empty(unmappedSegs))
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

/**
 * This function will unmap an existing segment at segment index held by value
 * of register C. Register C's value will be used by another segment later on,
 * thus it is pushed to the unmappedSegs stack.
 * @params:       C - an index of register array
 *              reg - register array
 *     unmappedSegs - stack storing segments that were previously mapped 
 *           memory - memory of the universal machine
 **/
void unmapSegment(uint32_t C, uint32_t *reg, Stack_T unmappedSegs, memSpace memory)
{
    assert(C <= 7); 
    assert(unmappedSegs != NULL && memory != NULL);
    assert(reg != NULL);

    unmap_seg(memory, reg[C]);
    Stack_push(unmappedSegs, (void*)(uintptr_t) reg[C]); 
}

  
/**
 * This function displays the value in register C on the I/O device. 
 * @params: C - an index of register array
 *        reg - register array 
 **/
void output(uint32_t C, uint32_t *reg)
{    
    assert(C <= 7);
    assert(reg != NULL);
    putchar(reg[C]); //TODO: Error checking of 0 to 255 and C < 7
}

/**
 * This function loads a value into register C once input arrives from the
 * I/O device.
 * @params: C - an index of register array
 *        reg - register array 
 **/
void input(uint32_t C, uint32_t *reg)
{
    assert(C <= 7);
    assert(reg != NULL);

    uint32_t charInput = (uint32_t) getc(stdin);
    
    if(charInput == (uint32_t) EOF)
    {
        reg[C] = (uint32_t) ~0;   
    }
    
    assert(charInput <= 255);
    reg[C] = charInput;
}

/**
 * This function will duplicate a segment at the segment index held in value of
 * register B. The first segment in memory, which holds the program is abandoned.
 * The instruction (program) counter now points to segment 0 at offset of value
 * in register C.
 * @params:            B - an index of register array
 *                     C - an index of register array
 *                   reg - register array
 *                memory - memory of the universal machine
 *    instructionPointer - the pointer to the current instruction in the program
 *      instructionCount - the number of instructions in the program
 *
 **/
// TODO:instructionPointer used to be instructionCount
// instructionCount used to be counter
void loadProgram(uint32_t B, uint32_t C, uint32_t *reg, memSpace memory, int* instructionPointer, int* instructionCount)
{    
    assert(B <= 7 && C <= 7);
    assert(reg != NULL);
    assert(instructionPointer != NULL && *instructionPointer >= 0);
    assert(instructionCount != NULL && *instructionCount >= 0);
    
    *instructionPointer = reg[C] - 1;
    if(reg[B] != 0)
    {
        int replacementProgramLength = program_load(memory, reg[B]);
        *instructionCount = replacementProgramLength;
        
    }  
}

/**
 * This function takes in a value that will then be stored in register A.
 * @params:  A - an index of register array
 *         reg - register array 
 * storedValue - the value to be stored in reg A
 **/
void loadValue(uint32_t A, uint32_t *reg, uint32_t storedValue)
{
   assert(A <= 7);
   assert(reg != NULL);
   reg[A] = storedValue;
}

