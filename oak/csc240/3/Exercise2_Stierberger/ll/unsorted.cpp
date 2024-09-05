#include "unsorted.h"
#include "ItemType.h"

#include <iostream>
using namespace std;
struct NodeType {
  ItemType info;
  NodeType *next;
};

UnsortedType::UnsortedType() // Class constructor
{
  length = 0;
  listData = NULL;
}
bool UnsortedType::IsFull() const
// Returns true if there is no room for another ItemType
//  on the free store; false otherwise.
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
// Post: Number of items in the list is returned.
{
  return length;
}

void UnsortedType::MakeEmpty()
// Post: List is empty; all items have been deallocated.
{
  NodeType *tempPtr;

  while (listData != NULL) {
    tempPtr = listData;
    listData = listData->next;
    delete tempPtr;
  }
  length = 0;
}
void UnsortedType::PutItem(ItemType item)
// item is in the list; length has been incremented.
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

ItemType UnsortedType::GetItem(ItemType &item, bool &found)
// Pre:  Key member(s) of item is initialized.
// Post: If found, item's key matches an element's key in the
//       list and a copy of that element has been stored in item;
//       otherwise, item is unchanged.
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

void UnsortedType::DeleteItem(ItemType item)
// Pre:  item's key has been initialized.
//       An element in the list has a key that matches item's.
// Post: No element in the list has a key that matches item's.
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
// Post: Current position has been initialized.
{
  currentPos = NULL;
}

ItemType UnsortedType::GetNextItem()
// Post:  A copy of the next item in the list is returned.
//        When the end of the list is reached, currentPos
{

  if (currentPos == NULL) // start at the beginning
    currentPos = listData;
  else // move to the next item
    currentPos = currentPos->next;
  ItemType item((currentPos->info).GetValue());
  return item;
}

UnsortedType::~UnsortedType()
// Post: List is empty; all items have been deallocated.
{
  NodeType *tempPtr;

  while (listData != NULL) {
    tempPtr = listData;
    listData = listData->next;
    delete tempPtr;
  }
}

void UnsortedType::Print() {
  ResetList();
  if (length == 0) {
    cout << "Empty list." << endl;
  } else {
    cout << "The list: " << endl;
    do {
      GetNextItem().Print(cout);
      cout << " ";
    } while (currentPos->next != NULL);
  }
  cout << endl;
}

// Assignment operator
UnsortedType &UnsortedType::operator=(const UnsortedType &rhs) {
  NodeType *tempPtr;
  if (this == &rhs) { // don't allow list = list;
    return *this;
  } else {
    // delete old contents of this
    int tempLength = GetLength();
    for (int i = 0; i < tempLength; i++) {
      ItemType item(listData->info);
      this->DeleteItem(item);
    }
    // copy new contents over to this from rhs
    tempPtr = rhs.listData;
    for (int i = 0; i < rhs.GetLength(); i++) {
      ItemType item(tempPtr->info);
      this->PutItem(item);
      tempPtr = tempPtr->next;
    }
  }
  return *this;
}

// Copy Constructor
UnsortedType::UnsortedType(const UnsortedType &ut) {
  length = 0;
  listData = NULL;
  NodeType *tempPtr;
  tempPtr = ut.listData;
  for (int i = 0; i < ut.GetLength(); i++) {
    ItemType item(tempPtr->info);
    this->PutItem(item);
    tempPtr = tempPtr->next;
  }
}

void UnsortedType::SplitLists(UnsortedType ut, ItemType item,
                              UnsortedType &list1, UnsortedType &list2) {
  int length = ut.GetLength();
  // Ensure proper Initialization
  ut.ResetList();
  list1.ResetList();
  list2.ResetList();

  for (int i = 0; i < length; i++) {
    ItemType temp = ut.GetNextItem().GetValue();

    if (temp.GetValue() <= item.GetValue()) {
      list1.PutItem(temp);
    } else {
      list2.PutItem(temp);
    }
  }

  cout << endl;
  cout << "Splitting the lists on Value 5 results in List 1 with values: "
       << endl;

  for (int i = 0; i < list1.GetLength(); i++) {
    list1.GetNextItem().Print(cout);
    cout << " ";
  }
  cout << endl;
  cout << endl;

  cout << "and List 2: " << endl;

  for (int i = 0; i < list2.GetLength(); i++) {
    list2.GetNextItem().Print(cout);
    cout << " ";
  }
}
