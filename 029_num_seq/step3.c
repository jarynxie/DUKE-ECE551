// This file is for Step 3.
// You should do
//  Step 3 (A): write seq3
//  Step 3 (B): write main to test seq3
//  Step 3 (C): write countEvenInSeq3Range
//  Step 3 (D): add test cases to main to test countEvenInSeq3Range
//
// Be sure to #include any header files you need!

#include <stdio.h>
#include <stdlib.h>

int seq3(int x, int y) {
  return 2 * y + (y - 3) * x;
}

int countEvenInSeq3Range(int xLow, int xHi, int yLow, int yHi) {
  if (xLow >= xHi || yLow >= yHi) {
    return 0;
  }
  int countEven = 0;
  for (int x = xLow; x < xHi; x++) {
    for (int y = yLow; y < yHi; y++) {
      if (seq3(x, y) % 2 == 0) {
        countEven++;
      }
    }
  }
  return countEven;
}

int main(void) {
  //test step1
  int seq3X = 0;
  int seq3Y = 0;
  int seq3Result = 0;

  seq3Result = seq3(seq3X, seq3Y);
  printf("seq3(%d, %d) = %d\n", seq3X, seq3Y, seq3Result);

  seq3X = 1;
  seq3Y = 0;
  seq3Result = seq3(seq3X, seq3Y);
  printf("seq3(%d, %d) = %d\n", seq3X, seq3Y, seq3Result);

  seq3X = 100000000;
  seq3Y = 0;
  seq3Result = seq3(seq3X, seq3Y);
  printf("seq3(%d, %d) = %d\n", seq3X, seq3Y, seq3Result);

  seq3X = 0;
  seq3Y = 1;
  seq3Result = seq3(seq3X, seq3Y);
  printf("seq3(%d, %d) = %d\n", seq3X, seq3Y, seq3Result);

  seq3X = 0;
  seq3Y = 100000000;
  seq3Result = seq3(seq3X, seq3Y);
  printf("seq3(%d, %d) = %d\n", seq3X, seq3Y, seq3Result);

  seq3X = 1;
  seq3Y = 1;
  seq3Result = seq3(seq3X, seq3Y);
  printf("seq3(%d, %d) = %d\n", seq3X, seq3Y, seq3Result);

  seq3X = 100000000;
  seq3Y = 100000000;
  seq3Result = seq3(seq3X, seq3Y);
  printf("seq3(%d, %d) = %d\n", seq3X, seq3Y, seq3Result);

  seq3X = 1;
  seq3Y = -1;
  seq3Result = seq3(seq3X, seq3Y);
  printf("seq3(%d, %d) = %d\n", seq3X, seq3Y, seq3Result);

  seq3X = 100000000;
  seq3Y = -100000000;
  seq3Result = seq3(seq3X, seq3Y);
  printf("seq3(%d, %d) = %d\n", seq3X, seq3Y, seq3Result);

  seq3X = -1;
  seq3Y = 1;
  seq3Result = seq3(seq3X, seq3Y);
  printf("seq3(%d, %d) = %d\n", seq3X, seq3Y, seq3Result);

  seq3X = -10000000;
  seq3Y = 100000000;
  seq3Result = seq3(seq3X, seq3Y);
  printf("seq3(%d, %d) = %d\n", seq3X, seq3Y, seq3Result);

  seq3X = -1;
  seq3Y = -1;
  seq3Result = seq3(seq3X, seq3Y);
  printf("seq3(%d, %d) = %d\n", seq3X, seq3Y, seq3Result);

  seq3X = -100000000;
  seq3Y = -100000000;
  seq3Result = seq3(seq3X, seq3Y);
  printf("seq3(%d, %d) = %d\n", seq3X, seq3Y, seq3Result);

  //test step3
  int xLow = 0;
  int xHi = 0;
  int yLow = 0;
  int yHi = 0;
  int countEven = 0;

  countEven = countEvenInSeq3Range(xLow, xHi, yLow, yHi);
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n", xLow, xHi, yLow, yHi, countEven);

  xLow = 3;
  xHi = 2;
  yLow = 0;
  yHi = 3;
  countEven = countEvenInSeq3Range(xLow, xHi, yLow, yHi);
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n", xLow, xHi, yLow, yHi, countEven);

  xLow = 0;
  xHi = 2;
  yLow = 4;
  yHi = 3;
  countEven = countEvenInSeq3Range(xLow, xHi, yLow, yHi);
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n", xLow, xHi, yLow, yHi, countEven);

  xLow = 3;
  xHi = 2;
  yLow = 4;
  yHi = 3;
  countEven = countEvenInSeq3Range(xLow, xHi, yLow, yHi);
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n", xLow, xHi, yLow, yHi, countEven);

  xLow = 0;
  xHi = 2;
  yLow = 0;
  yHi = 3;
  countEven = countEvenInSeq3Range(xLow, xHi, yLow, yHi);
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n", xLow, xHi, yLow, yHi, countEven);

  xLow = 0;
  xHi = 1;
  yLow = 1;
  yHi = 2;
  countEven = countEvenInSeq3Range(xLow, xHi, yLow, yHi);
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n", xLow, xHi, yLow, yHi, countEven);

  xLow = -5;
  xHi = -1;
  yLow = -5;
  yHi = -1;
  countEven = countEvenInSeq3Range(xLow, xHi, yLow, yHi);
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n", xLow, xHi, yLow, yHi, countEven);

  xLow = -5;
  xHi = -1;
  yLow = 1;
  yHi = 5;
  countEven = countEvenInSeq3Range(xLow, xHi, yLow, yHi);
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n", xLow, xHi, yLow, yHi, countEven);

  xLow = 1;
  xHi = 5;
  yLow = -5;
  yHi = -1;
  countEven = countEvenInSeq3Range(xLow, xHi, yLow, yHi);
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n", xLow, xHi, yLow, yHi, countEven);

  xLow = 1;
  xHi = 5;
  yLow = 1;
  yHi = 5;
  countEven = countEvenInSeq3Range(xLow, xHi, yLow, yHi);
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n", xLow, xHi, yLow, yHi, countEven);

  xLow = 1000;
  xHi = 1005;
  yLow = 20000;
  yHi = 20008;
  countEven = countEvenInSeq3Range(xLow, xHi, yLow, yHi);
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n", xLow, xHi, yLow, yHi, countEven);
}
