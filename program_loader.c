/*
 * program_loader.c
 *
 * Authors : Emiton Alves and Cameron LaFreniere
 *
 * Description: This file handles the loading of a binary file.
 *              The input file will be translated into a set of 32 bit words.
 *              The set of words are returned to the client.
 *
 * */

#include <stdio.h>
#include <stdlib.h> 
#include "bitpack.h"
#include "program_loader.h"

uint32_t fileLength(FILE *currentFile);
uint32_t createWord(FILE *program);

/**
 * This method is used to load a program segment from the binary file
 * @param: program - This is the binary file to be opened
 * @return: will return an instruction set that conatins all loaded
 * instructions and a field indicating number of instructions 
 * */
struct segment *loadProgram(char *program)
{
    FILE *input = fopen(program, "r");
    if(input == NULL)
    {
        fprintf(stderr, "Could not open file\n");
        exit(EXIT_FAILURE);
    }

    uint32_t programLength = fileLength(input) / 4;
    struct segment *instructionSet = NULL;
    instructionSet = malloc(sizeof(struct segment));
    instructionSet->segmentWords = malloc(programLength * sizeof(uint32_t));
    instructionSet->segmentLength = programLength;
    //int *instructionSet = malloc(programLength * sizeof(uint32_t)); // TODO: think about array_t instead
        
    uint32_t currentWord = 0;
    
    for(uint32_t i = 0; i < programLength; i++)
    {
        currentWord = createWord(input);    
        instructionSet->segmentWords[i] = currentWord;
    }

    return instructionSet;
}

/**
 * This method will determine the number of 32 bit words in a file
 * @param: currentFile - the file for which the words will be counted
 * @return: will return value specifying the number of words in the file 
 **/
uint32_t fileLength(FILE *currentFile)
{
    char currentChar = 0;
    uint64_t numberOfCharacters = 0;

    while (currentChar != EOF)
    {
        currentChar = fgetc(currentFile);
        numberOfCharacters += 1;
    }

    fseek(currentFile, 0, SEEK_SET);
    // TODO: If fseek gives headache, close file here and reopen after fileLength called 
    //fclose(currentFile);
    return (uint32_t) (numberOfCharacters -  1) / 4;
}

/**
 * This method will extact a word from a file
 * @param: program - the file where words a taken from
 * @return: will return a 32 bit word
 **/
uint32_t createWord(FILE *program)
{
    uint32_t word = 0;
    int bytesInWord[4] = {0,0,0,0}; // hold the differnt bytes in a word
    
    for(int i = 0; i < 4; i++)
    {
        bytesInWord[i] = getc(program);
        int bytePosition = 4 - i - 1; // in order to place bytes in reverse
        word = Bitpack_newu(word, 8, bytePosition * 8, bytesInWord[i]);
    }

    return word;
}
