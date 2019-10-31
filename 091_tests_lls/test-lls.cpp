#include <assert.h>

#include <cstdio>
#include <cstdlib>

#include "il.h"
void testList(void) {
  IntList list = IntList();
  assert(list.size == 0);
  assert(list.head == NULL);
  assert(list.tail == NULL);
  list.addFront(11);
  assert(list.head == list.tail);
  assert(list.size == 1);
  list.addFront(10);
  assert(list[0] == 10);
  assert(list[1] == 11);
  assert(list.head->data == 10);
  assert(list.tail->data == 11);
  assert(list.head->prev == NULL);
  assert(list.tail->next == NULL);
  assert(list.getSize() == 2);
  IntList list2 = IntList(list);
  IntList list3 = IntList();
  list3 = list2;
  assert(list3[0] == 10);
  list3.~IntList();
  list.addBack(100);
  assert(list.getSize() == 3);
  assert(list[2] = 100);
  list.remove(1);
  list.remove(100);
  assert(list.head->next->next == NULL);
}

int main(void) {
  //IntList list;
  testList();
  return EXIT_SUCCESS;
}
