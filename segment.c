/*
 * execute.c
 *
 * Authors : Emiton Alves and Cameron LaFreniere
 *
 * Description: This file TODO
 *
 * */

#include "segment.h"

void storeValue(memSpace memory, uint32_t value, uint32_t seg_ID, uint32_t position)
{
    struct segment *currentSegment = Seq_get(memory, seg_ID);
    currentSegment->segmentWords[position] = value;
}

uint32_t getValue(memSpace memory, uint32_t seg_ID, uint32_t position)
{
    struct segment *currentSegment = Seq_get(memory, seg_ID);
    return currentSegment->segmentWords[position];
}

struct segment *getSegment(memSpace memory, uint32_t seg_ID)
{
    struct segment *currentSegment = (struct segment*) Seq_get(memory, seg_ID);
    return currentSegment;
}

int program_load(memSpace memory, uint32_t seg_ID)
{
    struct segment *currentProgram = Seq_get(memory, seg_ID);
    uint32_t instructionCount = currentProgram->segmentLength;
    struct segment *replacementProgram = NULL;
    replacementProgram = malloc(sizeof(struct segment));
    replacementProgram->segmentLength = instructionCount;
    replacementProgram->segmentWords = malloc(instructionCount * sizeof(uint32_t));

    for(uint32_t i = 0; i < instructionCount; i++)
    {
        replacementProgram->segmentWords[i] = currentProgram->segmentWords[i];
    }

    struct segment *oldProgram = Seq_get(memory, 0);
    free(oldProgram->segmentWords);
    Seq_put(memory, 0, replacementProgram);
    return instructionCount;
}

uint32_t map_seg (memSpace memory, uint32_t value, uint32_t seg_ID)
{
    struct segment *replacementSeg = NULL;
    replacementSeg = malloc(sizeof(struct segment));
    replacementSeg->segmentLength = value;
    replacementSeg->segmentWords = malloc(value * sizeof(uint32_t));

    for(uint32_t i = 0; i < value; i++)
    {
        replacementSeg->segmentWords[i] = 0;    
    }
    if(seg_ID < (uint32_t) Seq_length(memory))
    {
        Seq_put(memory, seg_ID, replacementSeg);
        return seg_ID;
    }
    else //if(seg_ID >= (uint32_t) memoryLength(memory)) // TODO: Can we cast a seq call from int to uint32_t? 
    {
        Seq_addhi(memory, replacementSeg);
        return (uint32_t) (memoryLength(memory) - 1);
    } 
}

void unmap_seg(memSpace memory, uint32_t seg_ID)
{
    struct segment *currentSegment = Seq_get(memory, seg_ID);
    free(currentSegment->segmentWords);
    Seq_put(memory, seg_ID, NULL);
}

