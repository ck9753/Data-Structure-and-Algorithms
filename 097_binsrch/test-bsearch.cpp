#include <assert.h>

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high);

class CountedIntFn : public Function<int, int> {
 protected:
  unsigned remaining;
  Function<int, int> * f;
  const char * mesg;

 public:
  CountedIntFn(unsigned n, Function<int, int> * fn, const char * m) :
      remaining(n), f(fn), mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr, "Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }
};

class MyFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return arg; }
};

void check(Function<int, int> * f,
           int low,
           int high,
           int expected_ans,
           const char * mesg) {
  int i = 0;
  if (high > low) {
    i = log2(high - low) + 1;
  }
  else {
    i = 1;
  }
  CountedIntFn * wrap_func = new CountedIntFn(i, f, mesg);
  int ans = binarySearchForZero(wrap_func, low, high);
  delete wrap_func;
  if (ans != expected_ans) {
    fprintf(
        stderr, "ans : %d is different from what we expected: %d\n", ans, expected_ans);
    exit(EXIT_FAILURE);
  }
  if (ans == expected_ans) {
    printf("testcase success\n");
  }
}

int main(void) {
  MyFunction * func = new MyFunction();
  check(func, 2, 3, 4, "all positive\n");
  check(func, -2, -3, -4, "all negative\n");
  check(func, -1, 3, 0, "normal\n");
  check(func, 0, 2, 0, "inclusive zero\n");
  check(func, -3, 0, -2, "exclusive zero\n");
  check(func, -1, -1, -1, "low equals high\n");
  delete func;
  return EXIT_SUCCESS;
}
