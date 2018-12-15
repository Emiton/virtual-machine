#include "memory.h"

memSpace initializeMemory(memSpace *memory)
{
    return Seq_new(100);
}

void freeMemory(memSpace *memory)
{
    Seq_free(memory);
}

int memoryLength(memSpace memory)
{
    return Seq_length(memory);
}
