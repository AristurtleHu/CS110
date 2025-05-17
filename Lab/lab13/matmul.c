#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define MATRIX_SIZE 1024
#define EPSILON 1e-8

// Return the max symmetric relative error between matrices x and y
double rel_err(double *x, double *y) {
  double max_rel_err = 0.0;
  for (int i = 0; i < MATRIX_SIZE; i++) {
    for (int j = 0; j < MATRIX_SIZE; j++) {
      int idx = i * MATRIX_SIZE + j;
      double diff_abs = fabs(x[idx] - y[idx]);
      double abs_sum = fabs(x[idx]) + fabs(y[idx]);
      if (abs_sum < EPSILON) {
        abs_sum = EPSILON;
      }
      double rel_err = diff_abs / abs_sum;
      if (rel_err > EPSILON && rel_err > max_rel_err) {
        max_rel_err = rel_err;
      }
    }
  }
  return max_rel_err;
}

int sanity_check(double *x, double *ref) {
  double e = rel_err(x, ref);
  int pass = (e <= EPSILON);
  printf("\tMax relative error: %e. Sanity check %s\n", e,
         pass ? "PASS" : "FAIL");
  return pass;
}

void init_mat(double *x) {
  for (int i = 0; i < MATRIX_SIZE; i++) {
    for (int j = 0; j < MATRIX_SIZE; j++) {
      int idx = i * MATRIX_SIZE + j;
      x[idx] = (double)rand() / RAND_MAX;
    }
  }
}

void reset_mat(double *x) {
  for (int i = 0; i < MATRIX_SIZE; i++) {
    for (int j = 0; j < MATRIX_SIZE; j++) {
      int idx = i * MATRIX_SIZE + j;
      x[idx] = 0.0;
    }
  }
}

void matmul_serial(double *a, double *b, double *c) {
  for (int i = 0; i < MATRIX_SIZE; i++) {
    for (int j = 0; j < MATRIX_SIZE; j++) {
      for (int k = 0; k < MATRIX_SIZE; k++) {
        c[i * MATRIX_SIZE + j] +=
            a[i * MATRIX_SIZE + k] * b[k * MATRIX_SIZE + j];
      }
    }
  }
}

// Task 1
void matmul_omp_slices(double *a, double *b, double *c) {
#pragma omp parallel
  {
    for (int i = 0; i < MATRIX_SIZE; i++) {
      if (i % omp_get_num_threads() == omp_get_thread_num()) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
          for (int k = 0; k < MATRIX_SIZE; k++) {
            c[i * MATRIX_SIZE + j] +=
                a[i * MATRIX_SIZE + k] * b[k * MATRIX_SIZE + j];
          }
        }
      }
    }
  }
}

// Task 2
void matmul_omp_chunks(double *a, double *b, double *c) {
#pragma omp parallel
  {
    int num_threads = omp_get_num_threads();
    int tid = omp_get_thread_num();

    // Determine the contiguous chunk of rows for this thread.
    // This distributes rows as evenly as possible.
    int start_row = (tid * MATRIX_SIZE) / num_threads;
    int end_row = ((tid + 1) * MATRIX_SIZE) / num_threads;

    for (int i = start_row; i < end_row; i++) {
      for (int j = 0; j < MATRIX_SIZE; j++) {
        for (int k = 0; k < MATRIX_SIZE; k++) {
          c[i * MATRIX_SIZE + j] +=
              a[i * MATRIX_SIZE + k] * b[k * MATRIX_SIZE + j];
        }
      }
    }
  }
}

int main() {
  double *a = (double *)malloc(MATRIX_SIZE * MATRIX_SIZE * sizeof(double));
  double *b = (double *)malloc(MATRIX_SIZE * MATRIX_SIZE * sizeof(double));
  double *c = (double *)calloc(MATRIX_SIZE * MATRIX_SIZE, sizeof(double));
  double *serial_result =
      (double *)calloc(MATRIX_SIZE * MATRIX_SIZE, sizeof(double));

  if (!a || !b || !c || !serial_result) {
    free(a);
    free(b);
    free(c);
    free(serial_result);
    printf("Error: could not allocate memory.\n");
    return 1;
  }

  init_mat(a);
  init_mat(b);

  double start_time = omp_get_wtime();
  matmul_serial(a, b, serial_result);
  double end_time = omp_get_wtime();
  printf("Serial: %.5f seconds\n", end_time - start_time);

  printf("Max threads: %d\n", omp_get_max_threads());
  start_time = omp_get_wtime();
  matmul_omp_slices(a, b, c);
  end_time = omp_get_wtime();
  printf("Omp slices: %.5f seconds\n", end_time - start_time);
  if (!sanity_check(c, serial_result)) {
    return 1;
  }

  reset_mat(c);
  start_time = omp_get_wtime();
  matmul_omp_chunks(a, b, c);
  end_time = omp_get_wtime();
  printf("Omp chunks: %.5f seconds\n", end_time - start_time);
  if (!sanity_check(c, serial_result)) {
    return 1;
  }

  free(a);
  free(b);
  free(c);
  free(serial_result);
  return 0;
}
