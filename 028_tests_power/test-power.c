#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);

void run_check(unsigned x, unsigned y, unsigned expected_ans) {
  if (power(x, y) != expected_ans) {
    exit(EXIT_FAILURE);
  }
}
int main(void) {
  run_check(2, 3, 8);
  run_check(0, 0, 1);
  run_check(8, 3, 512);
  run_check(9, 0, 1);
  run_check(16, 5, 1048576);
  run_check(5, 5, 3125);

  printf("check all cases and no errors");
  return EXIT_SUCCESS;
}
