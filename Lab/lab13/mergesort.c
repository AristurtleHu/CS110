#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_SIZE 10000000
#define CUT_OFF 1000000

// Check if arr is in ascending order
int is_asc(int *arr) {
  for (int i = 0; i < ARRAY_SIZE - 1; i++) {
    if (arr[i] > arr[i + 1]) {
      printf("\tSanity check FAIL. "
             "Array is not ascending: %d (at %d) > %d (at %d)\n",
             arr[i], i, arr[i + 1], i + 1);
      return 0;
    }
  }
  printf("\tSanity check PASS.\n");
  return 1;
}

// Merges two subarrays of arr: arr[left..mid] and arr[mid+1..right]
void merge(int *arr, int left, int mid, int right) {
  int left_size = mid - left + 1;
  int right_size = right - mid;

  int *left_sub_arr = (int *)malloc(left_size * sizeof(int));
  int *right_sub_arr = (int *)malloc(right_size * sizeof(int));

  if (!left_sub_arr || !right_sub_arr) {
    printf("Error: could not allocate memory\n");
    free(left_sub_arr);
    free(right_sub_arr);
    return;
  }

  // copy data to tmp arrays
  memcpy(left_sub_arr, arr + left, left_size * sizeof(int));
  memcpy(right_sub_arr, arr + mid + 1, right_size * sizeof(int));

  // merge tmp arrays back
  int i = 0, j = 0, k = left;
  while (i < left_size && j < right_size) {
    if (left_sub_arr[i] <= right_sub_arr[j]) {
      arr[k++] = left_sub_arr[i++];
    } else {
      arr[k++] = right_sub_arr[j++];
    }
  }

  // copy the remaining elements if there are any
  while (i < left_size) {
    arr[k++] = left_sub_arr[i++];
  }
  while (j < right_size) {
    arr[k++] = right_sub_arr[j++];
  }

  free(left_sub_arr);
  free(right_sub_arr);
}

// arr[left...right] is to be sorted
void merge_sort_serial_recursive(int *arr, int left, int right) {
  if (left < right) {
    int mid = left + (right - left) / 2;
    merge_sort_serial_recursive(arr, left, mid);
    merge_sort_serial_recursive(arr, mid + 1, right);
    merge(arr, left, mid, right);
  }
}

void merge_sort_serial(int *arr) {
  merge_sort_serial_recursive(arr, 0, ARRAY_SIZE - 1);
}

// Your task
void merge_sort_omp_tasks_recursive(int *arr, int left, int right) {
  // Part 2:
  // For small array, just call the serial version to avoid creating too many
  // tasks.

  if (right - left < CUT_OFF) {
    merge_sort_serial_recursive(arr, left, right);
    return;
  }

  // Part 3:
  // Start two sort tasks to sort two subarrays by using `#pragma omp task`,
  // "wait" until they are sorted, and then merge them. i.e., you should use
  // `#pragma omp taskwait` before `merge`.
  // What if we do not wait for child tasks? Try it out.
  // You can also try `#pragma omp barrier` and think why it does not work.

  int mid = left + (right - left) / 2;

#pragma omp task
  {
    merge_sort_omp_tasks_recursive(arr, left, mid);
  }

#pragma omp task
  {
    merge_sort_omp_tasks_recursive(arr, mid + 1, right);
  }

#pragma omp taskwait

  merge(arr, left, mid, right);
  return;
}

// Your task
void merge_sort_omp_tasks(int *arr) {
  // Part 1:
  // Create a parallel region. In the parallel region, use ONLY ONE thread to
  // start the first sort process. For that thread, directly call (or create a
  // task of) `merge_sort_omp_tasks_recursive` is applicable. That thread, by
  // default, will be blocked until the overall sort finished. To get it
  // involved with recursive sort, you can add `nowait` clause

#pragma omp parallel
  {
#pragma omp single nowait
    {
      merge_sort_omp_tasks_recursive(arr, 0, ARRAY_SIZE - 1);
    }
  }
}

int main() {
  int *arr = (int *)malloc(ARRAY_SIZE * sizeof(int));
  int *arr_copy = (int *)malloc(ARRAY_SIZE * sizeof(int));
  for (int i = 0; i < ARRAY_SIZE; i++) {
    arr[i] = rand() % ARRAY_SIZE;
  }
  memcpy(arr_copy, arr, ARRAY_SIZE * sizeof(int));

  double start = omp_get_wtime();
  merge_sort_serial(arr);
  double end = omp_get_wtime();
  printf("Serial: %.5f seconds\n", end - start);
  if (!is_asc(arr)) {
    return 1;
  }

  memcpy(arr, arr_copy, ARRAY_SIZE * sizeof(int));
  printf("Max threads: %d\n", omp_get_max_threads());
  start = omp_get_wtime();
  merge_sort_omp_tasks(arr);
  end = omp_get_wtime();
  printf("Omp tasks: %.5f seconds\n", end - start);
  if (!is_asc(arr)) {
    return 1;
  }

  free(arr);
  free(arr_copy);
  return 0;
}