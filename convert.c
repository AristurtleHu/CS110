#include <stdbool.h>
#include <stdio.h>

enum type { normal, subnormal, zero, nan, inf };

typedef struct {
  int sign;              // 1 bit
  unsigned int exponent; // 32 bits >0
  unsigned int mantissa; // 31 bits
  enum type type;
} ca25;

typedef struct {
  int sign;              // 1 bit
  unsigned int exponent; // 8 bits 127-biased
  unsigned int mantissa; // 23 bits
  enum type type;
} fp32;

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

fp32 roundAwayFromZero(ca25 ca25, fp32 fp32) {
  if (fp32.type == normal && (ca25.mantissa & 0xFF)) // round away from zero
    fp32.mantissa++;

  if (fp32.type == subnormal && (ca25.mantissa & 0x1FF)) // round away from zero
    fp32.mantissa++;

  if ((fp32.mantissa << 1) > 0xFFFFFE) { // add the implicit 0 in LSB
    fp32.mantissa = 0;
    fp32.exponent++;

    if (fp32.type == subnormal)
      fp32.type = normal;

    else if (fp32.exponent == 0xFF)
      fp32.type = inf;
  }

  return fp32;
}

// convert ca25 to fp32
fp32 convert(ca25 ca25) {
  fp32 fp32;
  fp32.sign = ca25.sign;
  fp32.type = ca25.type;
  int exp = ca25.exponent - 0x7FFFFFFF;

  if (ca25.type == nan) {
    fp32.exponent = 0xFF;
    fp32.mantissa = ca25.mantissa >> 8;
    return fp32;
  }

  if (ca25.type == inf || exp + 127 >= 0xFF) { // too large for normal
    fp32.type = inf;
    fp32.exponent = 0xFF;
    fp32.mantissa = 0;
    return fp32;
  }

  if (ca25.type == zero) {
    fp32.exponent = 0;
    fp32.mantissa = 0;
    return fp32;
  }

  if (ca25.type == subnormal) { // too small for subnormal
    fp32.exponent = 0;
    fp32.mantissa = 1;
    return fp32;
  }

  if (ca25.type == normal) {
    if (exp + 149 < 0) { // too small for subnormal
      fp32.type = subnormal;
      fp32.exponent = 0;
      fp32.mantissa = 1;
      return fp32;
    }

    else if (exp + 126 < 0) {
      fp32.type = subnormal;
      fp32.exponent = 0;
      fp32.mantissa = 1 << 22; // add the implicit 1
      fp32.mantissa |= ca25.mantissa >> 9;
      fp32 = roundAwayFromZero(ca25, fp32);
      return fp32;
    }

    else {
      fp32.exponent = exp + 127;
      fp32.mantissa = ca25.mantissa >> 8;
      fp32 = roundAwayFromZero(ca25, fp32);
      return fp32;
    }
  }

  return fp32;
}

int main(void) {
  unsigned long long input;
  while (scanf("%llx", &input) != EOF) {
    ca25 ca25;
    ca25.sign = input >> 63;
    ca25.exponent = input >> 31 & 0xFFFFFFFF;
    ca25.mantissa = input & 0x7FFFFFFF;
    ca25.type = normal;

    int implicit = ca25.exponent == 0 ? 0 : 1;

    if (implicit == 0)
      ca25.type = ca25.mantissa == 0 ? zero : subnormal;
    else if (ca25.exponent == 0xFFFFFFFF)
      ca25.type = ca25.mantissa == 0 ? inf : nan;

    printf("ca25 S=%d E=%08x M=%d.%08x %s\n", ca25.sign, ca25.exponent,
           implicit, ca25.mantissa << 1, // one bit redundant, always zero
           getTypeName(ca25.type));

    fp32 fp32 = convert(ca25);
    if (fp32.type == subnormal)
      implicit = 0;
    if (fp32.type == normal)
      implicit = 1;

    printf("fp32 S=%d E=%02x M=%d.%06x %s\n", fp32.sign, fp32.exponent,
           implicit, fp32.mantissa << 1, // one bit redundant, always zero
           getTypeName(fp32.type));

    printf("%08x\n", (fp32.sign << 31) | (fp32.exponent << 23) | fp32.mantissa);
  }

  return 0;
}
