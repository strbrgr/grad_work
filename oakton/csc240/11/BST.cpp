#include "BST.h"
#include <fstream>

bool TreeType::IsFull() const
// Returns true if the free store has no room for another node
// and false otherwise.
{
  TreeNode *location;
  try {
    location = new TreeNode;
    delete location;
    return false;
  } catch (std::bad_alloc exception) {
    return true;
  }
}

bool TreeType::IsEmpty() const
// Returns true if the tree is empty and false otherwise.
{
  return root == NULL;
}

int CountNodes(TreeNode *tree);
int TreeType::LengthIs() const
// Calls the recursive function CountNodes to count the
// nodes in the tree.
{
  return CountNodes(root);
}

int CountNodes(TreeNode *tree)
// Post: Returns the number of nodes in the tree.
{
  if (tree == NULL)
    return 0;
  else
    return CountNodes(tree->left) + CountNodes(tree->right) + 1;
}

void Retrieve(TreeNode *tree, ItemType &item, bool &found);

void TreeType::RetrieveItem(ItemType &item, bool &found) const
// Calls recursive function Retrieve to search the tree for item.
{
  Retrieve(root, item, found);
}

void Retrieve(TreeNode *tree, ItemType &item, bool &found)
// Recursively searches tree for item.
// Post: If there is an element someItem whose key matches item's,
// found is true and item is set to a copy of someItem;
// otherwise, found is false and item is unchanged.
{
  if (tree == NULL)
    found = false; // item is not found.
  else if (item < tree->info)
    Retrieve(tree->left, item, found); // Search left subtree.
  else if (item > tree->info)
    Retrieve(tree->right, item, found); // Search right subtree.
  else {
    item = tree->info;
    found = true;
    // item is found.
  }
}

void Insert(TreeNode *&tree, ItemType item);

void TreeType::PutItem(ItemType item)
// Calls the recursive function Insert to insert item into tree.
{
  Insert(root, item);
}
void Insert(TreeNode *&tree, ItemType item)
// Inserts item into tree.
// Post: item is in tree; search property is maintained.
{
  if (tree == NULL) { // Insertion place found.
    tree = new TreeNode;
    tree->right = NULL;
    tree->left = NULL;
    tree->info = item;
  } else if (item < tree->info)
    Insert(tree->left, item);
  else
    Insert(tree->right, item);
}

void DeleteNode(TreeNode *&tree);

void Delete(TreeNode *&tree, ItemType item);

void TreeType::DeleteItem(ItemType item)
// Calls the recursive function Delete to delete item from tree.
{
  Delete(root, item);
}

void Delete(TreeNode *&tree, ItemType item)
// Deletes item from tree.
// Post: item is not in tree.
{
  if (item < tree->info)
    Delete(tree->left, item); // Look in left subtree.
  else if (item > tree->info)
    Delete(tree->right, item); // Look in right subtree.
  else
    DeleteNode(tree); // Node found; call DeleteNode.
}

void GetPredecessor(TreeNode *tree, ItemType &data);

void DeleteNode(TreeNode *&tree)
// Deletes the node pointed to by tree.
// Post: The user's data in the node pointed to by tree is no
// longer in the tree. If tree is a leaf node or has only one
// non-NULL child pointer, the node pointed to by tree is
// deleted; otherwise, the user's data is replaced by its
// logical predecessor and the predecessor's node is deleted.
{
  ItemType data;
  TreeNode *tempPtr;
  tempPtr = tree;
  if (tree->left == NULL) {
    tree = tree->right;
    delete tempPtr;
  } else if (tree->right == NULL) {
    tree = tree->left;
    delete tempPtr;
  } else {
    GetPredecessor(tree->left, data);
    tree->info = data;
    Delete(tree->left, data); // Delete predecessor node.
  }
}

void GetPredecessor(TreeNode *tree, ItemType &data)
// Sets data to the info member of the rightmost node in tree.
{
  while (tree->right != NULL)
    tree = tree->right;
  data = tree->info;
}

void PrintTree(TreeNode *tree, std::ofstream &outFile)
// Prints info member of items in tree in sorted order on outFile.
{
  if (tree != NULL) {
    PrintTree(tree->left, outFile);
    outFile << tree->info << " ";
    PrintTree(tree->right, outFile);
  }
}

void TreeType::Print(std::ofstream &outFile) const
// Calls recursive function Print to print items in the tree.
{
  PrintTree(root, outFile);
}

TreeType::TreeType() { root = NULL; }

void Destroy(TreeNode *&tree);
TreeType::~TreeType()
// Calls recursive function Destroy to destroy the tree.
{
  Destroy(root);
}
void Destroy(TreeNode *&tree)
// Post: tree is empty; nodes have been deallocated.
{
  if (tree != NULL) {
    Destroy(tree->left);
    Destroy(tree->right);
    delete tree;
  }
}

void CopyTree(TreeNode *&copy, const TreeNode *originalTree);

TreeType::TreeType(const TreeType &originalTree)
// Calls the recursive function CopyTree to copy originalTree
// into root.
{
  CopyTree(root, originalTree.root);
}
void TreeType::operator=(const TreeType &originalTree)
// Calls the recursive function CopyTree to copy originalTree
// into root.
{
  {
    if (&originalTree == this)
      return;      // Ignore assigning self to self.
    Destroy(root); // Deallocate existing tree nodes.
    CopyTree(root, originalTree.root);
  }
}

void CopyTree(TreeNode *&copy, const TreeNode *originalTree)
// Post: copy is the root of a tree that is a duplicate
// of originalTree.
{
  if (originalTree == NULL)
    copy = NULL;
  else {
    copy = new TreeNode;
    copy->info = originalTree->info;
    CopyTree(copy->left, originalTree->left);
    CopyTree(copy->right, originalTree->right);
  }
}

void TreeType::ResetTree(OrderType order)
// Calls a function to create a queue of the tree elements in
// the desired order.
{
  switch (order) {
  case PRE_ORDER:
    PreOrder(root, preQue);
    break;
  case IN_ORDER:
    InOrder(root, inQue);
    break;
  case POST_ORDER:
    PostOrder(root, postQue);
    break;
  }
}

void TreeType::PreOrder(TreeNode *tree, QueType &preQue)
// Post: preQue contains the tree items in preorder.
{
  if (tree != NULL) {
    preQue.Enqueue(tree->info);
    PreOrder(tree->left, preQue);
    PreOrder(tree->right, preQue);
  }
}

void TreeType::InOrder(TreeNode *tree, QueType &inQue)
// Post: inQue contains the tree items in inorder.
{
  if (tree != NULL) {
    InOrder(tree->left, inQue);
    inQue.Enqueue(tree->info);
    InOrder(tree->right, inQue);
  }
}

void TreeType::PostOrder(TreeNode *tree, QueType &postQue)
// Post: postQue contains the tree items in postorder.
{
  if (tree != NULL) {
    PostOrder(tree->left, postQue);
    PostOrder(tree->right, postQue);
    postQue.Enqueue(tree->info);
  }
}

void TreeType::GetNextItem(ItemType &item, OrderType order, bool &finished)
// Returns the next item in the desired order.
// Post: For the desired order, item is the next item in the queue.
// If item is the last one in the queue, finished is true;
// otherwise, finished is false.
{
  finished = false;
  switch (order) {
  case PRE_ORDER:
    preQue.Dequeue(item);
    if (preQue.IsEmpty())
      finished = true;
    break;
  case IN_ORDER:
    inQue.Dequeue(item);
    if (inQue.IsEmpty())
      finished = true;
    break;
  case POST_ORDER:
    postQue.Dequeue(item);
    if (postQue.IsEmpty())
      finished = true;
    break;
  }
}

std::string TreeType::Ancestors(ItemType item) const {
  if (root == NULL) {
    return "empty tree";
  }

  // No ancestors
  if (root->info == item) {
    return "";
  }

  std::string result = AncestorsHelper(root, item);
  if (result == "not found") {
    return "not found";
  }
  return result;
}

std::string TreeType::AncestorsHelper(TreeNode *node, ItemType item) const {
  // Base Case we hit a leaf or the pased in root is empty
  if (node == NULL) {
    return "not found";
  }

  // Recursive case
  if (node->info == item) {
    // Indicates that we have found the item
    //
    return "";
  }

  // Explore left
  if (item < node->info) {
    std::string leftPath = AncestorsHelper(node->left, item);
    if (leftPath != "not found") {
      // leftpath at this point is "" initially
      return std::string(1, node->info) +
             (leftPath.empty() ? "" : " " + leftPath);
    }
    // Explore right
  } else if (item > node->info) {
    std::string rightPath = AncestorsHelper(node->right, item);
    if (rightPath != "not found") {
      // rightpath at this point is "" initially
      return std::string(1, node->info) +
             (rightPath.empty() ? "" : " " + rightPath);
    }
  }
  return "not found";
}
