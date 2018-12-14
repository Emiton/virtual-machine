/*
 * program_loader.h
 *
 * Authors : Emiton Alves and Cameron LaFreniere
 *
 * Description: This file TODO
 *
 * */

struct segment {
    int *segment_words;
    int segment_length;
};

/*
 * 
 *
 *
 * */
struct segment *load(char *program);
