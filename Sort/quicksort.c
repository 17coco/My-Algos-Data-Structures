//
// Created by Zihan Xu on 2024/4/4.
//
#include "macros.h"
#include "logger.h"
#include <stdlib.h>
#include "quicksort.h"

// Utility function to swap tp integers
void swap(int *i, int *j) {
  int temp;
  temp = *i;
  *i = *j;
  *j = temp;
#ifdef LOG
  //3 assignments
  logger_add();
  logger_add();
  logger_add();
#endif
}

//Make everything less than pivot in its right
// and everything larger than pivot in its left
int partition(int *A, int size, int pivot) {
  //swapping pivot with the last
  swap(&A[size - 1], &A[pivot]);
#ifdef LOG
  //call to a function and subtraction
        logger_add();
        logger_add();
        logger_add();
#endif
  int i = 0;
  int j = size - 1;
#ifdef LOG
  //2 assignments
        logger_add();
        logger_add();
#endif
  while (i < j) {
    while (i <= size - 1 && A[i] < A[size - 1]) {
      //search from left for an element larger than pivot
      i++; //i will always land on a integer no less than pivot
    }
#ifdef LOG
    //3 comparisons 3 operations
        logger_add();
        logger_add();
        logger_add();
        logger_add();
        logger_add();
        logger_add();
#endif
    while (j >= 0 && A[j] >= A[size - 1]) {
      //search from right for an element less than pivot
      j--;
    }
#ifdef LOG
    //2 comparisons 2 operations
        logger_add();
        logger_add();
        logger_add();
        logger_add();
#endif
    if (i < j) { //swap i and j
#ifdef LOG
        logger_add();
#endif
      swap(&A[i], &A[j]);
      // now larger elements goes right and vice versa
#ifdef LOG
      //call to a function
        logger_add();
        logger_add();
#endif
    }
  }
  //swap i and last pivot()
  // put pivot in the "middle"
  swap(&A[i], &A[size - 1]);
#ifdef LOG
  //call to a function and an operation
        logger_add();
        logger_add();
        logger_add();
#endif
#ifdef LOG
  //return
        logger_add();
#endif
  return i;
}

//sort an array using quicksort
void quicksort(int *A, int size) {
#ifdef LOG
  logger_add();
#endif
  if (size > 1) {
    //get a random pivot
    srand(200);
#ifdef LOG
    //call to a function
    logger_add();
    logger_add();
#endif
    int pivot = rand() % (size - 1);
#ifdef LOG
    //call to a function
    //operation
    logger_add();
    logger_add();
    logger_add();
#endif
    // partition and get pivot
    pivot = partition(A, size, pivot);
#ifdef LOG
    //call to a function
    //assign
    logger_add();
    logger_add();
    logger_add();
#endif
    // divide and go on
    quicksort(A, pivot);
    quicksort(A + pivot + 1, size - pivot - 1);
#ifdef LOG
    //call to 2 function and 2 operations
    logger_add();
    logger_add();
    logger_add();
    logger_add();
    logger_add();
    logger_add();
#endif
  }
}
