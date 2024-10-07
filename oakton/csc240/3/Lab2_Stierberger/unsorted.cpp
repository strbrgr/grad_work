#include "unsorted.h"
#include <iostream>
using namespace std;
struct NodeType {
  ItemType info;
  NodeType *next;
};

UnsortedType::UnsortedType()
// constructor
{
  length = 0;
  listData = NULL;
}
UnsortedType::~UnsortedType()
// Destructor
{
  NodeType *tempPtr;

  while (listData != NULL) {
    tempPtr = listData;
    listData = listData->next;
    delete tempPtr;
  }
}

void UnsortedType::MakeEmpty()
// Function: Returns the list to the empty state.
// Post:  List is empty.
{
  NodeType *tempPtr;

  while (listData != NULL) {
    tempPtr = listData;
    listData = listData->next;
    delete tempPtr;
  }
  length = 0;
}

bool UnsortedType::IsFull() const
// Function:  Determines whether list is full.
// Pre:  List has been initialized.
// Post: Function value = (list is full)
{
  NodeType *location;
  try {
    location = new NodeType;
    delete location;
    return false;
  } catch (std::bad_alloc exception) {
    return true;
  }
}

int UnsortedType::GetLength() const
// Function: Determines the number of elements in list.
// Pre:  List has been initialized.
// Post: Function value = number of elements in list
{
  return length;
}

ItemType UnsortedType::GetItem(ItemType &item, bool &found)
// Function: Retrieves list element whose key matches item's key (if
//           present).
// Pre:  List has been initialized.
//       Key member of item is initialized.
// Post: If there is an element someItem whose key matches
//       item's key, then found = true and someItem is returned;
// 	 otherwise found = false and item is returned.
//       List is unchanged.
{
  bool moreToSearch;
  NodeType *location;

  location = listData;
  found = false;
  moreToSearch = (location != NULL);

  while (moreToSearch && !found) {
    switch (item.ComparedTo(location->info)) {
    case LESS:
    case GREATER:
      location = location->next;
      moreToSearch = (location != NULL);
      break;
    case EQUAL:
      found = true;
      item = location->info;
      break;
    }
  }
  return item;
}

void UnsortedType::PutItem(ItemType item)
// Function: Adds item to list.
// Pre:  List has been initialized.
//       List is not full.
//       item is not in list.
// Post: item is in list.
{
  NodeType *location; // Declare a pointer to a node

  location = new NodeType;   // Get a new node
  location->info = item;     // Store the item in the node
  location->next = listData; // Store address of first node
                             //   in next field of new node
  listData = location;       // Store address of new node into
                             //   external pointer
  length++;                  // Increment length of the list
}
void UnsortedType::DeleteItem(ItemType item)
// Function: Deletes the element whose key matches item's key.
// Pre:  List has been initialized.
//       Key member of item is initialized.
//       One and only one element in list has a key matching item's key.
// Post: No element in list has a key matching item's key.
{
  NodeType *location = listData;
  NodeType *tempLocation;

  // Locate node to be deleted.
  if (item.ComparedTo(listData->info) == EQUAL) {
    tempLocation = location;
    listData = listData->next; // Delete first node.
  } else {
    while (item.ComparedTo((location->next)->info) != EQUAL)
      location = location->next;

    // Delete node at location->next
    tempLocation = location->next;
    location->next = (location->next)->next;
  }
  delete tempLocation;
  length--;
}

void UnsortedType::ResetList()
// Function: Initializes current position for an iteration through the list.
// Pre:  List has been initialized.
// Post: Current position is prior to list.
{
  currentPos = listData;
}

ItemType UnsortedType::GetNextItem()
// Function: Gets the next element in list.
// Pre:  List has been initialized and has not been changed since last call.
//       Current position is defined.
//       Element at current position is not last in list.
//
// Post: Current position is updated to next position.
//       item is a copy of element at current position.
{
  ItemType item;

  if (currentPos != NULL) {
    item = currentPos->info;
    currentPos = currentPos->next;
  }

  return item;
}

void UnsortedType::Print()
// Function: Prints name and status or empty
// Post: Value(s) have been sent to the stream out.
{
  if (currentPos == NULL) {
    cout << "Empty." << endl;
    return;
  }
  for (int i = 0; i < GetLength(); i++) {
    ItemType temp = GetNextItem();
    temp.Print();
  }
}

