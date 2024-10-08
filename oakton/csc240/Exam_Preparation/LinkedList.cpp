#include "LinkedList.h"
#include "iostream"
#include <cstddef>
#include <optional>

LinkedList::LinkedList()
// Constructor: Initializes the linked list with an empty state.
{
  location = NULL;
  head = NULL;
  length = 0;
}

LinkedList::~LinkedList()
// Destructor: Deallocates memory by making the list empty.
{
  MakeEmpty();
}

int LinkedList::GetLength() const
// Returns the length of the linked list.
{
  return length;
}

void LinkedList::PutItemFront(ItemType item)
// Inserts item at the front of the linked list.
{
  NodeType *newNode = new NodeType;
  newNode->info = item;
  newNode->next = head;
  head = newNode;
  length++;
}

void LinkedList::PutItemMiddle(ItemType item)
// Inserts item in the middle of the linked list.
{
  if (length == 0) {
    PutItemFront(item);
    return;
  }

  if (length == 1) {
    PutItemEnd(item);
    return;
  }

  NodeType *location = head;
  NodeType *previous = NULL;
  int middle = length / 2;

  // Traverse to the middle of the list
  for (int i = 0; i < middle; i++) {
    previous = location;
    location = location->next;
  }

  // Create new node and insert between previous and next
  NodeType *newNode = new NodeType;
  newNode->info = item;
  newNode->next = location;
  previous->next = newNode;
  length++;
}

void LinkedList::PutItemEnd(ItemType item)
// Inserts item at the end of the linked list.
{
  // Empty list case
  if (head == NULL) {
    PutItemFront(item);
    return;
  }

  NodeType *location = head;

  // Traverse to the end of the list
  while (location->next != NULL) {
    location = location->next;
  }

  // Create new node and insert at the end
  NodeType *newNode = new NodeType;
  newNode->info = item;
  newNode->next = NULL;
  location->next = newNode;
  length++;
}

void LinkedList::DeleteItem(ItemType item)
// Deletes all nodes that have an info value matching the provided item.
// If no nodes match, the list remains unchanged.
{
  NodeType *templocation;
  NodeType *location = head;
  NodeType *prev;

  while (location != NULL) {
    if (location->info == item) {

      if (location == head) {
        head = head->next;
        // Deletes the current node and moves head to the next node.
        delete location;
        location = head;
      } else {
        prev->next = location->next;
        delete location;
        location = prev->next;
      }
      length--;
    } else {
      prev = location;
      location = location->next;
    }
  }
}

void LinkedList::DeleteItemFront() {
  // Empty list
  if (head == NULL) {
    return;
  }

  // One node in list
  if (length == 1) {
    MakeEmpty();
    return;
  }

  // Move head forward and delete previous head
  NodeType *templocation = head;
  head = head->next;
  delete templocation;
  length--;
}

void LinkedList::DeleteItemEnd() {
  // Empty list
  if (head == NULL) {
    return;
  }

  // One node in list
  if (head->next == NULL) {
    delete head;
    head = NULL;
    length = 0;
    return;
  }

  // Iterate to second to last element
  NodeType *location = head;
  NodeType *prev;
  while (location->next != NULL) {
    prev = location;
    location = location->next;
  }
  delete location;
  prev->next = NULL;
  length--;
}

void LinkedList::DeleteItemByPosition(int position) {
  // Handle edge cases
  if (position < 0 || position >= length) {
    return;
  }

  if (position == 0) {
    NodeType *tempPtr = head;
    head = head->next;
    delete tempPtr;
    length--;
    return;
  }

  NodeType *location = head;
  for (int i = 0; i < position - 1; i++) {
    location = location->next;
  }

  NodeType *nodeToDelete = location->next;
  location->next = nodeToDelete->next;
  delete nodeToDelete;
  length--;
}

std::optional<ItemType> LinkedList::FindNode(ItemType item) const {
  if (head == NULL) {
    std::cout << "Nope" << std::endl;
    return std::nullopt;
  }

  NodeType *location = head;
  while (location != NULL) {
    if (location->info == item) {
      return item;
    }
    location = location->next;
  }

  return std::nullopt;
}

void LinkedList::MakeEmpty()
// Empties the linked list by deallocating all node memory.
{
  while (head != NULL) {
    NodeType *location;
    location = head;
    head = head->next;
    delete location;
  }
  length = 0;
}

void LinkedList::Print() const
// Prints the info of each node in the linked list.
{
  NodeType *location = head;
  while (location != NULL) {
    std::cout << "Node is: " << location->info << std::endl;
    location = location->next;
  }
}

void LinkedList::ResetList()
// Resets the location pointer to NULL (for iteration purposes).
{
  location = NULL;
}

bool LinkedList::IsEmpty() const
// Returns true if the linked list is empty, otherwise false.
{
  return length == 0;
}
