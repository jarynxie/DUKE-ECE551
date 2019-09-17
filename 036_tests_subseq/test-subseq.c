#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);
void run_check(int * array, size_t n, unsigned expected_ans) {
  unsigned ans = maxSeq(array, n);
  if (expected_ans != ans) {
    printf("There is an error!\n");
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  int array1[] = {1, 2, 1, 3, 6, 7, 2, 4, 6, 9};
  run_check(array1, 10, 4);

  int array2[] = {0, 0};
  run_check(array2, 2, 1);

  int array3[] = {-1000000008, 1000000000, 1000000005, 1000000006};
  run_check(array3, 4, 4);

  //int array4[] = {};
  //run_check(array4, 0, 0);

  int array5[] = {0};
  run_check(array5, 1, 1);

  int array6[] = {1, 2, 4, 6, 6, 7, 5, 6};
  run_check(array6, 8, 4);

  printf("Nothing goes wrong!\n");
  return EXIT_SUCCESS;
}
