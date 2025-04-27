#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "cache.h"
#include "simulate.h"

#define REGISTER_NAME_TO_NUMBER(name1, name2, number) \
  if (strcmp(register_name, name1) == 0 || strcmp(register_name, name2) == 0) return number

#define PARSE_LW(inst_name) \
  else if (strcmp(inst, #inst_name) == 0) { \
    instruction->type = INSTRUCTION_ ## inst_name; \
    instruction->rd = register_name_to_label(strtok(NULL, ", ")); \
    instruction->imm = strtol(strtok(NULL, " ("), NULL, 10); \
    instruction->rs1 = register_name_to_label(strtok(NULL, ")")); \
    fprintf(stderr, "rs1: %u, rd: %u, imm: %ld\n", instruction->rs1, instruction->rd, instruction->imm); \
  }

#define PARSE_SW(inst_name) \
  else if (strcmp(inst, #inst_name) == 0) { \
    instruction->type = INSTRUCTION_ ## inst_name; \
    instruction->rs2 = register_name_to_label(strtok(NULL, ", ")); \
    instruction->imm = strtol(strtok(NULL, " ("), NULL, 10); \
    instruction->rs1 = register_name_to_label(strtok(NULL, ")")); \
    fprintf(stderr, "rs1: %u, rs2: %u, imm: %ld\n", instruction->rs1, instruction->rs2, instruction->imm); \
  }

/* Finish the remaining macro. */
#define PARSE_RTYPE(inst_name) \
  /* Your code here. */

#define PARSE_ITYPE(inst_name) \
  /* Your code here. */

#define PARSE_SBTYPE(inst_name) \
  /* Your code here. */

/* 32 integer registers. */
static uint32_t registers[32];

/* The program counter. */
static uint32_t program_counter;

static unsigned register_name_to_label(const char *register_name) {
  /* Use the REGISTER_NAME_TO_NUMBER macro above. */
  /* Your code here. */

  /* s0 is also called fp. */
  if (strcmp(register_name, "fp") == 0) return 8;

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
  
  /* Use the PARSE_* macro you written above. */
  /* Your code here. */

  else {
    fprintf(stderr, "Invalid instruction!\n");
  }
}

struct Instruction *parse_asm(FILE *file, size_t num_lines) {
  struct Instruction *instructions = malloc(sizeof(struct Instruction) * num_lines);
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
  /* Your code here. */
}
