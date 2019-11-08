#include <cstdio>
#include <cstdlib>

#include "bstset.h"

int main(void) {
  BstSet<int> map;
  map.add(2);
  map.add(4);
  map.add(1);
  map.add(7);
  map.add(3);
  map.add(9);
  map.add(-1);
  map.add(88);
  map.add(17);
  map.add(-23);
  map.add(16);
  map.add(44);
  map.add(77);
  map.remove(2);
  map.remove(16);
  map.remove(-1);
  map.remove(4);
  map.remove(9);
  std::cout << "111\n";
  map.remove(1100);
  std::cout << "111\n";
  //map.lookup(1100);
  std::cout << "111\n";

  BstSet<int> map2(map);
  BstSet<int> map3 = map;
  map.printInOrder();
  map2.printInOrder();
  map3.printInOrder();
  return EXIT_SUCCESS;
}
