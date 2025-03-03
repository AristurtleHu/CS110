#include <stdio.h>

typedef struct {
  int sign;     // 1 bit
  int exponent; // 32 bits
  int mantissa; // 31 bits
} ca25;

typedef struct {
  int sign;     // 1 bit
  int exponent; // 8 bits
  int mantissa; // 23 bits
} fp32;

// convert ca25 to fp32
fp32 convert(ca25 ca25) {
  fp32 fp32;
  fp32.sign = ca25.sign;
  fp32.exponent = ca25.exponent + 127;
  fp32.mantissa = ca25.mantissa << 8; // TODO:
  return fp32;
}

int main(void) {
  unsigned long long ca25_hex;
  while (scanf("%llx", &ca25_hex) != EOF) {
    printf("%lld", ca25_hex);
    // ca25 ca25;
    // ca25.sign = (ca25_hex >> 31) & 0x1;
    // ca25.exponent = (ca25_hex >> 30) & 0x3;
    // ca25.mantissa = ca25_hex & 0x3FFFFFFF;

    // fp32 fp32 = convert(ca25);

    // printf("%d %d %d\n", fp32.sign, fp32.exponent, fp32.mantissa);
  }

  return 0;
}
