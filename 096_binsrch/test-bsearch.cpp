#include <assert.h>
#include <math.h>

#include <cstdio>
#include <cstdlib>

#include "function.h"
#include "search.cpp"
int binarySearchForZero(Function<int, int> * f, int low, int high);

class CountedIntFn : public Function<int, int> {
 protected:
  unsigned remaining;
  Function<int, int> * f;
  const char * mesg;

 public:
  CountedIntFn(unsigned n, Function<int, int> * fn, const char * m) :
      remaining(n),
      f(fn),
      mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr, "Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }
};

class SinFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return 10000000 * (sin(arg / 100000.0) - 0.5); }
};

class anotherFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return arg; }
};

void check(Function<int, int> * f,
           int low,
           int high,
           int expected_ans,
           const char * mesg) {
  int maxTime = 0;
  if (high > low) {
    maxTime = log2(high - low) + 1;
  }
  else {
    maxTime = 1;
  }
  CountedIntFn * x = new CountedIntFn(maxTime, f, mesg);
  int ans = binarySearchForZero(x, low, high);
  assert(ans == expected_ans);
  delete x;
}

int main(void) {
  SinFunction * sin = new SinFunction();
  anotherFunction * fun = new anotherFunction();
  check(sin, 0, 150000, 52359, "case 1");
  check(fun, -5, 5, 0, "case 2");
  check(fun, -5, -2, -3, "case 3");
  check(fun, 5, 6, 5, "case 4");
  check(fun, 5, 5, 5, "case 5");
  check(fun, 7, 5, 7, "case 6");
  check(fun, -500000000, 5, 0, "case 7");
  delete sin;
  delete fun;
  return EXIT_SUCCESS;
}
