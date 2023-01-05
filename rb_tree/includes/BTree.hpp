#ifndef B_TREE_HPP
#define B_TREE_HPP

class BTree {
 private:
  int value_;
  BTree *right_;
  BTree *left_;

 public:
  BTree(/* args*/);
  BTree(int value);
  BTree(const BTree &copy);
  ~BTree();
  BTree &operator=(const BTree &ref);

  // GETTER
  int getValue();

  // BTREE function
  BTree *search(int value);
  bool insert(BTree *new_node);
  bool del(int value);
  void print_tree();
};

#endif