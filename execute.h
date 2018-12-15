#ifndef EXECUTE_INCLUDED
#define EXECUTE_INCLUDED

#include "program_loader.h"
#include "operators.h"
#include "bitpack.h"
#include <stack.h>
#include "memory.h"

void getRegisterValues(uint32_t word,
                           int registerPositions[],
                           uint32_t **registerValues);
void runProgram(struct segment *instructionSet);


#endif
