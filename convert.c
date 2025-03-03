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

enum type { normal, subnormal, zero, nan, inf };

const char *getTypeName(enum type type) {
  switch (type) {
  case normal:
    return "normal";
  case subnormal:
    return "subnormal";
  case zero:
    return "zero";
  case nan:
    return "nan";
  case inf:
    return "inf";
  }
  return NULL;
}

int main(void) {
  unsigned long long input;
  while (scanf("%llx", &input) != EOF) {
    ca25 ca25;
    ca25.sign = input >> 63;
    ca25.exponent = input >> 31 & 0xFFFFFFFF;
    ca25.mantissa = input & 0x7FFFFFFF;

    int implicit = ca25.exponent == 0 ? 0 : 1;

    enum type type = normal;
    if (implicit == 0)
      type = ca25.mantissa == 0 ? zero : subnormal;
    else if (ca25.exponent == (int)0xFFFFFFFF)
      type = ca25.mantissa == 0 ? inf : nan;

    printf("ca25 S=%d E=%08x M=%d.%08x %s\n", ca25.sign, ca25.exponent,
           implicit, ca25.mantissa << 1, getTypeName(type));

    fp32 fp32 = convert(ca25);

    printf("fp32 S=%d E=%02x M=%d.%06x %s\n", fp32.sign, fp32.exponent,
           implicit, fp32.mantissa, getTypeName(type));
  }

  return 0;
}
