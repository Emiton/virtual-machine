/*
 * program_loader.h
 *
 * Authors : Emiton Alves and Cameron LaFreniere
 *
 * Description: This file TODO
 *
 * */

struct segment {
    int *segmentWords;
    int segmentLength;
};

struct segment *loadProgram(char *program);
