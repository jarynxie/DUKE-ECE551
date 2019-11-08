#include <cstdio>
#include <cstdlib>

#include "bstmap.h"

int main(void) {
  BstMap<int, int> map;
  map.add(2, 2);
  map.add(4, 4);
  map.add(1, 1);
  map.add(7, 7);
  map.add(3, 3);
  map.add(9, 9);
  map.add(-1, -1);
  map.add(88, 88);
  map.add(17, 17);
  map.add(-23, -23);
  map.add(16, 16);
  map.add(44, 44);
  map.add(77, 77);
  map.remove(2);
  map.remove(16);
  map.remove(-1);
  map.remove(4);
  map.remove(9);
  map.remove(1100);
  map.lookup(1100);

  map.add(17, 16);
  std::cout << map.lookup(17) << std::endl;
  BstMap<int, int> map2(map);
  BstMap<int, int> map3 = map;
  map.printInOrder();
  map2.printInOrder();
  map3.printInOrder();
  return EXIT_SUCCESS;
}
