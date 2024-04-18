//
// Created by Zihan Xu on 2024/4/5.
//
#include "quicksort.h"
#include "stdlib.h"
#include "macros.h"
#include "logger.h"

void insertionsort(int *A, int size) {

  int i = 1;
#ifdef LOG
  logger_add();
#endif
  int j;
#ifdef LOG
  logger_add();
#endif
  while (i < size) {
    j = i;
#ifdef LOG
    logger_add();
#endif
    while (j > 0 && A[j] < A[j - 1]) {
#ifdef LOG
      //two comparisons
      logger_add();
      logger_add();
#endif
      swap(&A[j], &A[j - 1]);
#ifdef LOG
      //call to a function
      logger_add();
      logger_add();
#endif
      j--;
#ifdef LOG
      logger_add();
#endif
    }
    i++;
#ifdef LOG
    logger_add();
#endif
  }
}

void insertion_sort(int *A, int left, int right) {

  int i = left + 1;
#ifdef LOG
  logger_add();
#endif
  int j;
  while (i < right + 1) {
#ifdef LOG
    logger_add();
    logger_add();
#endif
    j = i;
#ifdef LOG
    logger_add();
#endif
    while (j > left && A[j] < A[j - 1]) {
#ifdef LOG
      //two comparisons
      logger_add();
      logger_add();
#endif
      swap(&A[j], &A[j - 1]);
#ifdef LOG
      //call to a function
      logger_add();
      logger_add();
#endif
      j--;
#ifdef LOG
      logger_add();
#endif
    }
    i++;
#ifdef LOG
    logger_add();
#endif
  }
}


