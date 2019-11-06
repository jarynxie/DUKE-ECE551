#include <cstdio>
#include <cstdlib>

#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  if (low == high || high - low == 1) {
    return low;
  }
  int middle = low + (high - low) / 2;
  int fx = f->invoke(middle);
  if (fx <= 0) {
    return binarySearchForZero(f, middle, high);
  }
  else {
    return binarySearchForZero(f, low, middle);
  }
  return low;
}
