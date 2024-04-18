//
// Created by Zihan Xu on 2024/4/8.
//

#include "random_data.h"
#include "stdlib.h"

int *random_data(int n) {
  int *random_arr = (int *) malloc(sizeof(int) * n);
  int i;
  for (i = 0; i < n; i++) {
    random_arr[i] = rand();
  }
  return random_arr;
}