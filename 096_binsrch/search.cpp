#include <cstdio>
#include <cstdlib>

#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  if (f->invoke(high - 1) < 0) {
    return high - 1;
  }
  int curr = (low + high) / 2;
  if (f->invoke(curr) == 0) {
    return curr;
  }
  if (f->invoke(curr) > 0) {
    return binarySearchForZero(f, low, curr);
  }
  if (f->invoke(curr) < 0) {
    return binarySearchForZero(f, curr, high);
  }
  return low;
}
