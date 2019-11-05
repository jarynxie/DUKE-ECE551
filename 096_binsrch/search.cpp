#include <cstdio>
#include <cstdlib>

#include "function.h"

int searchHelper(Function<int, int> * f, int low, int high) {
  int curr = (low + high) / 2;
  if (f->invoke(curr) == 0) {
    return curr;
  }
  if (f->invoke(curr) > 0) {
    return searchHelper(f, low, curr);
  }
  if (f->invoke(curr) < 0) {
    return searchHelper(f, curr + 1, high);
  }
  return low;
}

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  if (low == high || high - low == 1 || low > high) {
    return low;
  }
  if (f->invoke(high) < 0) {
    return high - 1;
  }
  if (f->invoke(low) > 0) {
    return low;
  }
  return searchHelper(f, low, high);
}
