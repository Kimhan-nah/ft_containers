#include "BTreeNode.hpp"

#include <iostream>

BTreeNode::BTreeNode() {}

BTreeNode::BTreeNode(int value) {
  value_ = value;
  right_ = NULL;
  left_ = NULL;
}

BTreeNode::BTreeNode(const BTreeNode &copy) { *this = copy; }

BTreeNode::~BTreeNode() {}

BTreeNode &BTreeNode::operator=(const BTreeNode &ref) { return (*this); }

int BTreeNode::getValue() { return value_; }

BTreeNode *BTreeNode::getLeft() { return left_; }

BTreeNode *BTreeNode::getRight() { return right_; }

BTreeNode *BTreeNode::search(BTreeNode *node, int value) {
  std::cout << "====SEARCH====" << std::endl;

  if (node == NULL) {
    return NULL;
  }
  if (value_ == value) {
    return node;
  } else if (value_ < value) {
    return search(left_, value);
    // return search(node->getLeft(), value);
  } else {
    return search(right_, value);
    // return search(node->getRight(), value);
  }
}

bool BTreeNode::insert(BTreeNode *new_node) {
  std::cout << "====INSERT====" << std::endl;
  if (new_node == NULL) {
    std::cout << "ERROR : NULL Node" << std::endl;
    return false;
  }
  int value = new_node->getValue();

  // search
  BTreeNode *tmp = search(new_node, value);

  if (value_ == value) {
    std::cout << "ERROR : Duplicated Node" << std::endl;
    return false;
  }

  return true;
}