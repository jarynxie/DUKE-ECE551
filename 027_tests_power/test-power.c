#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);
void run_check(unsigned x, unsigned y, unsigned expected_ans) {
  unsigned ans = power(x, y);
  if (expected_ans != ans) {
    printf("There is an error!\n");
    exit(EXIT_FAILURE);
  }
}
int main(void) {
  run_check(0, 0, 1);
  run_check(0, 1, 0);
  run_check(3, 3, 27);
  //  run_check(-1, 2, 1);
  run_check(10, 0, 1);
  run_check(1, 0, 1);
  // run_check(1, -2, 1);
  // run_check(2, 31, 2147483648);
  exit(EXIT_SUCCESS);
}
