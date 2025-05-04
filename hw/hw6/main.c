#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "cache.h"
#include "simulate.h"

size_t count_lines(FILE *file) {
  size_t num_lines = 0;
  char buf[100];
  while (fgets(buf, sizeof(buf), file)) {
    num_lines += 1;
  }
  fseek(file, 0, SEEK_SET);
  return num_lines;
}

int main(int argc, const char *argv[]) {
  assert(argc == 2);
  FILE *file = fopen(argv[1], "r");
  size_t num_lines = count_lines(file);
  fprintf(stderr, "Number of lines in %s: %zu\n", argv[1], num_lines);
  struct Instruction *insts = parse_asm(file, num_lines);
  start_simulation(insts, num_lines);
  free(insts);
  fclose(file);
  print_cache_statistics();
  return 0;
}
