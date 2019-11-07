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
  //BstMap<int, int> map2(map);
  //BstMap<int, int> map3 = map;
  map.printInOrder();
  //std::cout << std::endl;
  //map2.printInOrder();
  //std::cout << std::endl;
  //map3.printInOrder();
  //std::cout << std::endl;
  return EXIT_SUCCESS;
}
