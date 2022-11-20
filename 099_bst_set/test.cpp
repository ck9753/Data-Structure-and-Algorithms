#include <cstdio>
#include <cstdlib>

#include "bstset.h"

int main() {
  BstSet<int> set;
  set.add(14);
  set.add(87);
  set.add(-1);
  set.add(25);
  set.add(98);
  set.add(0);
  set.add(39);
  set.add(57);
  set.add(-2);
  set.add(100);

  std::cout << "Expected: -2 -1 0 14 25 39 57 87 98 100" << std::endl;
  set.inOrderPrint();

  int ans1 = set.contains(57);
  int ans2 = set.contains(100);
  std::cout << "ans1 is expected to be true and actual is " << ans1 << "\n";
  std::cout << "ans2 is expected to be true and actual is " << ans2 << "\n";
  set.remove(25);
  set.inOrderPrint();

  BstSet<int> set2(set);
  set2.inOrderPrint();

  return EXIT_SUCCESS;
}
