#include <iostream>

#include "../includes/BTree.hpp"

int main() {
  // SEARCH
  BTree *b_tree = new BTree(5);

  // TEST CODE : INSERT
  b_tree->insert(new BTree(2));
  b_tree->insert(new BTree(1));
  b_tree->insert(new BTree(3));
  b_tree->insert(new BTree(0));
  b_tree->insert(new BTree(4));
  b_tree->insert(new BTree(8));
  b_tree->insert(new BTree(10));

  // Print
  b_tree->print_tree();

  return 0;
}