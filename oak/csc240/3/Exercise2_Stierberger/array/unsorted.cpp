#include "unsorted.h"
#include "ItemType.h"
#include <iostream>
using namespace std;

UnsortedType::UnsortedType() { length = 0; }

bool UnsortedType::IsFull() const
// Returns true if there is no room for another ItemType
//  on the free store; false otherwise.
{
  return (length == MAX_ITEMS);
}

int UnsortedType::GetLength() const
// Post: Number of items in the list is returned.
{
  return length;
}

void UnsortedType::MakeEmpty()
// Post: List is empty; all items have been deallocated.
{
  length = 0;
}
void UnsortedType::PutItem(ItemType item)
// item is in the list; length has been incremented.
{
  if (!IsFull()) {
    info[length] = item;
    length++;
  }
}

ItemType UnsortedType::GetItem(ItemType &item, bool &found)
// Pre:  Key member(s) of item is initialized.
// Post: If found, item's key matches an element's key in the
//       list and a copy of that element has been stored in item;
//       otherwise, item is unchanged.
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

void UnsortedType::DeleteItem(const ItemType item)
// Pre:  item's key has been initialized.
//       An element in the list has a key that matches item's.
// Post: No element in the list has a key that matches item's.
{
  int location = 0;

  while (item.ComparedTo(info[location]) != EQUAL) {
    location++;
  }
  info[location] = info[length - 1];
  length--;
}

void UnsortedType::ResetList()
// Post: Current position has been initialized.
{
  currentPos = -1;
}

ItemType UnsortedType::GetNextItem()
// Post:  A copy of the next item in the list is returned.
//        When the end of the list is reached, currentPos
//        is reset to begin again.
{
  currentPos++;
  return info[currentPos];
}

void UnsortedType::Print()
// Function: Prints contents of the list or empty list
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
    ItemType temp = list.GetNextItem().GetValue();
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
