#ifndef _CS110_HW6_CACHE_H_
#define _CS110_HW6_CACHE_H_
#include <stdint.h>

void init_cache_system();
void add_inst_access(uint32_t);
void add_data_access(uint32_t);
void print_cache_statistics();

#endif
