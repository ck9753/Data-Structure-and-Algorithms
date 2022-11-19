#include <cstdio>
#include <cstdlib>

#include "bstmap.h"

int main() {
  BstMap<int, int> map;
  map.add(14, 1);
  map.add(87, 2);
  map.add(-1, 3);
  map.add(25, 4);
  map.add(98, 5);
  map.add(0, 6);
  map.add(39, 7);
  map.add(57, 8);
  map.add(-2, 9);
  map.add(100, 10);

  std::cout << "Expected: -2 -1 0 14 25 39 57 87 98 100" << std::endl;
  map.inOrderPrint();

  int ans1 = map.lookup(57);
  int ans2 = map.lookup(100);
  std::cout << "The location of 57 is expected to 8 and actual is " << ans1 << "\n";
  std::cout << "The location of 100 is expected to 10 and actual is " << ans2 << "\n";
  map.remove(25);
  map.inOrderPrint();

  BstMap<int, int> map2(map);
  map2.inOrderPrint();

  return EXIT_SUCCESS;
}
