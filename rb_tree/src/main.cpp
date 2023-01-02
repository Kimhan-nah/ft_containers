#include "BTreeNode.hpp"

int main() {
  // SEARCH
  BTreeNode *b_tree = new BTreeNode(1);
  // BTreeNode *left = new BTreeNode(2);
  // BTreeNode *right = new BTreeNode(3);

  // TEST CODE : INSERT
  for (int i = 0; i < 10; i++) {
    b_tree->insert(new BTreeNode(i));
  }

  return 0;
}