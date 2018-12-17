/*
 * um.c
 *
 * Authors : Emiton Alves and Cameron LaFreniere
 *
 * Description: This file is the starting point for our program. It will load
 *              a binary file into an instruction set. It will then execute the
 *              instruction set. Everything is initiated from this point. 
 * */

#include <stdio.h>
#include "program_loader.h"
#include "execute.h"

/**
 * This function drives the entire program
 * @params: argc - number of arguments from command line
 *          argv - command line arguments
 * */
int main(int argc, char *argv[])
{
    
    if(argc == 2)
    {
        struct segment *program = load(argv[1]);
        runProgram(program);        
    }
    else
    {
        fprintf(stderr, "usgae: ./um program \n");
    }

}
