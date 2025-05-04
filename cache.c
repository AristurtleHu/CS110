#include "cache.h"
#include <stdbool.h>
#include <stdio.h>

uint32_t cache[4];
bool valid[4];
int lru[4];
int total_access;
int inst_hit;
int data_hit;

void init_cache_system() {
  for (int i = 0; i < 4; i++) {
    cache[i] = 0;
    valid[i] = false;
    lru[i] = 0;
  }
  total_access = 0;
  inst_hit = 0;
  data_hit = 0;
}

bool match_addr(uint32_t address, uint32_t cache_line) {
  return (address & 0xFFFFFFF0) == (cache_line & 0xFFFFFFF0);
}

void add_lru() {
  for (int i = 0; i < 4; i++) {
    if (valid[i])
      lru[i]++;
  }
}

bool find_cache(uint32_t address) {
  for (int i = 0; i < 4; i++) {
    if (valid[i] && match_addr(address, cache[i])) {
      add_lru();
      lru[i] = 0; // Reset LRU counter for the hit cache line
      fprintf(stderr, "Cache hit at slot %d.\n", i);
      return true;
    }
  }

  return false;
}

void replace_cache(uint32_t address) {
  for (int i = 0; i < 4; i++) {
    if (!valid[i]) {
      fprintf(stderr, "Cold cache miss at slot %d.\n", i);
      cache[i] = address;
      valid[i] = true;
      add_lru();
      lru[i] = 0;
      return;
    }
  }

  // Replace the least recently used cache line
  int lru_index = 0;
  for (int i = 1; i < 4; i++) {
    if (lru[i] > lru[lru_index])
      lru_index = i;
  }
  cache[lru_index] = address;
  add_lru();
  lru[lru_index] = 0;
  fprintf(stderr, "Cache miss for address 0x%x, replacement slot %d.\n",
          address, lru_index);
}

void add_inst_access(uint32_t address) {
  fprintf(stderr, "Find cache slot for address 0x%x.\n", address);
  total_access++;

  if (find_cache(address))
    inst_hit++;
  else
    replace_cache(address);
}

void add_data_access(uint32_t address) {
  fprintf(stderr, "Data memory access at 0x%x.\n", address);
  fprintf(stderr, "Find cache slot for address 0x%x.\n", address);
  total_access++;

  if (find_cache(address))
    data_hit++;
  else
    replace_cache(address);
}

void print_cache_statistics() {
  printf("Total memory accesses: %d.\n", total_access);
  printf("Instruction cache hit: %d.\n", inst_hit);
  printf("Data cache hit: %d.\n", data_hit);
  printf("Total cache misses: %d.\n", total_access - inst_hit - data_hit);
}
