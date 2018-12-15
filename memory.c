#include "memory.h"

memspace initializeMemory(memspace *memory)
{
    return Seq_new(100);
}

void freeMemory(memspace *memory)
{
    Seq_free(memory);
}

int memoryLength(memspace memory)
{
    return Seq_length(memory);
}
