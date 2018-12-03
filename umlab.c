// This is the code from the lab handout
  typedef uint32_t Um_instruction;
  Um_instruction three_register(Um_opcode op, int ra, int rb, int rc);
  Um_instruction loadval(unsigned ra, unsigned val);
  static inline Um_instruction halt(void) {
    return three_register(HALT, 0, 0, 0);
  }
  enum regs { r0 = 0, r1, r2, r3, r4, r5, r6, r7 };
  extern Um_write_sequence(FILE *output, Seq_T stream);
  static inline void emit(Seq_T stream, Um_instruction inst) {
    assert(sizeof(inst) <= sizeof(uintptr_t));
    Seq_addhi(stream, (void *)(uintptr_t)inst);
  }
  static inline Um_instruction get_inst(Seq_T stream, int i) {
    assert(sizeof(Um_instruction) <= sizeof(uintptr_t));
    return (Um_instruction)(uintptr_t)(Seq_get(stream, i));
  }

  static inline void put_inst(Seq_T stream, int i, Um_instruction inst) {
    assert(sizeof(inst) <= sizeof(uintptr_t));
    Seq_put(stream, i, (void *)(uintptr_t) inst);
  }
  void emit_halt_test(Seq_T stream) {
    emit(stream, halt());
    emit(stream, loadval(r1, 'B'));
    emit(stream, output(r1));
    emit(stream, loadval(r1, 'a'));
    emit(stream, output(r1));
    emit(stream, loadval(r1, 'd'));
    emit(stream, output(r1));
    emit(stream, loadval(r1, '!'));
    emit(stream, output(r1));
    emit(stream, loadval(r1, '\n'));
    emit(stream, output(r1));
  }
  static void add_label(Seq_T stream, int location_to_patch, int label_value) {
    Um_instruction inst = get_inst(stream, location_to_patch);
    unsigned k = Bitpack_getu(inst, 25, 0);
    inst       = Bitpack_newu(inst, 25, 0, label_value+k);
    put_inst(stream, location_to_patch, inst);
  }
static void emit_out_string(Seq_T stream, const char *s, int aux_reg);
  void emit_goto_test(Seq_T stream) {
    int patch_L = Seq_length(stream);
    emit(stream, loadval(r7, 0));  // will be patched to 'r7 := L'
    emit(stream, loadprogram(r0, r7)); // should goto label L
    emit_out_string(stream, "GOTO failed.\n", r1);
    emit(stream, halt());
    add_label(stream, patch_L, Seq_length(stream)); // define 'L' to be here
    emit_out_string(stream, "GOTO passed.\n", r1);
    emit(stream, halt());
  }  
