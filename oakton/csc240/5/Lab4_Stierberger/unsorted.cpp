#include "unsorted.h"
#include "ItemType.h"
#include <iostream>
using namespace std;

UnsortedType::UnsortedType()
// Constructor
{
  length = 0;
  currentPos = 0;
  limit = 5;
  info = new ItemType[limit];
}

void UnsortedType::MakeEmpty()
// Function: Returns the list to the empty state.
// Post:  List is empty.
{
  length = 0;
}

bool UnsortedType::IsFull() const
// Function:  Determines whether list is full.
// Pre:  List has been initialized.
// Post: Function value = (list is full)
{
  return (length == limit);
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
  int location = 0;
  found = false;

  while (location < length && !found) {
    switch (item.ComparedTo(info[location])) {
    case LESS:
    case GREATER:
      location++;
      break;
    case EQUAL:
      found = true;
      item = info[location];
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
  if (IsFull()) {
    UnsortedType::DoubleSize();
  }

    info[length] = item;
    length++;

}

void UnsortedType::DeleteItem(const ItemType item)
// Function: Deletes the element whose key matches item's key.
// Pre:  List has been initialized.
//       Key member of item is initialized.
//       One and only one element in list has a key matching item's key.
// Post: No element in list has a key matching item's key.
{
  int replacementsIndex = 0;
  for (int i = 0; i < length; i++) {
    if (item.ComparedTo(info[i]) != EQUAL) {
      info[replacementsIndex] = info[i];
      replacementsIndex++;
    }
  }
  length = replacementsIndex;
}

void UnsortedType::ResetList()
// Function: Initializes current position for an iteration through the list.
// Pre:  List has been initialized.
// Post: Current position is prior to list.
{
  currentPos = -1;
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
  currentPos++;
  return info[currentPos];
}

void UnsortedType::Print()
// Function: Prints contents of the list or empty list
// post: Value has been sent to the stream out.
{
  ResetList();
  if (length == 0) {
    cout << "Empty list." << endl;
  } else {
    cout << "The list: " << endl;
    ResetList();
    for (int i = 0; i < length; i++) {
      GetNextItem().Print(cout);
      cout << " ";
    }
    cout << endl;
  }
}

void UnsortedType::SplitLists(UnsortedType &list, ItemType item,
                              UnsortedType &list1, UnsortedType &list2)
// Function: Divides list into two lists according to the value of item.
// Pre: list has been initialized and is not empty. list1 and list2 are
// empty.
// Post: list1 contains all the items of list whose values are less
// than or equal to the value of item. list2 contains all of the items of
// list whose values are greater than the value of item.
{
  // Ensure proper Initialization
  list.ResetList();
  list1.ResetList();
  list2.ResetList();

  for (int i = 0; i < list.GetLength(); i++) {
    ItemType temp = list.GetNextItem();

    switch (temp.ComparedTo(item)) {
    case LESS:
    case EQUAL:
      list1.PutItem(temp);
      break;
    case GREATER:
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

void UnsortedType::ShiftRight()
// Function: Shifts the contents of the list one element to the right.
// Pre: List has been initialized and is not empty.
// Post: Last item is at the front
{
  if (length > 1) {
    ItemType lastItem = info[length - 1];
    for (int i = length - 1; i > 0; i--) {
      info[i] = info[i - 1];
    }
    info[0] = lastItem;
  }
}

void UnsortedType::DoubleSize()
{
  cout << "List is full. Let's double the size and copy over all elements" << endl;
  int newSize = length * 2;
  cout << "New Size is: " << newSize << endl;

  ItemType* doubledArray = new ItemType[newSize];

  for (int i = 0; i < length; i++) {
    doubledArray[i] = info[i];
  }

  delete[] info;

  limit = newSize;
  info = doubledArray;
}
