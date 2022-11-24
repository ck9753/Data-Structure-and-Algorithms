#include "node.h"
void Node::buildMap(BitString b, std::map<unsigned, BitString> & theMap) {
  //WRITE ME!
  if (sym != NO_SYM) {
    theMap.insert(std::pair<unsigned, BitString>(sym, b));
  }

  else {
    BitString bit_left = b.plusZero();
    this->left->buildMap(bit_left, theMap);
    BitString bit_right = b.plusOne();
    this->right->buildMap(bit_right, theMap);
  }
}
