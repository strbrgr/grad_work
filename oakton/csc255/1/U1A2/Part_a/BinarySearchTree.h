#include <iostream>
#include <ostream>
#include <stdexcept>
#include <utility>

template <typename Comparable> class BinarySearchTree {
public:
  BinarySearchTree();
  BinarySearchTree(const BinarySearchTree &rhs);
  BinarySearchTree(BinarySearchTree &&rhs);
  ~BinarySearchTree();

  const Comparable &findMin() const;
  const Comparable &findMax() const;
  bool contains(const Comparable &x) const;
  bool isEmpty() const;
  void printTree(std::ostream &out = std::cout) const;

  void makeEmpty();
  void insert(const Comparable &x);
  void insert(Comparable &&x);
  void remove(const Comparable &x);
  int getRank(const std::string &name) const;

  BinarySearchTree &operator=(const BinarySearchTree &rhs);
  BinarySearchTree &operator=(BinarySearchTree &&rhs);

private:
  struct BinaryNode {
    Comparable element;
    BinaryNode *left;
    BinaryNode *right;

    BinaryNode(const Comparable &theElement, BinaryNode *lt, BinaryNode *rt)
        : element{theElement}, left{lt}, right{rt} {}

    BinaryNode(Comparable &&theElement, BinaryNode *lt, BinaryNode *rt)
        : element{std::move(theElement)}, left{lt}, right{rt} {}
  };

  BinaryNode *root;

  void insert(const Comparable &x, BinaryNode *&t);
  void insert(Comparable &&x, BinaryNode *&t);
  void remove(const Comparable &x, BinaryNode *&t);
  BinaryNode *findMin(BinaryNode *t) const;
  BinaryNode *findMax(BinaryNode *t) const;
  bool contains(const Comparable &x, BinaryNode *t) const;
  void makeEmpty(BinaryNode *&t);
  void printTree(BinaryNode *t, std::ostream &out) const;
  BinaryNode *clone(BinaryNode *t) const;
};

// Constructor
template <typename Comparable>
BinarySearchTree<Comparable>::BinarySearchTree() : root{nullptr} {}

// Destructor
template <typename Comparable>
BinarySearchTree<Comparable>::~BinarySearchTree() {
  makeEmpty();
}

// Copy constructor
template <typename Comparable>
BinarySearchTree<Comparable>::BinarySearchTree(const BinarySearchTree &rhs)
    : root{nullptr} {
  root = clone(rhs.root);
}

// Move constructor
template <typename Comparable>
BinarySearchTree<Comparable>::BinarySearchTree(BinarySearchTree &&rhs)
    : root{rhs.root} {
  rhs.root = nullptr;
}

// Make subtree empty
template <typename Comparable>
void BinarySearchTree<Comparable>::makeEmpty(BinaryNode *&t) {
  if (t != nullptr) {
    makeEmpty(t->left);
    makeEmpty(t->right);
    delete t;
  }
  t = nullptr;
}

// Insert
template <typename Comparable>
void BinarySearchTree<Comparable>::insert(const Comparable &x) {
  insert(x, root);
}

template <typename Comparable>
void BinarySearchTree<Comparable>::insert(Comparable &&x) {
  insert(std::move(x), root);
}

template <typename Comparable>
void BinarySearchTree<Comparable>::insert(const Comparable &x, BinaryNode *&t) {
  if (t == nullptr)
    t = new BinaryNode{x, nullptr, nullptr};
  else if (x < t->element)
    insert(x, t->left);
  else if (t->element < x)
    insert(x, t->right);
  else
    ; // Duplicate; do nothing
}

template <typename Comparable>
void BinarySearchTree<Comparable>::insert(Comparable &&x, BinaryNode *&t) {
  if (t == nullptr)
    t = new BinaryNode{std::move(x), nullptr, nullptr};
  else if (x < t->element)
    insert(std::move(x), t->left);
  else if (t->element < x)
    insert(std::move(x), t->right);
  else
    ; // Duplicate; do nothing
}

// Remove
template <typename Comparable>
void BinarySearchTree<Comparable>::remove(const Comparable &x) {
  remove(x, root);
}

template <typename Comparable>
void BinarySearchTree<Comparable>::remove(const Comparable &x, BinaryNode *&t) {
  if (t == nullptr)
    return; // Item not found; do nothing

  if (x < t->element)
    remove(x, t->left);
  else if (t->element < x)
    remove(x, t->right);
  else if (t->left != nullptr && t->right != nullptr) { // Two children
    t->element = findMin(t->right)->element;
    remove(t->element, t->right);
  } else {
    BinaryNode *oldNode = t;
    t = (t->left != nullptr) ? t->left : t->right;
    delete oldNode;
  }
}

// Find minimum
template <typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode *
BinarySearchTree<Comparable>::findMin(BinaryNode *t) const {
  if (t == nullptr)
    return nullptr;
  if (t->left == nullptr)
    return t;
  return findMin(t->left);
}

// Find maximum
template <typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode *
BinarySearchTree<Comparable>::findMax(BinaryNode *t) const {
  if (t != nullptr)
    while (t->right != nullptr)
      t = t->right;
  return t;
}

// Contains
template <typename Comparable>
bool BinarySearchTree<Comparable>::contains(const Comparable &x) const {
  return contains(x, root);
}

template <typename Comparable>
bool BinarySearchTree<Comparable>::contains(const Comparable &x,
                                            BinaryNode *t) const {
  if (t == nullptr)
    return false;
  else if (x < t->element)
    return contains(x, t->left);
  else if (t->element < x)
    return contains(x, t->right);
  else
    return true; // Match
}

// Print tree
template <typename Comparable>
void BinarySearchTree<Comparable>::printTree(std::ostream &out) const {
  printTree(root, out);
}

template <typename Comparable>
void BinarySearchTree<Comparable>::printTree(BinaryNode *t,
                                             std::ostream &out) const {
  if (t != nullptr) {
    printTree(t->left, out);
    out << t->element << std::endl;
    printTree(t->right, out);
  }
}

// Make the entire tree empty
template <typename Comparable> void BinarySearchTree<Comparable>::makeEmpty() {
  makeEmpty(root);
}

// Clone function
template <typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode *
BinarySearchTree<Comparable>::clone(BinaryNode *t) const {
  if (t == nullptr)
    return nullptr;
  else
    return new BinaryNode{t->element, clone(t->left), clone(t->right)};
}

template <typename Comparable>
int BinarySearchTree<Comparable>::getRank(const std::string &colorName) const {
  BinaryNode *current = root;

  while (current != nullptr) {
    // Compare by name instead of rank
    if (colorName < current->element.name) {
      current = current->left; // Go left
    } else if (current->element.name < colorName) {
      current = current->right; // Go right
    } else {
      return current->element.rank; // Return the rank of the found color
    }
  }
  return -1; // Return -1 if the color is not found
}
