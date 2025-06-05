#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

struct node {
  int8_t a;
  uint8_t b;
  short c;
  int d;
};

int main(void) {
  struct node N[3];
  for (int i = 0; i < 3; i++) {
    N[i].a = 0x1f;   // int8_t
    N[i].b = 0xb1;   // uint8_t
    N[i].c = 0x1595; // short
    N[i].d = 0;      // int
  }

  for (int i = 0; i < 3; i++) {
    N[i].d = N[i].a * N[i].b + N[i].c;
    printf("%x", N[i].a * N[i].b);
    printf(" + %x = ", N[i].c);
    printf("%x\n", N[i].d);
  }
}