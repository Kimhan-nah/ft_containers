#ifndef B_TREE_NODE_HPP
#define B_TREE_NODE_HPP

class BTreeNode {
 private:
  int value_;
  BTreeNode *right_;
  BTreeNode *left_;

 public:
  BTreeNode(/* args*/);
  BTreeNode(int value);
  BTreeNode(const BTreeNode &copy);
  ~BTreeNode();
  BTreeNode &operator=(const BTreeNode &ref);

  // GETTER
  int getValue();
  BTreeNode *getLeft();
  BTreeNode *getRight();

  // BTREE function
  BTreeNode *search(BTreeNode *node, int value);
  bool insert(BTreeNode *new_node);
};

#endif