/*
 * instructions.h
 *
 * Authors: Emiton Alves and Cameron LaFreniere
 * 
 * Description: This file holds all operators that will execute instructions 
 *              provided by the program
 */
void conditionalMove(uint32_t *regValues, uint32_t *r);
void segmentedLoad(uint32_t *regValues, uint32_t *r, Mem mem);
void segmentedStore(uint32_t *regValues, uint32_t *r, Mem mem);
void addition(uint32_t *regValues, uint32_t *r);
void multiplication(uint32_t *regValues, uint32_t *r);
void division(uint32_t *regValues, uint32_t *r);
void bitwiseNAND(uint32_t *regValues, uint32_t *r);
void halt(Stack_T unmappedSegs, Mem mem);
void mapSegment(uint32_t *regValues, uint32_t *r, Stack_T unmappedSegs, Mem mem);
void unmapSegment(uint32_t *regValues, uint32_t *r, Stack_T unmappedSegs, Mem mem);
void output(uint32_t *regValues, uint32_t *r);
void input(uint32_t *regValues, uint32_t *r);
void loadProgram(uint32_t *regValues, uint32_t *r, int* instructionCount, int* counter); // counter and program length?
void loadValue(uint32_t *regValues, uint32_t *r, uint32_t storedValue);
