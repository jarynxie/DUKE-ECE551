// This file is for Step 1.
// You should do
//  Step 1 (A): write seq1
//  Step 1 (B): write main to test seq1
//  Step 1 (C): write printSeq1Range
//  Step 1 (D): add test cases to main to test printSeq1Range
//
// Be sure to #include any header files you need!
#include <stdio.h>
#include <stdlib.h>

int seq1(int x) {
  return 4 * x - 3;
}

int main(void) {
  int seq1In;
  int seq1Result;

  seq1In = 0;
  seq1Result = seq1(seq1In);
  printf("seq1(%d) = %d\n", seq1In, seq1Result);

  seq1In = -1;
  seq1Result = seq1(seq1In);
  printf("seq1(%d) = %d\n", seq1In, seq1Result);

  seq1In = 1;
  seq1Result = seq1(seq1In);
  printf("seq1(%d) = %d\n", seq1In, seq1Result);

  seq1In = 9;
  seq1Result = seq1(seq1In);
  printf("seq1(%d) = %d\n", seq1In, seq1Result);

  seq1In = 10;
  seq1Result = seq1(seq1In);
  printf("seq1(%d) = %d\n", seq1In, seq1Result);

  seq1In = 11;
  seq1Result = seq1(seq1In);
  printf("seq1(%d) = %d\n", seq1In, seq1Result);

  seq1In = -500000000;
  seq1Result = seq1(seq1In);
  printf("seq1(%d) = %d\n", seq1In, seq1Result);

  seq1In = 500000000;
  seq1Result = seq1(seq1In);
  printf("seq1(%d) = %d\n", seq1In, seq1Result);

  seq1In = -2;
  seq1Result = seq1(seq1In);
  printf("seq1(%d) = %d\n", seq1In, seq1Result);

  seq1In = -3;
  seq1Result = seq1(seq1In);
  printf("seq1(%d) = %d\n", seq1In, seq1Result);

  seq1In = -4;
  seq1Result = seq1(seq1In);
  printf("seq1(%d) = %d\n", seq1In, seq1Result);

  seq1In = -1000000000;
  seq1Result = seq1(seq1In);
  printf("seq1(%d) = %d\n", seq1In, seq1Result);

  seq1In = 1000000000;
  seq1Result = seq1(seq1In);
  printf("seq1(%d) = %d\n", seq1In, seq1Result);
}
