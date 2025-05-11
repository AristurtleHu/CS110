#include <emmintrin.h> /* header file for the SSE intrinsics */
#include <math.h>
#include <stdio.h>
#include <time.h>

float **a;
float **b;
float **c;
float **c2;

int n = 10000;
int p = 8000;

void init(void) {
  a = malloc(n * sizeof(float *));
  b = malloc(4 * sizeof(float *));
  c = malloc(n * sizeof(float *));
  c2 = malloc(n * sizeof(float *));
  for (int i = 0; i < n; ++i) {
    a[i] = malloc(4 * sizeof(float));
    c[i] = malloc(p * sizeof(float));
    c2[i] = malloc(p * sizeof(float));
  }
  for (int i = 0; i < 4; ++i) {
    b[i] = malloc(p * sizeof(float));
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < 4; ++j) {
      a[i][j] = (float)rand() / (float)RAND_MAX;
    }
  }

  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < p; ++j) {
      b[i][j] = (float)rand() / (float)RAND_MAX;
    }
  }
}

void check_correctness(char *msg) {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < p; ++j) {
      if (fabs(c[i][j] - c2[i][j]) > 1 / 1e6) {
        printf("%s incorrect!\n", msg);
        return;
      }
    }
  }
}

void naive_matmul(void) {
  struct timespec start, end;
  clock_gettime(CLOCK_MONOTONIC, &start);

  // c = a * b
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < p; ++j) {
      c[i][j] = 0;
      for (int k = 0; k < 4; ++k) {
        c[i][j] += a[i][k] * b[k][j];
      }
    }
  }
  clock_gettime(CLOCK_MONOTONIC, &end);
  printf("naive: %f\n",
         (float)(end.tv_sec - start.tv_sec) +
             (float)(end.tv_nsec - start.tv_nsec) / 1000000000.0f);
}

void loop_unroll_matmul(void) {
  struct timespec start, end;
  clock_gettime(CLOCK_MONOTONIC, &start);

  // c2 = a * b
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < p; ++j) {
      c2[i][j] = 0;
      c2[i][j] += a[i][0] * b[0][j];
      c2[i][j] += a[i][1] * b[1][j];
      c2[i][j] += a[i][2] * b[2][j];
      c2[i][j] += a[i][3] * b[3][j];
    }
  }
  clock_gettime(CLOCK_MONOTONIC, &end);
  printf("unroll: %f\n",
         (float)(end.tv_sec - start.tv_sec) +
             (float)(end.tv_nsec - start.tv_nsec) / 1000000000.0f);
  check_correctness("loop_unroll_matmul");
}

void simd_matmul(void) {
  struct timespec start, end;
  clock_gettime(CLOCK_MONOTONIC, &start);

  // c2 = a * b
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < p; j += 4) {
      __m128 sum_vec = _mm_setzero_ps();
      for (int k = 0; k < 4; ++k) {
        // Load a[i][k] and broadcast it to all four elements
        __m128 val_a_ik = _mm_set1_ps(a[i][k]);

        // b[k][j], b[k][j+1], b[k][j+2], b[k][j+3]
        __m128 row_b_kj = _mm_loadu_ps(&b[k][j]);

        sum_vec = _mm_add_ps(sum_vec, _mm_mul_ps(val_a_ik, row_b_kj));
      }
      // Store the four computed results into c2[i][j] through c2[i][j+3]
      _mm_storeu_ps(&c2[i][j], sum_vec);
    }
  }
  clock_gettime(CLOCK_MONOTONIC, &end);
  printf("simd: %f\n",
         (float)(end.tv_sec - start.tv_sec) +
             (float)(end.tv_nsec - start.tv_nsec) / 1000000000.0f);
  check_correctness("simd_matmul");
}

void loop_unroll_simd_matmul(void) {
  struct timespec start, end;
  clock_gettime(CLOCK_MONOTONIC, &start);

  // c2 = a * b
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < p; j += 4) {
      __m128 sum_vec = _mm_setzero_ps();

      // k = 0
      __m128 val_a_i0 = _mm_set1_ps(a[i][0]);
      __m128 row_b_0j = _mm_loadu_ps(&b[0][j]);
      sum_vec = _mm_add_ps(sum_vec, _mm_mul_ps(val_a_i0, row_b_0j));

      // k = 1
      __m128 val_a_i1 = _mm_set1_ps(a[i][1]);
      __m128 row_b_1j = _mm_loadu_ps(&b[1][j]);
      sum_vec = _mm_add_ps(sum_vec, _mm_mul_ps(val_a_i1, row_b_1j));

      // k = 2
      __m128 val_a_i2 = _mm_set1_ps(a[i][2]);
      __m128 row_b_2j = _mm_loadu_ps(&b[2][j]);
      sum_vec = _mm_add_ps(sum_vec, _mm_mul_ps(val_a_i2, row_b_2j));

      // k = 3
      __m128 val_a_i3 = _mm_set1_ps(a[i][3]);
      __m128 row_b_3j = _mm_loadu_ps(&b[3][j]);
      sum_vec = _mm_add_ps(sum_vec, _mm_mul_ps(val_a_i3, row_b_3j));

      // Store the four computed results into c2[i][j] through c2[i][j+3]
      _mm_storeu_ps(&c2[i][j], sum_vec);
    }
  }
  clock_gettime(CLOCK_MONOTONIC, &end);
  printf("unroll+simd: %f\n",
         (float)(end.tv_sec - start.tv_sec) +
             (float)(end.tv_nsec - start.tv_nsec) / 1000000000.0f);
  check_correctness("loop_unroll_simd_matmul");
}

void deallocate() {
  for (int i = 0; i < n; ++i) {
    free(a[i]);
    free(c[i]);
    free(c2[i]);
  }
  for (int i = 0; i < 4; ++i) {
    free(b[i]);
  }
  free(a);
  free(b);
  free(c);
  free(c2);
  a = NULL;
  b = NULL;
  c = NULL;
  c2 = NULL;
}

int main(void) {
  init();

  naive_matmul();
  simd_matmul();
  loop_unroll_matmul();
  loop_unroll_simd_matmul();

  deallocate();
  return 0;
}
