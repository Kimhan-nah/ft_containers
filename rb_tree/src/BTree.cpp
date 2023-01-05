#include "../includes/BTree.hpp"

#include <iostream>

BTree::BTree() {
  right_ = NULL;
  left_ = NULL;
}

BTree::BTree(int value) {
  value_ = value;
  right_ = NULL;
  left_ = NULL;
}

BTree::BTree(const BTree &copy) { *this = copy; }

BTree::~BTree() {}

BTree &BTree::operator=(const BTree &ref) {
  value_ = ref.value_;
  right_ = ref.right_;
  left_ = ref.left_;
  return (*this);
}

int BTree::getValue() { return value_; }

BTree *BTree::search(int value) {
  std::cout << "====SEARCH====" << std::endl;

  if (value_ == value) {
    return this;
  } else if (value_ < value && left_) {
    return left_->search(value);
  } else if (value_ > value && right_) {
    return right_->search(value);
  } else {
    std::cout << "There are no " << value_ << std::endl;
    return NULL;
  }
}

bool BTree::insert(BTree *new_node) {
  int value = new_node->getValue();

  if (new_node == NULL) {
    std::cout << "ERROR : NULL Node" << std::endl;
    return false;
  }

  if (value_ == value) {
    std::cout << "ERROR : Duplicated Node" << std::endl;
    return false;
  } else if (value_ < value) {
    if (left_)
      return left_->insert(new_node);
    else {
      left_ = new_node;
      return true;
    }
  } else {
    if (right_)
      return right_->insert(new_node);
    else {
      right_ = new_node;
      return true;
    }
  }
}

// bool BTree::del(int value) { search(value); }

void BTree::print_tree() {
  BTree tmp = *this;

  if (right_ != NULL) right_->print_tree();
  std::cout << value_ << std::endl;
  if (left_ != NULL) left_->print_tree();
}