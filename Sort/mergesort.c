//
// Created by Zihan Xu on 2024/4/5.
//

#include <stdlib.h>
#include "mergesort.h"
#include "logger.h"
#include "macros.h"

void merge(int *A,int size1, int *B,int size2) {
  int i = 0;
  int j = 0;
  int k = 0;
#ifdef LOG
  logger_add();
  logger_add();
  logger_add();
#endif

  int *temp = (int *)malloc(sizeof(int) * (size1 + size2)); //temp to store results
#ifdef LOG
  logger_add();
#endif

  while (j < size2) {//while B hasn't run out
#ifdef LOG
    logger_add();
#endif
    //and make sure A doesn't run out
    if (A[i] < B[j] && i < size1) {
#ifdef LOG
      logger_add();
      logger_add();
#endif
      temp[k] = A[i];
      k++;
      i++;
#ifdef LOG
      logger_add();
      logger_add();
      logger_add();
#endif
    } else { //if strings2 is larger or strings1 ran out
      temp[k] = B[j];
      k++;
      j++;
#ifdef LOG
      logger_add();
      logger_add();
      logger_add();
#endif
    }
  }

  while (i < size1) {//right has out but left hasn't

    temp[k] = A[i];
    k++;
    i++;
#ifdef LOG
    logger_add();
    logger_add();
    logger_add();
    logger_add();
#endif
  }

  //since A,B are parts of array
  //and the start of A is also the start of strings
  for (k=0;k<size1+size2;k++) {
    A[k] = temp[k];
#ifdef LOG
    logger_add();
#endif
  }
  free(temp);
#ifdef LOG
  logger_add();
#endif
}

void my_mergesort(int *A,int size) {
  int left = 0;
  int right = size-1;
#ifdef LOG
  logger_add();
  logger_add();
#endif
#ifdef LOG
  logger_add();
#endif
  if (left<right) { //base case
    int mid = (left+right) / 2;
#ifdef LOG
  logger_add();
  logger_add();
#endif

    //dividing
    my_mergesort(A, size - size/2);
    my_mergesort(A + mid+1, size/2);
    //conquering
    merge(A, size - size/2,
          A + mid+1, size/2);
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
