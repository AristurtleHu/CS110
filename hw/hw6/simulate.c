#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "cache.h"
#include "simulate.h"

#define REGISTER_NAME_TO_NUMBER(name1, name2, number)                          \
  if (strcmp(register_name, name1) == 0 || strcmp(register_name, name2) == 0)  \
  return number

#define PARSE_LW(inst_name)                                                    \
  else if (strcmp(inst, #inst_name) == 0) {                                    \
    instruction->type = INSTRUCTION_##inst_name;                               \
    instruction->rd = register_name_to_label(strtok(NULL, ", "));              \
    instruction->imm = strtol(strtok(NULL, " ("), NULL, 10);                   \
    instruction->rs1 = register_name_to_label(strtok(NULL, ")"));              \
    fprintf(stderr, "rs1: %u, rd: %u, imm: %ld\n", instruction->rs1,           \
            instruction->rd, instruction->imm);                                \
  }

#define PARSE_SW(inst_name)                                                    \
  else if (strcmp(inst, #inst_name) == 0) {                                    \
    instruction->type = INSTRUCTION_##inst_name;                               \
    instruction->rs2 = register_name_to_label(strtok(NULL, ", "));             \
    instruction->imm = strtol(strtok(NULL, " ("), NULL, 10);                   \
    instruction->rs1 = register_name_to_label(strtok(NULL, ")"));              \
    fprintf(stderr, "rs1: %u, rs2: %u, imm: %ld\n", instruction->rs1,          \
            instruction->rs2, instruction->imm);                               \
  }

/* Finish the remaining macro. */
#define PARSE_RTYPE(inst_name)                                                 \
  else if (strcmp(inst, #inst_name) == 0) {                                    \
    instruction->type = INSTRUCTION_##inst_name;                               \
    instruction->rd = register_name_to_label(strtok(NULL, ", "));              \
    instruction->rs1 = register_name_to_label(strtok(NULL, ", "));             \
    instruction->rs2 = register_name_to_label(strtok(NULL, " \n"));            \
    fprintf(stderr, "rs1: %u, rs2: %u, rd: %u\n", instruction->rs1,            \
            instruction->rs2, instruction->rd);                                \
  }

#define PARSE_ITYPE(inst_name)                                                 \
  else if (strcmp(inst, #inst_name) == 0) {                                    \
    instruction->type = INSTRUCTION_##inst_name;                               \
    instruction->rd = register_name_to_label(strtok(NULL, ", "));              \
    instruction->rs1 = register_name_to_label(strtok(NULL, ", "));             \
    instruction->imm = strtol(strtok(NULL, " \n"), NULL, 0);                   \
    fprintf(stderr, "rs1: %u, rd: %u, imm: %ld\n", instruction->rs1,           \
            instruction->rd, instruction->imm);                                \
  }

#define PARSE_SBTYPE(inst_name)                                                \
  else if (strcmp(inst, #inst_name) == 0) {                                    \
    instruction->type = INSTRUCTION_##inst_name;                               \
    instruction->rs1 = register_name_to_label(strtok(NULL, ", "));             \
    instruction->rs2 = register_name_to_label(strtok(NULL, ", "));             \
    instruction->imm = strtol(strtok(NULL, " \n"), NULL, 0);                   \
    fprintf(stderr, "rs1: %u, rs2: %u, imm: %ld\n", instruction->rs1,          \
            instruction->rs2, instruction->imm);                               \
  }

/* 32 integer registers. */
static uint32_t registers[32];

/* The program counter. */
static uint32_t program_counter;

static unsigned register_name_to_label(const char *register_name) {
  REGISTER_NAME_TO_NUMBER("zero", "x0", 0);
  REGISTER_NAME_TO_NUMBER("ra", "x1", 1);
  REGISTER_NAME_TO_NUMBER("sp", "x2", 2);
  REGISTER_NAME_TO_NUMBER("gp", "x3", 3);
  REGISTER_NAME_TO_NUMBER("tp", "x4", 4);
  REGISTER_NAME_TO_NUMBER("t0", "x5", 5);
  REGISTER_NAME_TO_NUMBER("t1", "x6", 6);
  REGISTER_NAME_TO_NUMBER("t2", "x7", 7);
  REGISTER_NAME_TO_NUMBER("s0", "x8", 8);
  REGISTER_NAME_TO_NUMBER("s1", "x9", 9);
  REGISTER_NAME_TO_NUMBER("a0", "x10", 10);
  REGISTER_NAME_TO_NUMBER("a1", "x11", 11);
  REGISTER_NAME_TO_NUMBER("a2", "x12", 12);
  REGISTER_NAME_TO_NUMBER("a3", "x13", 13);
  REGISTER_NAME_TO_NUMBER("a4", "x14", 14);
  REGISTER_NAME_TO_NUMBER("a5", "x15", 15);
  REGISTER_NAME_TO_NUMBER("a6", "x16", 16);
  REGISTER_NAME_TO_NUMBER("a7", "x17", 17);
  REGISTER_NAME_TO_NUMBER("s2", "x18", 18);
  REGISTER_NAME_TO_NUMBER("s3", "x19", 19);
  REGISTER_NAME_TO_NUMBER("s4", "x20", 20);
  REGISTER_NAME_TO_NUMBER("s5", "x21", 21);
  REGISTER_NAME_TO_NUMBER("s6", "x22", 22);
  REGISTER_NAME_TO_NUMBER("s7", "x23", 23);
  REGISTER_NAME_TO_NUMBER("s8", "x24", 24);
  REGISTER_NAME_TO_NUMBER("s9", "x25", 25);
  REGISTER_NAME_TO_NUMBER("s10", "x26", 26);
  REGISTER_NAME_TO_NUMBER("s11", "x27", 27);
  REGISTER_NAME_TO_NUMBER("t3", "x28", 28);
  REGISTER_NAME_TO_NUMBER("t4", "x29", 29);
  REGISTER_NAME_TO_NUMBER("t5", "x30", 30);
  REGISTER_NAME_TO_NUMBER("t6", "x31", 31);

  /* s0 is also called fp. */
  if (strcmp(register_name, "fp") == 0)
    return 8;

  /* Return 32 on error. */
  return 32;
}

static void parse_inst(char *buf, struct Instruction *instruction) {
  char *inst = strtok(buf, " ");
  fprintf(stderr, "Instruction: %s, ", inst);

  if (strcmp(inst, "li") == 0) {
    instruction->type = INSTRUCTION_li;
    instruction->rd = register_name_to_label(strtok(NULL, ", "));
    instruction->imm = strtol(strtok(NULL, " \n"), NULL, 0);
    fprintf(stderr, "rd: %u, imm: %ld\n", instruction->rd, instruction->imm);
  }
  PARSE_LW(lw)
  PARSE_SW(sw)
  PARSE_RTYPE(add)
  PARSE_RTYPE(and)
  PARSE_RTYPE(div)
  PARSE_RTYPE(mul)
  PARSE_RTYPE(rem)
  PARSE_RTYPE(or)
  PARSE_RTYPE(sll)
  PARSE_RTYPE(srl)
  PARSE_RTYPE(sub)
  PARSE_RTYPE(xor)
  PARSE_ITYPE(addi)
  PARSE_ITYPE(andi)
  PARSE_ITYPE(ori)
  PARSE_ITYPE(slli)
  PARSE_ITYPE(srli)
  PARSE_ITYPE(xori)
  PARSE_SBTYPE(beq)
  PARSE_SBTYPE(bne)

  else {
    fprintf(stderr, "Invalid instruction!\n");
  }
}

struct Instruction *parse_asm(FILE *file, size_t num_lines) {
  struct Instruction *instructions =
      malloc(sizeof(struct Instruction) * num_lines);
  size_t i;
  char buf[100];
  for (i = 0; i < num_lines; ++i) {
    fgets(buf, sizeof(buf), file);
    parse_inst(buf, instructions + i);
  }
  return instructions;
}

/***************************
 *                         *
 *  YOUR CODE START HERE.  *
 *                         *
 ***************************/

void start_simulation(struct Instruction *instructions, size_t num) {
  // initialization
  memset(registers, 0, sizeof(registers));
  program_counter = 0;
  init_cache_system();

  // simulation
  while (program_counter < num * 4) {
    fprintf(stderr, "Instruction memory access at 0x%x.\n", program_counter);
    add_inst_access(program_counter);

    struct Instruction *instruction = instructions + program_counter / 4;
    fprintf(stderr, "Execute instruction: ");

    switch (instruction->type) {
    case INSTRUCTION_li:
      fprintf(stderr, "li x%u %ld\n", instruction->rd, instruction->imm);
      registers[instruction->rd] = instruction->imm;
      break;
    case INSTRUCTION_lw:
      fprintf(stderr, "lw x%u %ld(x%u)\n", instruction->rd, instruction->imm,
              instruction->rs1);
      add_data_access(registers[instruction->rs1] + instruction->imm);
      break;
    case INSTRUCTION_sw:
      fprintf(stderr, "sw x%u %ld(x%u)\n", instruction->rs2, instruction->imm,
              instruction->rs1);
      add_data_access(registers[instruction->rs1] + instruction->imm);
      break;
    case INSTRUCTION_add:
      fprintf(stderr, "add x%u x%u x%u\n", instruction->rd, instruction->rs1,
              instruction->rs2);
      registers[instruction->rd] =
          registers[instruction->rs1] + registers[instruction->rs2];
      break;
    case INSTRUCTION_and:
      fprintf(stderr, "and x%u x%u x%u\n", instruction->rd, instruction->rs1,
              instruction->rs2);
      registers[instruction->rd] =
          registers[instruction->rs1] & registers[instruction->rs2];
      break;
    case INSTRUCTION_div:
      fprintf(stderr, "div x%u x%u x%u\n", instruction->rd, instruction->rs1,
              instruction->rs2);
      registers[instruction->rd] =
          registers[instruction->rs1] / registers[instruction->rs2];
      break;
    case INSTRUCTION_mul:
      fprintf(stderr, "mul x%u x%u x%u\n", instruction->rd, instruction->rs1,
              instruction->rs2);
      registers[instruction->rd] =
          registers[instruction->rs1] * registers[instruction->rs2];
      break;
    case INSTRUCTION_rem:
      fprintf(stderr, "rem x%u x%u x%u\n", instruction->rd, instruction->rs1,
              instruction->rs2);
      registers[instruction->rd] =
          registers[instruction->rs1] % registers[instruction->rs2];
      break;
    case INSTRUCTION_or:
      fprintf(stderr, "or x%u x%u x%u\n", instruction->rd, instruction->rs1,
              instruction->rs2);
      registers[instruction->rd] =
          registers[instruction->rs1] | registers[instruction->rs2];
      break;
    case INSTRUCTION_sll:
      fprintf(stderr, "sll x%u x%u x%u\n", instruction->rd, instruction->rs1,
              instruction->rs2);
      registers[instruction->rd] = registers[instruction->rs1]
                                   << registers[instruction->rs2];
      break;
    case INSTRUCTION_srl:
      fprintf(stderr, "srl x%u x%u x%u\n", instruction->rd, instruction->rs1,
              instruction->rs2);
      registers[instruction->rd] =
          registers[instruction->rs1] >> registers[instruction->rs2];
      break;
    case INSTRUCTION_sub:
      fprintf(stderr, "sub x%u x%u x%u\n", instruction->rd, instruction->rs1,
              instruction->rs2);
      registers[instruction->rd] =
          registers[instruction->rs1] - registers[instruction->rs2];
      break;
    case INSTRUCTION_xor:
      fprintf(stderr, "xor x%u x%u x%u\n", instruction->rd, instruction->rs1,
              instruction->rs2);
      registers[instruction->rd] =
          registers[instruction->rs1] ^ registers[instruction->rs2];
      break;
    case INSTRUCTION_addi:
      fprintf(stderr, "addi x%u x%u %ld\n", instruction->rd, instruction->rs1,
              instruction->imm);
      registers[instruction->rd] =
          registers[instruction->rs1] + instruction->imm;
      break;
    case INSTRUCTION_andi:
      fprintf(stderr, "andi x%u x%u %ld\n", instruction->rd, instruction->rs1,
              instruction->imm);
      registers[instruction->rd] =
          registers[instruction->rs1] & instruction->imm;
      break;
    case INSTRUCTION_ori:
      fprintf(stderr, "ori x%u x%u %ld\n", instruction->rd, instruction->rs1,
              instruction->imm);
      registers[instruction->rd] =
          registers[instruction->rs1] | instruction->imm;
      break;
    case INSTRUCTION_slli:
      fprintf(stderr, "slli x%u x%u %ld\n", instruction->rd, instruction->rs1,
              instruction->imm);
      registers[instruction->rd] = registers[instruction->rs1]
                                   << instruction->imm;
      break;
    case INSTRUCTION_srli:
      fprintf(stderr, "srli x%u x%u %ld\n", instruction->rd, instruction->rs1,
              instruction->imm);
      registers[instruction->rd] =
          registers[instruction->rs1] >> instruction->imm;
      break;
    case INSTRUCTION_xori:
      fprintf(stderr, "xori x%u x%u %ld\n", instruction->rd, instruction->rs1,
              instruction->imm);
      registers[instruction->rd] =
          registers[instruction->rs1] ^ instruction->imm;
      break;
    case INSTRUCTION_beq:
      fprintf(stderr, "beq x%u x%u %ld\n", instruction->rs1, instruction->rs2,
              instruction->imm);
      if (registers[instruction->rs1] == registers[instruction->rs2]) {
        // Subtract 4 because PC will be incremented by 4 after the switch.
        program_counter += instruction->imm - 4;
      }
      break;
    case INSTRUCTION_bne:
      fprintf(stderr, "bne x%u x%u %ld\n", instruction->rs1, instruction->rs2,
              instruction->imm);
      if (registers[instruction->rs1] != registers[instruction->rs2]) {
        // Subtract 4 because PC will be incremented by 4 after the switch.
        program_counter += instruction->imm - 4;
      }
      break;
    }

    program_counter += 4;

    for (int i = 0; i < 32; ++i)
      fprintf(stderr, "x%d: %u ", i, registers[i]);
    fprintf(stderr, "Program counter: %u\n", program_counter);
  }
}
