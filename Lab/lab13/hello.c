#include <omp.h>
#include <stdio.h>

int main(void) {
#pragma omp parallel
  {
    int thread_ID = omp_get_thread_num();
    int num_threads = omp_get_num_threads();
    printf("thread %d of %d: hello world\n", thread_ID, num_threads);
  }
  return 0;
}
