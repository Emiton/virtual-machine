/*
 * segment.c
 *
 * Authors : Emiton Alves and Cameron LaFreniere
 *
 * Description: This file holds all truths related to the true representation of
 *              a segment. The functions provided allow for operations on a
 *              segment to be performed, such as placing a segment in memory,
 *              storing a value, getting a value, getting a segment, and
 *              removing a segment from memory.   
 *
 * */

#include "segment.h"

/**
 * This function gets a segment from memory and assigns a specific word
 * in that segment to be assigned to a value.
 * @param: memory - the memory space of the program
 *          value - the value to be stored in the segment
 *         seg_ID - the index of the segment in the sequence
 *       position - the word offset in the segment 
 **/    
 void storeValue(memSpace memory, uint32_t value, uint32_t seg_ID, uint32_t position)
{
    assert(seg_ID < (uint32_t) memoryLength(memory));
    struct segment *currentSegment = Seq_get(memory, (int)seg_ID);
    currentSegment->segmentWords[position] = value;
}

/**
 * This function gets a segment and based on a given offset, will return
 * the value of a word. 
 * @param: memory - the memory space of the program
 *         seg_ID - the index of the segment in the sequence
 *       position - the word offset in the segment 
 * 
 * @return: value in a specified word within a segment 
 **/    
uint32_t getValue(memSpace memory, uint32_t seg_ID, uint32_t position)
{
    struct segment *currentSegment = Seq_get(memory, seg_ID);
    return currentSegment->segmentWords[position];
}


/**
 * This function retrieves a segment specified by the segment index (represented
 * by seg_ID). 
 * @param: memory - the memory space of the program
 *         seg_ID - the index of the segment in the sequence
 *       position - the word offset in the segment 
 * @return: segment specified by seg_ID
 **/    
struct segment *getSegment(memSpace memory, uint32_t seg_ID)
{
    struct segment *currentSegment = (struct segment*) Seq_get(memory, seg_ID);
    return currentSegment;
}


/**
 * This function gets the original  program and its instruction count,
 * then creates a replacement program that stores all words from the original
 * program. The original program is then removed from memory and replaced by the
 * new program in memory. The instruction count is returned.
 * 
 * @param: memory - the memory space of the program
 *         seg_ID - the index of the segment in the sequence
 *
 * @return: number of words (instructions) in replacement program
 **/    
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


/**
 * This function creates a new segment of a length passed in
 * and assigns all words within the segment to be 0. If the seg_ID
 * is within the bounds of the current memory, the new segment
 * is placed within memory. Otherwise, the new segment is appended
 * to the end of the memory, expanding the memory by one segment.
 *
 * @param: memory - the memory space of the program
 *          value - the value to be stored in the segment
 *         seg_ID - the index of the segment in the sequence
 * @return: segment ID of the new segment
 **/    
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
    
    else  
    {
        Seq_addhi(memory, replacementSeg);
        return (uint32_t) (memoryLength(memory) - 1);
    } 
}

/**
 * This function gets a segment specified by its ID and
 * will free that segment from memory. The value at its address in memory
 * is now NULL.
 * @param: memory - the memory space of the program
 *         seg_ID - the index of the segment in the sequence
 **/
void unmap_seg(memSpace memory, uint32_t seg_ID)
{
    struct segment *currentSegment = Seq_get(memory, seg_ID);
    free(currentSegment->segmentWords);
    Seq_put(memory, seg_ID, NULL);
}


/**
 * This function maps the program instruction set into segment 0 in memory.
 * @param:      memory - the memory space of the program
 *     *instructionSet - the words of the program   
 **/
void mapProgramSegment(memSpace memory, struct segment *instructionSet)
{
  Seq_addhi(memory, instructionSet); 
}
