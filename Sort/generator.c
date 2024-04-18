#include <stdio.h>
#include <stdlib.h>
#include "quicksort.h"
#include "mergesort.h"
#include "insertionsort.h"
#include "macros.h"
#include "logger.h"
#include "hybridsort.h"
#include "random_data.h"

#ifdef LOG
extern log_t logger; //the global variable logger used here. "extern" means that this variable is defined elsewhere.
// This makes the compiler happy, although the linker would need to find it.
#endif

// helper to copy array A to  array B
void arr_copy(int *A, int *B, int size) {
  int i;
  for (i = 0; i < size; i++) {
    B[i] = A[i];
  }
}

void get_steps(int size, int seed) {
#ifdef LOG
  logger_reset();
#endif
  srand(seed);
  int i;
  int *arr = random_data(size);
  int arr1[size];
  int arr2[size];
  int arr3[size];
  int arr4[size];
  arr_copy(arr, arr1, size);
  arr_copy(arr, arr2, size);
  arr_copy(arr, arr3, size);
  arr_copy(arr, arr4, size);
  free(arr);


  my_mergesort(arr1, size);
  for (i = 0; i < size - 1; i++) {
    if (arr1[i] > arr1[i + 1]) {
      printf("Wrong order! %d before %d\n", arr2[i], arr2[i + 1]);
    }
  }

#ifdef LOG
  printf("Steps taken by mergesort: %ld\n", logger.num_steps);
  logger_reset();
#endif


  hybrid(arr2, size);

  // check result of hybrid
  for (i = 0; i < size - 1; i++) {
    if (arr2[i] > arr2[i + 1]) {
      printf("Wrong order! %d before %d\n", arr2[i], arr2[i + 1]);
    }
  }

#ifdef LOG
  printf("Steps taken by hybrid sort: %ld\n", logger.num_steps);
  logger_reset();
#endif

  quicksort(arr3, size);
  for (i = 0; i < size - 1; i++) {
    if (arr3[i] > arr3[i + 1]) {
      printf("Wrong order! %d before %d\n", arr2[i], arr2[i + 1]);
    }
  }
#ifdef LOG
  printf("Steps taken by quicksort: %ld\n", logger.num_steps);
  logger_reset();
#endif

  insertionsort(arr4, size);
  for (i = 0; i < size - 1; i++) {
    if (arr4[i] > arr4[i + 1]) {
      printf("Wrong order! %d before %d\n", arr2[i], arr2[i + 1]);
    }
  }
#ifdef LOG
  printf("Steps taken by insertionsort: %ld\n", logger.num_steps);
  logger_reset();
#endif


}

//to pass the auto grader the macro is now turned off
//please turn it on if you wanna try this program
//Also, if you wanna just see some of the four algorithms
//just comment out others
int main() {
  int size[] = {1, 5, 10, 15, 20, 25,
                50, 75, 100, 500, 1000,
                5000, 10000, 50000, 100000,
                500000};
  int seed[] = {100, 200, 300, 400, 500};
  int i;
  int j;
  for (i = 0; i < 16; i++) {
    printf("\n---Getting data for size %d---\n", size[i]);
    for (j = 0; j < 5; j++) {
      printf("---Data set %d---\n", j + 1);
      get_steps(size[i], seed[j]);
    }
  }
}
