#ifndef DEBUG_UTIL_H
#define DEBUG_UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define assert_int_eq(actual, expected)                                        \
  do {                                                                         \
    if ((actual) != (expected)) {                                              \
      fprintf(stderr, "Assertion failed: %s:%d expected %d, actual %d\n",      \
              __FILE__, __LINE__, (expected), (actual));                       \
      exit(-1);                                                                \
    }                                                                          \
  } while (0)

#define assert_string_eq(actual, expected)                                     \
  do {                                                                         \
    if (strcmp((actual), (expected)) != 0) {                                   \
      fprintf(stderr, "Assertion failed: %s:%d expected '%s', actual '%s'\n",  \
              __FILE__, __LINE__, (expected), (actual));                       \
      exit(-1);                                                                \
    }                                                                          \
  } while (0)

#define assert_true(condition)                                                 \
  do {                                                                         \
    if (!(condition)) {                                                        \
      fprintf(stderr, "Assertion failed: %s:%d condition is false: %s\n",      \
              __FILE__, __LINE__, #condition);                                 \
      exit(-1);                                                                \
    }                                                                          \
  } while (0)

#endif // DEBUG_UTIL_H
