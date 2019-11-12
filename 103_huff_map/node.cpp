#include "node.h"

#include <assert.h>
void Node::buildMap(BitString b, std::map<unsigned, BitString> & theMap) {
  if (sym != NO_SYM) {
    assert(left == NULL);
    assert(right == NULL);
    theMap.insert(std::pair<unsigned, BitString>(sym, b));
  }
  else if (sym == NO_SYM) {
    left->buildMap(b.plusZero(), theMap);
    right->buildMap(b.plusOne(), theMap);
  }
}
