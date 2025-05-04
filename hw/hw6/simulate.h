#ifndef _CS110_HW6_SIMULATE_H_
#define _CS110_HW6_SIMULATE_H_

#include <stdlib.h>

// All instructions you need to implement.
// Instructions not in this list are not required.
enum Instruction_type {
  INSTRUCTION_li,
  INSTRUCTION_lw,
  INSTRUCTION_sw,
  INSTRUCTION_add,
  INSTRUCTION_and,
  INSTRUCTION_div,
  INSTRUCTION_mul,
  INSTRUCTION_rem,
  INSTRUCTION_or,
  INSTRUCTION_sll,
  INSTRUCTION_srl,
  INSTRUCTION_sub,
  INSTRUCTION_xor,
  INSTRUCTION_addi,
  INSTRUCTION_andi,
  INSTRUCTION_ori,
  INSTRUCTION_slli,
  INSTRUCTION_srli,
  INSTRUCTION_xori,
  INSTRUCTION_beq,
  INSTRUCTION_bne
};

struct Instruction {
  enum Instruction_type type;
  unsigned rs1;
  unsigned rs2;
  unsigned rd;
  long imm;
};

struct Instruction *parse_asm(FILE *, size_t);
void start_simulation(struct Instruction *, size_t);

#endif /* simulate.h */