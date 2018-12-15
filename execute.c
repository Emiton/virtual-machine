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
    // Create memory TODO
    // Create unmapped stack
    int instructionCount = instructionSet->segmentLength;
    // Add program to mem sequence

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
                conditonalMove(registerValues, r);
                break;
            case 1:
                //
                break;
            case 2:
                //
                break;
            case 3:
                //
                break;
            case 4:
                //
                break;
            case 5:
                //
                break;
            case 6:
                //
                break;
            case 7:
                //
                break;
            case 8:
                //
                break;
            case 9:
                //
                break;
            case 10:
                //
                break;
            case 11:
                //
                break;
            case 12:
                //
                break;
            case 13:
                //
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
