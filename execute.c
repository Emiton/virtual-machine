/*
 * execute.c
 *
 * Authors : Emiton Alves and Cameron LaFreniere
 *
 * Description: This file runs the program by going through each
 *              instruction and performs an instruction based
 *              on a given op code. The file also initializes
 *              the program memory and creates a stack to store
 *              segment indices that are no longer being used but can be 
 *              used later.
 * */

#include <stdio.h>
#include <stdlib.h>
#include "execute.h"


int instructionPointer = 0;
uint32_t registersGP[8] = {0};

/**
 * This function runs through the program word by word, executing
 * each instruction based on a specified op code. The registers used in
 * each word will be retrieved to get the value they contain.
 * @param: program - This is the binary file to be opened
 * @return: Will return an instruction set that conatins all loaded
 *          instructions and a field indicating number of instructions 
 **/
void runProgram(struct segment *instructionSet)
{
    memSpace memory = initializeMemory(100);
    Stack_T unmappedSegs = Stack_new();
    int instructionCount = instructionSet->segmentLength;
    mapProgramSegment(memory, instructionSet);
    for(;instructionPointer < instructionCount;instructionPointer++)
    {
        struct segment *currentSegment = getSegment(memory, 0);
        uint32_t currentWord = currentSegment->segmentWords[instructionPointer];
        uint32_t operator = (uint32_t)Bitpack_getu(currentWord, 4, 28);
        uint32_t A, B, C;
        switch(operator)
        {
            case 0:
                A = (uint32_t) Bitpack_getu(currentWord, 3, 6);
                B = (uint32_t) Bitpack_getu(currentWord, 3, 3);
                C = (uint32_t) Bitpack_getu(currentWord, 3, 0); 
                conditionalMove(A, B, C, registersGP);
                break;
            case 1:
                A = (uint32_t) Bitpack_getu(currentWord, 3, 6);
                B = (uint32_t) Bitpack_getu(currentWord, 3, 3);
                C = (uint32_t) Bitpack_getu(currentWord, 3, 0);
                segmentedLoad(A, B, C, registersGP, memory);
                break;
            case 2:
                A = (uint32_t) Bitpack_getu(currentWord, 3, 6);
                B = (uint32_t) Bitpack_getu(currentWord, 3, 3);
                C = (uint32_t) Bitpack_getu(currentWord, 3, 0);
                segmentedStore(A, B, C, registersGP, memory);
                break;
            case 3:
                A = (uint32_t) Bitpack_getu(currentWord, 3, 6);
                B = (uint32_t) Bitpack_getu(currentWord, 3, 3);
                C = (uint32_t) Bitpack_getu(currentWord, 3, 0);
                addition(A, B, C, registersGP);
                break;
            case 4:
                A = (uint32_t) Bitpack_getu(currentWord, 3, 6);
                B = (uint32_t) Bitpack_getu(currentWord, 3, 3);
                C = (uint32_t) Bitpack_getu(currentWord, 3, 0);
                multiplication(A, B, C, registersGP);
                break;
            case 5:
                A = (uint32_t) Bitpack_getu(currentWord, 3, 6);
                B = (uint32_t) Bitpack_getu(currentWord, 3, 3);
                C = (uint32_t) Bitpack_getu(currentWord, 3, 0);
                division(A, B, C, registersGP);
                break;
            case 6:
                A = (uint32_t) Bitpack_getu(currentWord, 3, 6);
                B = (uint32_t) Bitpack_getu(currentWord, 3, 3);
                C = (uint32_t) Bitpack_getu(currentWord, 3, 0);
                bitwiseNAND(A, B, C, registersGP);
                break;
            case 7:
                halt(unmappedSegs, memory);
                break;
            case 8:
                B = (uint32_t) Bitpack_getu(currentWord, 3, 3);
                C = (uint32_t) Bitpack_getu(currentWord, 3, 0);
                mapSegment(B, C, registersGP, unmappedSegs, memory);
                break;
            case 9:
                C = (uint32_t) Bitpack_getu(currentWord, 3, 0);
                unmapSegment(C, registersGP, unmappedSegs, memory);
                break;
            case 10:
                C = (uint32_t) Bitpack_getu(currentWord, 3, 0);
                output(C, registersGP);
                break;
            case 11:
                C = (uint32_t) Bitpack_getu(currentWord, 3, 0);
                input(C, registersGP);
                break;
            case 12:
                B = (uint32_t) Bitpack_getu(currentWord, 3, 3);
                C = (uint32_t) Bitpack_getu(currentWord, 3, 0);
                loadProgram(B,
                            C, 
                            registersGP, 
                            memory, 
                            &instructionPointer, 
                            &instructionCount);
                break;
            case 13:
                C = (uint32_t) Bitpack_getu(currentWord, 3, 25);
                uint32_t value = (uint32_t) Bitpack_getu(currentWord, 25, 0);
                loadValue(C, registersGP, value);
                break;
        } 
    }
}
