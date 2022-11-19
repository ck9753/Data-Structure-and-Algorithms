#include <cmath>
#include <cstdio>
#include <cstdlib>

#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  while (low + 1 < high) {
    int mid = (low + high) / 2;
    int fx = f->invoke(mid);
    if (fx == 0) {
      return mid;
    }
    else if (fx > 0) {
      high = mid;
    }
    else {
      low = mid;
    }
  }
  return low;
}
