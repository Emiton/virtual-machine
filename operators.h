/*
 * operators.h
 *
 * Authors: Emiton Alves and Cameron LaFreniere
 * 
 * Description: This file holds all operators that will execute instructions 
 *              provided by the program
 */
void conditionalMove(uint32_t *regValues, uint32_t *reg);
void segmentedLoad(uint32_t *regValues, uint32_t *reg, Mem mem);
void segmentedStore(uint32_t *regValues, uint32_t *reg, Mem mem);
void addition(uint32_t *regValues, uint32_t *reg);
void multiplication(uint32_t *regValues, uint32_t *reg);
void division(uint32_t *regValues, uint32_t *reg);
void bitwiseNAND(uint32_t *regValues, uint32_t *reg);
void halt(Stack_T unmappedSegs, Mem mem);
void mapSegment(uint32_t *regValues, uint32_t *reg, Stack_T unmappedSegs, Mem mem);
void unmapSegment(uint32_t *regValues, uint32_t *reg, Stack_T unmappedSegs, Mem mem);
void output(uint32_t *regValues, uint32_t *reg);
void input(uint32_t *regValues, uint32_t *reg);
void loadProgram(uint32_t *regValues, uint32_t *reg, Mem mem, int* instructionCount, int* counter); // counter and program length?
void loadValue(uint32_t *regValues, uint32_t *reg, uint32_t storedValue);
void freeProg(Stack_T unmappedSegs, Mem mem);
