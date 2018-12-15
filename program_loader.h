/*
 * program_loader.h
 *
 * Authors : Emiton Alves and Cameron LaFreniere
 *
 * Description: This file TODO
 *
 * */
#ifndef PROGRAM_LOADER_INCLUDED
#define PROGRAM_LOADER_INCLUDED

#include "bitpack.h"
#include <stdio.h>
#include <stdlib.h>

struct segment {
    int *segmentWords;
    int segmentLength;
};

struct segment *loadProgram(char *program);

#endif
