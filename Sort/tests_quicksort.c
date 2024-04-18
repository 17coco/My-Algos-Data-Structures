//
// Created by Zihan Xu on 2024/4/4.
//

#include "quicksort.h"
#include <stdio.h>
#include <stdlib.h>

//test empty array and one element array
int test_empty_and_one() {
  printf("---Test test_empty_and_one() begin: ---\n");
  int arr1[] = {};
  // should not get exception
  quicksort(arr1, 0);

  int arr2[] = {1};
  quicksort(arr2, 1);
  if (arr2[0] != 1) {
    printf("Something went wrong with sorting array of size 1");
    return 0;
  }
  printf("---Test test_empty_and_one() end: ---\n");
  return 1;
}

//test arrays with all identical entries
int test_all_same() {
  printf("---Test test_all_same() begin: ---\n");
  int i;
  //all same numbers and even size
  int arr3[] = {1, 1, 1, 1, 1, 1};
  quicksort(arr3, 6);
  for (i = 0; i < 5; i++) {
    if (arr3[i] > arr3[i + 1]) {
      printf("wrong!: former: %d, latter: %d\n", arr3[i], arr3[i + 1]);
      return 0;
    }
  }

  //all same numbers and odd size
  int arr4[] = {1, 1, 1, 1, 1, 1,1};
  quicksort(arr4, 7);
  for (i = 0; i < 6; i++) {
    if (arr4[i] > arr4[i + 1]) {
      printf("wrong!: former: %d, latter: %d\n", arr4[i], arr4[i + 1]);
      return 0;
    }
  }

  printf("---Test test_all_same() end: ---\n");
  return 1;
}

//test arrays of even size
int test_even() {
  printf("---Test test_even() begin: ---\n");
  //with duplicate entries
  int i;
  int arr1[] = {3, 8, 2, 6, 4, 4};
  quicksort(arr1, 6);
  for (i = 0; i < 5; i++) {
    if (arr1[i] > arr1[i + 1]) {
      printf("wrong!: former: %d, latter: %d\n", arr1[i], arr1[i + 1]);
      return 0;
    }
  }
  //without duplicate entries and odd size
  int arr2[] = {8, 6, 1, 4, 0, 9};
  quicksort(arr2, 6);
  for (i = 0; i < 5; i++) {
    if (arr2[i] > arr2[i + 1]) {
      printf("wrong!: former: %d, latter: %d\n", arr2[i], arr2[i + 1]);
      return 0;
    }
  }

  printf("---Test test_even() end: ---\n");
  return 1;
}

//test arrays of odd size
int test_odd() {
  printf("---Test test_odd() begin: ---\n");
  //with duplicate entries
  int i;
  int arr1[] = {3, 8, 2, 6, 4, 0, 0};
  quicksort(arr1, 7);
  for (i = 0; i < 6; i++) {
    if (arr1[i] > arr1[i + 1]) {
      printf("wrong!: former: %d, latter: %d\n", arr1[i], arr1[i + 1]);
      return 0;
    }
  }
  //without duplicate entries
  int arr2[] = {8, 6, 1, 4, 0, 9, 7};
  quicksort(arr2, 7);
  for (i = 0; i < 6; i++) {
    if (arr2[i] > arr2[i + 1]) {
      printf("wrong!: former: %d, latter: %d\n", arr2[i], arr2[i + 1]);
      return 0;
    }
  }
  printf("---Test test_odd() end: ---\n");
  return 1;
}

//test large random arrays
int test_large() {
  printf("---Test test_large() end: ---\n");
  int i;
  int B[1000];
  for (i = 0; i < 1000; i++) {
    B[i] = rand() % 1000;
  }

  quicksort(B, 1000);

  for (i = 0; i < 999; i++) {
    if (B[i] > B[i + 1]) {
      printf("wrong!: former: %d, latter: %d\n", B[i], B[i + 1]);
      return 0;
    }
  }
  printf("---Test test_large() end: ---\n");
  return 1;
}

int main() {
  int tested = 5;
  int success = 0;
  success += test_empty_and_one();
  success += test_odd();
  success += test_even();
  success += test_all_same();
  success += test_large();
  printf("Ran %d tests, %d successful, %d failed\n----\n",
         tested, success, tested - success);


}