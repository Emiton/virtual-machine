#include "memory.h"

memSpace initializeMemory(int length)
{
    return Seq_new(length);
}

void freeMemory(memSpace *memory)
{
    Seq_free(memory);
}

int memoryLength(memSpace memory)
{
    return Seq_length(memory);
}
