#include <stdio.h>
#include <stdlib.h> // TODO: remove?
#include "bitpack.h"
#include "program_loader.h"

uint32_t fileLength(FILE *currentFile);

/**
 * This method is used to load a program segment from the binary file
 * @param: program - This is the binary file to be opened
 * @return: will return an instruction set that conatins all loaded
 * instructions and a field indicating number of instructions 
 * */
struct segment *load(char *program)
{
    FILE *input = fopen(program, "r");
    if(input == NULL)
    {
        fprintf(stderr, "Could not open file\n");
        exit(EXIT_FAILURE);
    }

    uint32_t programLength = fileLength(input) / 4;
    int *inst = malloc(programLength * sizeof(uint32_t)); // TODO: think about array_t instead
    (void) inst;

}

/**
 * This method will determine the number of 32 bit words in a file
 * @param: currentFile - the file for which the words will be counted
 * @return: will return value specifying the number of words in the file 
 * */
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
