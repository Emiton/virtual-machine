/*
 * execute.h
 *
 * Authors : Emiton Alves and Cameron LaFreniere
 * 
 * Description: Interface for execute.c
 * */

#ifndef EXECUTE_INCLUDED
#define EXECUTE_INCLUDED

#include "program_loader.h"
#include "operators.h"
#include "bitpack.h"
#include <stack.h>
#include "memory.h"

void runProgram(struct segment *instructionSet);


#endif
