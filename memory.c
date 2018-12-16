/**
 *
 * memory.c
 *
 * Authors : Emiton Alves and Cameron LaFreniere
 *
 * Description: This file is where the secrets of memory lie. Notice that there
 *              are no references to segments, meaning that memory.c does not
 *              concern itself with the implementation of the indices of 
 *              the sequence that it initializes and eventually frees. 
 *
 * */

#include "memory.h"


/**
 * This function creates a sequence from Hansen's CII, which will store the
 * memory for the program (UM).
 * @param: length - the number of indices to be initialized in the sequence.
 **/
 memSpace initializeMemory(int length)
{
    return Seq_new(length);
}

/**
 * This function will free the entire sequence which is the memory of the UM.
 * @param: *memory - memory of the UM 
 **/
void freeMemory(memSpace *memory)
{
    Seq_free(memory);
}

/**
 *  This function returns the number of indices in the sequence, which
 *  represents the length of the memory in the UM. 
 * @param: memory - memory of the UM 
 **/
int memoryLength(memSpace memory)
{
    return Seq_length(memory);
}

