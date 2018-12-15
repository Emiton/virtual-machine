/*
 * execute.c
 *
 * Authors : Emiton Alves and Cameron LaFreniere
 *
 * Description: This file TODO
 *
 * */

#include <stdio.h>
#include <stdlib.h>
#include "execute.h"

int instructionPointer = 0;
uint32_t registersGP[8] = {0};

/**TODO
 * This function is used to load a program segment from the binary file
 * @param: program - This is the binary file to be opened
 * @return: will return an instruction set that conatins all loaded
 * instructions and a field indicating number of instructions 
 **/
void runProgram(struct segment *instructionSet)
{
    uint32_t A, B, C;
    memSpace memory = initializeMemory(100);
    Stack_T unmappedSegs = Stack_new();
    int instructionCount = instructionSet->segmentLength;
    Seq_addhi(memory, instructionSet);

    for(;instructionPointer < instructionCount ;instructionPointer++)
    {
        struct *segment currentSegment = Seq_get(memory, 0);
        uint32_t currentWord = currentSegment->segmentWords[instructionPointer];
        uint32_t operator = (uint32_t)Bitpack_getu(currentWord, 4, 28); // look at casting and other methods. Is this safe?
        uint32_t registersValues[3] = {0}; // Registers that will be operated on 
        switch(operator)
        {
            case 0:
                registerValues = getRegisterValues(currentWord, 
                                                   [6,3,0],
                                                   registerValues);
                conditonalMove(registerValues, registersGP);
                break;
            case 1:
                registerValues = getRegisterValues(currentWord, 
                                                   [6,3,0],
                                                   registerValues);
                segmentedLoad(registerValues, registersGP, memory);
                break;
            case 2:
                registerValues = getRegisterValues(currentWord, 
                                                   [6,3,0],
                                                   registerValues);
                segmentedStore(registerValues, registersGP, memory);
                break;
            case 3:
                registerValues = getRegisterValues(currentWord, 
                                                   [6,3,0],
                                                   registerValues);
                add(registerValues, registersGP);
                break;
            case 4:
                registerValues = getRegisterValues(currentWord, 
                                                   [6,3,0],
                                                   registerValues);
                multiply(registerValues, registersGP);
                break;
            case 5:
                registerValues = getRegisterValues(currentWord, 
                                                   [6,3,0],
                                                   registerValues);
                divide(registerValues, registersGP);
                break;
            case 6:
                registerValues = getRegisterValues(currentWord, 
                                                   [6,3,0],
                                                   registerValues);
                bitwiseNAND(registerValues, registersGP);
                break;
            case 7:
                halt(unmappedSegs, memory);
                break;
            case 8:
                registerValues = getRegisterValues(currentWord, 
                                                   [-1,3,0],
                                                   registerValues);
                mapSegment(registerValues, registersGP, unmappedSegs, memory);
                break;
            case 9:
                registerValues = getRegisterValues(currentWord, 
                                                   [-1,-1,0],
                                                   registerValues);
                unmapSegment(registerValues, registersGP, unmappedSegs, memory);
                break;
            case 10:
                registerValues = getRegisterValues(currentWord, 
                                                   [-1,-1,0],
                                                   registerValues);
                output(registerValues, registersGP);
                break;
            case 11:
                registerValues = getRegisterValues(currentWord, 
                                                   [-1,-1,0],
                                                   registerValues);
                input(registerValues, registersGP);
                break;
            case 12:
                registerValues = getRegisterValues(currentWord, 
                                                   [-1,3,0],
                                                   registerValues);
                loadProgram(registerValues, 
                            registersGP, 
                            memory, 
                            &instructionPointer, 
                            &instructionCount);
                break;
            case 13:
                registerValues = getRegisterValues(currentWord, 
                                                   [25,-1,-1],
                                                   registerValues);
                uint32_t value = Bitpack_getu(currentWord, 0, 25);
                loadValue(registerValues, registersGP, value);
                break;
        }
    }
}

int32_t* getRegisterValues(uint32_t word,
                           int[] registerPositions,
                           uint32_t *registerValues) 
{
    for(int i = 0; i < 3; i++)
    {
        if(registerPositions[i] != -1)
        {
            registerValues[i] = (uint32_t) Bitpack_getu(word, 3, registerPositions[i]);
        }
    }
    return registerValues;
}
