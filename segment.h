#ifndef SEGMENT_INCLUDED
#define SEGMENT_INCLUDED

#include "memory.h"
#include "program_loader.h"
#include <stdlib.h>

void storeValue(memSpace memory, uint32_t value, uint32_t seg_ID, uint32_t position);
uint32_t getValue(memSpace memory, uint32_t seg_ID, uint32_t position);
struct segment *getSegment(memSpace memory, uint32_t seg_ID);
int program_load(memSpace memory, uint32_t seg_ID);
uint32_t map_seg(memSpace memory, uint32_t value, uint32_t seg_ID);
void unmap_seg(memSpace memory, uint32_t seg_ID);
void mapProgramSegment(memSpace memory, struct segment *instructionSet);
#endif
