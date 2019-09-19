// This file is for Step 2.
// You should do
//  Step 2 (A): write seq2
//  Step 2 (B): write main to test seq2
//  Step 2 (C): write sumSeq2
//  Step 2 (D): add test cases to main to test sumSeq2
//
// Be sure to #include any header files you need!

#include <stdio.h>
#include <stdlib.h>
int seq2(int x) {
  if (x % 4 == 2 || x % 4 == -2) {
    return 2 * x;
  }
  else {
    return (x + 1) * (x + 2) - 1;
  }
}

int sumSeq2(int low, int high) {
  int answer = 0;
  if (low >= high) {
    return 0;
  }
  else {
    for (int current = low; current < high; current++) {
      answer += seq2(current);
    }
    return answer;
  }
}

int main(void) {
  int seq2In = 0;
  int seq2Result = 0;

  seq2In = 0;
  seq2Result = seq2(seq2In);
  printf("seq2(%d) = %d\n", seq2In, seq2Result);

  seq2In = 1;
  seq2Result = seq2(seq2In);
  printf("seq2(%d) = %d\n", seq2In, seq2Result);

  seq2In = 2;
  seq2Result = seq2(seq2In);
  printf("seq2(%d) = %d\n", seq2In, seq2Result);

  seq2In = 3;
  seq2Result = seq2(seq2In);
  printf("seq2(%d) = %d\n", seq2In, seq2Result);

  seq2In = 6;
  seq2Result = seq2(seq2In);
  printf("seq2(%d) = %d\n", seq2In, seq2Result);

  seq2In = 10;
  seq2Result = seq2(seq2In);
  printf("seq2(%d) = %d\n", seq2In, seq2Result);

  seq2In = -1;
  seq2Result = seq2(seq2In);
  printf("seq2(%d) = %d\n", seq2In, seq2Result);

  seq2In = -2;
  seq2Result = seq2(seq2In);
  printf("seq2(%d) = %d\n", seq2In, seq2Result);

  seq2In = -3;
  seq2Result = seq2(seq2In);
  printf("seq2(%d) = %d\n", seq2In, seq2Result);

  seq2In = -4;
  seq2Result = seq2(seq2In);
  printf("seq2(%d) = %d\n", seq2In, seq2Result);

  seq2In = -6;
  seq2Result = seq2(seq2In);
  printf("seq2(%d) = %d\n", seq2In, seq2Result);

  seq2In = 400002;
  seq2Result = seq2(seq2In);
  printf("seq2(%d) = %d\n", seq2In, seq2Result);

  seq2In = -400002;
  seq2Result = seq2(seq2In);
  printf("seq2(%d) = %d\n", seq2In, seq2Result);

  seq2In = 40000;
  seq2Result = seq2(seq2In);
  printf("seq2(%d) = %d\n", seq2In, seq2Result);

  seq2In = -40000;
  seq2Result = seq2(seq2In);
  printf("seq2(%d) = %d\n", seq2In, seq2Result);

  seq2In = 2100000000;
  seq2Result = seq2(seq2In);
  printf("seq2(%d) = %d\n", seq2In, seq2Result);

  seq2In = -2100000000;
  seq2Result = seq2(seq2In);
  printf("seq2(%d) = %d\n", seq2In, seq2Result);

  seq2In = 2100000002;
  seq2Result = seq2(seq2In);
  printf("seq2(%d) = %d\n", seq2In, seq2Result);

  seq2In = -2100000002;
  seq2Result = seq2(seq2In);
  printf("seq2(%d) = %d\n", seq2In, seq2Result);

  int low = 0;
  int high = 0;

  low = 0;
  high = 2;
  printf("sumSeq2(%d, %d) = %d\n", low, high, sumSeq2(low, high));

  low = 3;
  high = 6;
  printf("sumSeq2(%d, %d) = %d\n", low, high, sumSeq2(low, high));

  low = 9;
  high = 7;
  printf("sumSeq2(%d, %d) = %d\n", low, high, sumSeq2(low, high));

  low = 9;
  high = 9;
  printf("sumSeq2(%d, %d) = %d\n", low, high, sumSeq2(low, high));

  low = 0;
  high = 100000;
  printf("sumSeq2(%d, %d) = %d\n", low, high, sumSeq2(low, high));

  low = -2;
  high = -6;
  printf("sumSeq2(%d, %d) = %d\n", low, high, sumSeq2(low, high));

  low = -10;
  high = -2;
  printf("sumSeq2(%d, %d) = %d\n", low, high, sumSeq2(low, high));

  low = 7;
  high = 3;
  printf("sumSeq2(%d, %d) = %d\n", low, high, sumSeq2(low, high));

  low = 30;
  high = 25;
  printf("sumSeq2(%d, %d) = %d\n", low, high, sumSeq2(low, high));

  low = 0;
  high = 0;
  printf("sumSeq2(%d, %d) = %d\n", low, high, sumSeq2(low, high));

  low = 400002;
  high = 400005;
  printf("sumSeq2(%d, %d) = %d\n", low, high, sumSeq2(low, high));

  low = -400002;
  high = -400000;
  printf("sumSeq2(%d, %d) = %d\n", low, high, sumSeq2(low, high));

  low = 2100000000;
  high = 2100000005;
  printf("sumSeq2(%d, %d) = %d\n", low, high, sumSeq2(low, high));

  low = -2100000000;
  high = -2000000000;
  printf("sumSeq2(%d, %d) = %d\n", low, high, sumSeq2(low, high));

  return EXIT_SUCCESS;
}
