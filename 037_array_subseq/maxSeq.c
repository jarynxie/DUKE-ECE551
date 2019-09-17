#include <stdio.h>
#include <stdlib.h>

size_t maxSeq_helper(int * curLoc, size_t curMax) {
  size_t returnMax = curMax;
  if (*curLoc <= *(curLoc - 1)) {
    returnMax = 1;
  }
  else {
    returnMax++;
  }
  return returnMax;
}

size_t maxCal(size_t a, size_t b) {
  return a > b ? a : b;
}

size_t maxSeq(int * array, size_t n) {
  if (n == 0) {
    return 0;
  }
  size_t max = 1;
  size_t curMax = 1;
  for (size_t i = 1; i < n; i++) {
    curMax = maxSeq_helper(array + i, curMax);
    max = maxCal(curMax, max);
  }
  return max;
}
