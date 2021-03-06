/*
 * program_loader.h
 *
 * Authors : Emiton Alves and Cameron LaFreniere
 *
 * Description: Interface for program_loader.c
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

struct segment *load(char *program);

#endif
