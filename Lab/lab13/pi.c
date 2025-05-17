#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_STEPS 10000000
#define EPSILON 1e-8
#define REPEAT 100

// Symmetric relative error
double rel_err(double x, double y) {
  double diff_abs = fabs(x - y);
  double abs_sum = fabs(x + y);
  if (abs_sum < EPSILON) {
    abs_sum = EPSILON;
  }
  return diff_abs / abs_sum;
}

int sanity_check(double x, double ref) {
  double e = rel_err(x, ref);
  int pass = (e <= EPSILON);
  printf("\tRelative error: %e. Sanity check %s\n", e, pass ? "PASS" : "FAIL");
  return pass;
}

double pi_serial() {
  double step = 1.0 / NUM_STEPS;
  double sum = 0.0;
  for (int i = 0; i < NUM_STEPS; i++) {
    double x = (i + 0.5) * step;
    sum += 4.0 / (1.0 + x * x);
  }
  return step * sum;
}

double pi_omp_naive() {
  double step = 1.0 / NUM_STEPS;
  double sum = 0.0;
#pragma omp parallel for
  for (int i = 0; i < NUM_STEPS; i++) {
    double x = (i + 0.5) * step;
#pragma omp critical
    sum += 4.0 / (1.0 + x * x);
  }
  return step * sum;
}

// Task 1
double pi_omp_opt() {
  double step = 1.0 / NUM_STEPS;
  double sum = 0.0;
#pragma omp parallel
  {
    double sum_local = 0.0;
#pragma omp for
    for (int i = 0; i < NUM_STEPS; i++) {
      double x = (i + 0.5) * step;
      sum_local += 4.0 / (1.0 + x * x);
    }
#pragma omp critical
    sum += sum_local;
  }
  return step * sum;
}

// Task 2
double pi_omp_reduction() {
  double step = 1.0 / NUM_STEPS;
  double sum = 0.0;
#pragma omp parallel for reduction(+ : sum)
  for (int i = 0; i < NUM_STEPS; i++) {
    double x = (i + 0.5) * step;
    sum += 4.0 / (1.0 + x * x);
  }
  return step * sum;
}

int main() {
  double serial_result, omp_naive_result, omp_opt_result, omp_reduction_result;
  double start_time, end_time;

  int max_threads = omp_get_max_threads();

  start_time = omp_get_wtime();
  serial_result = pi_serial();
  end_time = omp_get_wtime();
  printf("Serial: %.5f seconds. PI: %.9f\n", end_time - start_time,
         serial_result);

  omp_set_num_threads(max_threads);
  start_time = omp_get_wtime();
  omp_naive_result = pi_omp_naive();
  end_time = omp_get_wtime();
  printf("Omp naive: %d thread(s). %.5f seconds. PI: %.9f\n", max_threads,
         end_time - start_time, omp_naive_result);
  if (!sanity_check(omp_naive_result, serial_result)) {
    return 1;
  }

  for (int i = 1; i <= max_threads; i++) {
    omp_set_num_threads(i);
    double elaspsed_time = 0.0;
    for (int r = 0; r < REPEAT; r++) {
      start_time = omp_get_wtime();
      omp_opt_result = pi_omp_opt();
      end_time = omp_get_wtime();
      elaspsed_time += end_time - start_time;
    }
    printf("Omp optimized: %d thread(s). %.5f seconds. PI: %.9f\n", i,
           elaspsed_time / REPEAT, omp_opt_result);
    if (!sanity_check(omp_opt_result, serial_result)) {
      return 1;
    }
  }

  for (int i = 1; i <= max_threads; i++) {
    omp_set_num_threads(i);
    double elaspsed_time = 0.0;
    for (int r = 0; r < REPEAT; r++) {
      start_time = omp_get_wtime();
      omp_reduction_result = pi_omp_reduction();
      end_time = omp_get_wtime();
      elaspsed_time += end_time - start_time;
    }
    printf("Omp reduction: %d thread(s). %.5f seconds. PI: %.9f\n", i,
           elaspsed_time / REPEAT, omp_reduction_result);
    if (!sanity_check(omp_reduction_result, serial_result)) {
      return 1;
    }
  }

  return 0;
}
