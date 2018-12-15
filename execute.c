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

//uint32_t* getRegisterValues(uint32_t word,
//                           int registerPositions[],
//                           uint32_t *registerValues);

//void getRegisterValues(uint32_t word,
//                           int registerPositions[],
//                           uint32_t **registerValues);

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
    memSpace memory = initializeMemory(100);
    Stack_T unmappedSegs = Stack_new();
    int instructionCount = instructionSet->segmentLength;
    Seq_addhi(memory, instructionSet);

    for(;instructionPointer < instructionCount;instructionPointer++)
    {
        struct segment *currentSegment = Seq_get(memory, 0);
        uint32_t currentWord = currentSegment->segmentWords[instructionPointer];
        uint32_t operator = (uint32_t)Bitpack_getu(currentWord, 4, 28); // look at casting and other methods. Is this safe?
        //uint32_t registerValues[3] = {0}; // Registers that will be operated on 
        //uint32_t *registerValues;
        uint32_t A, B, C;
        /*int abcPositions[3] = {6,3,0};
        int bcPositions[3] = {-1,3,0};
        int cPosition[3] = {-1,-1,0};
        int aPosition[3] = {25,-1,-1};*/
        switch(operator)
        {
            case 0:
                A = Bitpack_getu(currentWord, 3, 6);
                B = Bitpack_getu(currentWord, 3, 3);
                C = Bitpack_getu(currentWord, 3, 0); 
                conditionalMove(A, B, C, registersGP);
                break;
            case 1:
                A = Bitpack_getu(currentWord, 3, 6);
                B = Bitpack_getu(currentWord, 3, 3);
                C = Bitpack_getu(currentWord, 3, 0);
                segmentedLoad(A, B, C, registersGP, memory);
                break;
            case 2:
                A = Bitpack_getu(currentWord, 3, 6);
                B = Bitpack_getu(currentWord, 3, 3);
                C = Bitpack_getu(currentWord, 3, 0);
                segmentedStore(A, B, C, registersGP, memory);
                break;
            case 3:
                A = Bitpack_getu(currentWord, 3, 6);
                B = Bitpack_getu(currentWord, 3, 3);
                C = Bitpack_getu(currentWord, 3, 0);
                addition(A, B, C, registersGP);
                break;
            case 4:
                A = Bitpack_getu(currentWord, 3, 6);
                B = Bitpack_getu(currentWord, 3, 3);
                C = Bitpack_getu(currentWord, 3, 0);
                multiplication(A, B, C, registersGP);
                break;
            case 5:
                A = Bitpack_getu(currentWord, 3, 6);
                B = Bitpack_getu(currentWord, 3, 3);
                C = Bitpack_getu(currentWord, 3, 0);
                division(A, B, C, registersGP);
                break;
            case 6:
                A = Bitpack_getu(currentWord, 3, 6);
                B = Bitpack_getu(currentWord, 3, 3);
                C = Bitpack_getu(currentWord, 3, 0);
                bitwiseNAND(A, B, C, registersGP);
                break;
            case 7:
                halt(unmappedSegs, memory);
                break;
            case 8:
                B = Bitpack_getu(currentWord, 3, 3);
                C = Bitpack_getu(currentWord, 3, 0);
                mapSegment(B, C, registersGP, unmappedSegs, memory);
                break;
            case 9:
                C = Bitpack_getu(currentWord, 3, 0);
                unmapSegment(C, registersGP, unmappedSegs, memory);
                break;
            case 10:
                C = Bitpack_getu(currentWord, 3, 0);
                output(C, registersGP);
                break;
            case 11:
                C = Bitpack_getu(currentWord, 3, 0);
                input(C, registersGP);
                break;
            case 12:
                B = Bitpack_getu(currentWord, 3, 3);
                C = Bitpack_getu(currentWord, 3, 0);
                loadProgram(B,
                            C, 
                            registersGP, 
                            memory, 
                            &instructionPointer, 
                            &instructionCount);
                break;
            case 13:
                C = Bitpack_getu(currentWord, 3, 25);
                loadValue(C, registersGP, value);
                break;
        } 
    }
}
/*
// TODO remove registerValues, not used, remove from all 
uint32_t* getRegisterValues(uint32_t word,
                           int registerPositions[],
                           uint32_t *registerValues) 
{
    uint32_t regVal[3] = {0};
    for(int i = 0; i < 3; i++)
    {
        if(registerPositions[i] != -1)
        {
            regVal[i] = (uint32_t) Bitpack_getu(word, 3, registerPositions[i]);
        }
    }
    (void)registerValues;
    return *regVal;
}
*/
/*
void getRegisterValues(uint32_t word,
                           int registerPositions[],
                           uint32_t **registerValues) 
{
    uint32_t regVal[3] = {0};
    for(int i = 0; i < 3; i++)
    {
        if(registerPositions[i] != -1)
        {
            regVal[i] = (uint32_t) Bitpack_getu(word, 3, registerPositions[i]);
        }

    }
    *registerValues = regVal;
}
*/
