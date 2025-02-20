#include <stdint.h>
#include <stdio.h>
#include <time.h>

#define Print(type) printf("Size of " #type " is %lu\n", sizeof(type))

// gcc -m64 'Ex5_64.c' -o 'Ex5_64' -Wpedantic -Wall -Wextra -Wvla -Werror
// -std=c11

int main(void) {
  Print(char);
  Print(short);
  Print(short int);
  Print(int);
  Print(long int);
  Print(unsigned int);
  Print(void *);
  Print(size_t);
  Print(float);
  Print(double);
  Print(int8_t);
  Print(int16_t);
  Print(int32_t);
  Print(int64_t);
  Print(time_t);
  Print(clock_t);
  Print(struct tm);
  Print(NULL);
  Print(struct {
    int a;
    short b;
  });
  return 0;
}