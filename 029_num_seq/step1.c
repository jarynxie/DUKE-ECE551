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

void printSeq1Range(int low, int high) {
  if (low >= high) {
    printf("\n");
  }
  else {
    for (int current = low; current < high - 1; current++) {
      printf("%d, ", seq1(current));
    }
    printf("%d\n", seq1(high - 1));
  }
}

int main(void) {
  int seq1In = 0;
  int seq1Result = 0;

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

  int low = 0;
  int high = 0;

  low = 0;
  high = 4;
  printf("printSeq1Range(%d, %d)\n", low, high);
  printSeq1Range(low, high);

  low = 5;
  high = 9;
  printf("printSeq1Range(%d, %d)\n", low, high);
  printSeq1Range(low, high);

  low = -2;
  high = 6;
  printf("printSeq1Range(%d, %d)\n", low, high);
  printSeq1Range(low, high);

  low = -10;
  high = -2;
  printf("printSeq1Range(%d, %d)\n", low, high);
  printSeq1Range(low, high);

  low = 7;
  high = 3;
  printf("printSeq1Range(%d, %d)\n", low, high);
  printSeq1Range(low, high);

  low = 30;
  high = 25;
  printf("printSeq1Range(%d, %d)\n", low, high);
  printSeq1Range(low, high);

  low = 0;
  high = 0;
  printf("printSeq1Range(%d, %d)\n", low, high);
  printSeq1Range(low, high);

  low = -500000000;
  high = -499999995;
  printf("printSeq1Range(%d, %d)\n", low, high);
  printSeq1Range(low, high);

  low = 500000000;
  high = 500000005;
  printf("printSeq1Range(%d, %d)\n", low, high);
  printSeq1Range(low, high);
}
