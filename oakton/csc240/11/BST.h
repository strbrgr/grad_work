#include "QueType.h"
#include <iostream>
#include <string>
typedef char ItemType;
struct TreeNode {
  ItemType info;
  TreeNode *left;
  TreeNode *right;
};
// Assumption: ItemType is a type for which the operators "<"
// and "==" are defined--either an appropriate built-in type or
// a class that overloads these operators.
enum OrderType { PRE_ORDER, IN_ORDER, POST_ORDER };
class TreeType {
public:
  TreeType();  // Constructor.
  ~TreeType(); // Destructor.
  TreeType(const TreeType &originalTree);
  void operator=(TreeType &originalTree);
  void MakeEmpty();
  bool IsEmpty() const;
  bool IsFull() const;
  int LengthIs() const;
  void RetrieveItem(ItemType &item, bool &found) const;
  void PutItem(ItemType item);
  void operator=(const TreeType &originalTree);
  void DeleteItem(ItemType item);
  void ResetTree(OrderType order);
  void GetNextItem(ItemType &item, OrderType order, bool &finished);
  void Print(std::ofstream &outFile) const;
  void PreOrder(TreeNode *, QueType &);
  void InOrder(TreeNode *, QueType &);
  void PostOrder(TreeNode *, QueType &);
  std::string Ancestors(ItemType item) const;
  std::string AncestorsHelper(TreeNode *node, ItemType item) const;

private:
  TreeNode *root;
  QueType preQue;
  QueType inQue;
  QueType postQue;
  std::string ancestors;
};
