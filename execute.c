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

void getRegisterValues(uint32_t word,
                           int registerPositions[],
                           uint32_t **registerValues);

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
        uint32_t *registerValues;
        int abcPositions[3] = {6,3,0};
        int bcPositions[3] = {-1,3,0};
        int cPosition[3] = {-1,-1,0};
        int aPosition[3] = {25,-1,-1};
        switch(operator)
        {
            case 0: 
                getRegisterValues(currentWord, abcPositions, &registerValues);
                conditionalMove(registerValues, registersGP);
                break;
            case 1:
                getRegisterValues(currentWord, abcPositions, &registerValues);
                segmentedLoad(registerValues, registersGP, memory);
                break;
            case 2:
                getRegisterValues(currentWord, abcPositions, &registerValues);
                segmentedStore(registerValues, registersGP, memory);
                break;
            case 3:
                getRegisterValues(currentWord, abcPositions, &registerValues); 
                addition(registerValues, registersGP);
                break;
            case 4:
                getRegisterValues(currentWord, abcPositions, &registerValues);
                multiplication(registerValues, registersGP);
                break;
            case 5:
                getRegisterValues(currentWord, abcPositions, &registerValues);
                division(registerValues, registersGP);
                break;
            case 6:
                getRegisterValues(currentWord, abcPositions, &registerValues);
                bitwiseNAND(registerValues, registersGP);
                break;
            case 7:
                halt(unmappedSegs, memory);
                break;
            case 8:
                getRegisterValues(currentWord, bcPositions, &registerValues);
                mapSegment(registerValues, registersGP, unmappedSegs, memory);
                break;
            case 9:
                getRegisterValues(currentWord, cPosition, &registerValues);
                unmapSegment(registerValues, registersGP, unmappedSegs, memory);
                break;
            case 10:
                getRegisterValues(currentWord, cPosition, &registerValues);
                output(registerValues, registersGP);
                break;
            case 11:
                getRegisterValues(currentWord, cPosition, &registerValues);
                input(registerValues, registersGP);
                break;
            case 12:
                getRegisterValues(currentWord, bcPositions, &registerValues);
                loadProgram(registerValues, 
                            registersGP, 
                            memory, 
                            &instructionPointer, 
                            &instructionCount);
                break;
            case 13:
                getRegisterValues(currentWord, aPosition, &registerValues);
                uint32_t value = Bitpack_getu(currentWord, 0, 25);
                loadValue(registerValues, registersGP, value);
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
