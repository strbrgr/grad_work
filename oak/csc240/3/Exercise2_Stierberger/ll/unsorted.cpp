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
  currentPos = NULL;
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

  if (currentPos == NULL) // start at the beginning
    currentPos = listData;
  else // move to the next item
    currentPos = currentPos->next;
  ItemType item((currentPos->info).GetValue());
  return item;
}

void UnsortedType::Print()
// Function: Prints contents of the list or empty list
// Post: Value has been sent to the stream out.
{
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

void UnsortedType::SplitLists(UnsortedType ut, ItemType item,
                              UnsortedType &list1, UnsortedType &list2)
// Function: Divides list into two lists according to the value of item.
// Pre: list has been initialized and is not empty. list1 and list2 are
// empty. Post: list1 contains all the items of list whose values are less
// than or equal to the value of item. list2 contains all of the items of
// list whose values are greater than the value of item.
{
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
