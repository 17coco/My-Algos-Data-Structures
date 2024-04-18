//
// Created by Zihan Xu on 2024/4/6.
//

#include "hybridsort.h"
#include "mergesort.h"
#include "insertionsort.h"
#include "logger.h"
#include "macros.h"

void hybrid(int *A, int size) {
  int turning_point = 10; // this is what I get by empirical data
  int left = 0;
  int right = size - 1;
#ifdef LOG
  logger_add();
  logger_add();
  logger_add();
#endif
  if (left < right) { //base case
#ifdef LOG
    logger_add();
#endif
    int mid = (left + right) / 2;
#ifdef LOG
    logger_add();
    logger_add();
#endif
    if (size < turning_point) {
      // if it's small enough then insertion sort
      insertion_sort(A, left, right);
#ifdef LOG
      //call to 3 functions
  logger_add();
  logger_add();
  logger_add();
  logger_add();
  logger_add();
  logger_add();
#endif
    } else {
      //dividing
      hybrid(A, size - size / 2);
      hybrid(A + mid + 1, size / 2);
      //merge
      merge(A, size - size / 2,
            A + mid + 1, size / 2);
#ifdef LOG
      //call to 3 functions
  logger_add();
  logger_add();
  logger_add();
  logger_add();
  logger_add();
  logger_add();
#endif
    }

  }
}
