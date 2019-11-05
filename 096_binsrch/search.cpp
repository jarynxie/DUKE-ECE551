#include <cstdio>
#include <cstdlib>

#include "function.h"

int searchHelper(Function<int, int> * f, int low, int high) {
  int curr = (low + high) / 2;
  int ans;
  if (f->invoke(curr) == 0) {
    ans = curr;
  }
  if (f->invoke(curr) > 0) {
    ans = searchHelper(f, low, curr - 1);
  }
  if (f->invoke(curr) < 0) {
    ans = searchHelper(f, curr + 1, high);
  }
  return ans;
}

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  if (f->invoke(high) < 0) {
    return high - 1;
  }
  if (f->invoke(low) > 0) {
    return low;
  }
  return searchHelper(f, low, high - 1);
}
