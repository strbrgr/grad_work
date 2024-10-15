// This is an implementation of an unsorted Linked List
#include <optional>
typedef int ItemType;

struct NodeType {
  ItemType info;
  NodeType *next;
};

class LinkedList {
public:
  LinkedList();
  LinkedList(const LinkedList &ll);
  ~LinkedList();
  LinkedList &operator=(const LinkedList &ll);
  LinkedList operator+(const LinkedList &ll);
  bool operator==(const LinkedList &ll) const;
  int GetLength() const;
  void PutItemFront(ItemType item);
  void PutItemMiddle(ItemType item);
  void PutItemEnd(ItemType item);
  void DeleteItem(ItemType item);
  void DeleteItemFront();
  void DeleteItemEnd();
  void DeleteItemByPosition(int position);
  std::optional<ItemType> FindNode(ItemType item) const;

  void MakeEmpty();

  ItemType IterateOver() const;
  void ResetList();
  ItemType GetNextItem();
  bool IsEmpty() const;

  void Print() const;

private:
  NodeType *location; // iterator
  NodeType *head;     // external pointer
  int length;
};
