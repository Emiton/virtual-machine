#ifndef LAB_DEFINED
#define LAB_DEFINED

#include <stdint.h>
#include <seq.h>
#include <assert.h>
#include "bitpack.h"

  typedef uint32_t Um_instruction;
  typedef uint32_t Um_opcode;

  void put_inst(Seq_T stream, int i, Um_instruction *inst);
  Um_instruction * get_inst(Seq_T stream, int i);
  void emit(Seq_T stream, Um_instruction *inst);
  void emit_goto_test(Seq_T stream);
  void emit_cmv_test(Seq_T stream);
  void emit_out_string(Seq_T stream, const char *s, int aux_reg);
  void emit_halt_test(Seq_T stream);
  void emit_map_unmap_test(Seq_T stream);
  void emit_arith_test(Seq_T stream);
  void emit_load_store_test(Seq_T stream);
  void add_label(Seq_T stream, int location_to_patch, int label_value);
  void Um_write_sequence(FILE *output, Seq_T stream);
  
  enum ops {CMV = 0, SLOAD, SSTORE, ADD, MULT, DIVIDE, NAND, HALT, MAP,
                                        UMAP, OUT, IN, LOADP, LOADV};
  enum regs { r0 = 0, r1, r2, r3, r4, r5, r6, r7 };
  Um_instruction * three_register(Um_opcode op, unsigned ra, unsigned rb, 
                                  unsigned rc);
  
  Um_instruction * loadval(unsigned ra, unsigned val);
  
  
  
#endif

