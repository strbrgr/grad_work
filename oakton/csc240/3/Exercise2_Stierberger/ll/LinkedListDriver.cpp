//============================================================================
// Name        : CSC240_Linked_List_Practice.cpp
// Author      : Jochen Stierberger
// Version     : 09/05/2024
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "ItemType.h"
#include "unsorted.h"
#include <iostream>
using namespace std;

// This function removes all instances of ItemType item from list,
// and returns a list without those items.
UnsortedType DeleteAllItems(UnsortedType &list, ItemType item) {
  UnsortedType listWithoutItem;
  list.ResetList();
  for (int i = 0; i < list.GetLength(); i++) {
    ItemType temp = list.GetNextItem();
    if (temp.ComparedTo(item) != EQUAL) {
      listWithoutItem.PutItem(temp);
    }
  }
  return listWithoutItem;
}

// Write a function that returns a list of all instances of item
// found in an UnsortedType linked-list.
UnsortedType FindAllItems(UnsortedType &list, ItemType item) {
  UnsortedType itemsFound;
  list.ResetList();
  for (int i = 0; i < list.GetLength(); i++) {
    ItemType temp = list.GetNextItem();
    if (temp.ComparedTo(item) == EQUAL) {
      itemsFound.PutItem(temp);
    }
  }
  return itemsFound;
}

int main() {
  UnsortedType myList;
  myList.PutItem(ItemType(8));
  myList.PutItem(ItemType(5));
  myList.PutItem(ItemType(2));
  myList.PutItem(ItemType(5));
  myList.PutItem(ItemType(7));
  myList.PutItem(ItemType(3));
  myList.PutItem(ItemType(5));
  myList.Print();
  FindAllItems(myList, ItemType(5)).Print();
  DeleteAllItems(myList, ItemType(5)).Print();
  UnsortedType newList;
  newList.PutItem(ItemType(9));
  newList.PutItem(ItemType(7));
  newList.PutItem(ItemType(2));
  newList.PutItem(ItemType(3));
  newList.PutItem(ItemType(4));
  newList.PutItem(ItemType(6));
  newList.PutItem(ItemType(1));
  cout << "Before assignment: " << endl;
  newList.Print();
  newList = myList; // use the overloaded assignment operator
  cout << "After assignment: " << endl;
  newList.Print();
  myList.Print();
  UnsortedType copy(myList); // use the copy constructor
  copy.Print();
  // if the copy constructor is not implemented, the following assignment will
  // be shallow copy
  UnsortedType otherList =
      copy; // NOT the assignment operator, but copy constructor
  cout << "otherList should have the same contents of copy." << endl;
  otherList.Print();
  cout << "copy." << endl;
  copy.DeleteItem(ItemType(3));
  copy.Print();
  cout << "otherList should NOT have the same contents of copy." << endl;
  otherList.Print();

  UnsortedType listToSplit;
  listToSplit.PutItem(ItemType(5));
  listToSplit.PutItem(ItemType(-12));
  listToSplit.PutItem(ItemType(34));
  listToSplit.PutItem(ItemType(34));
  listToSplit.PutItem(ItemType(5));
  listToSplit.PutItem(ItemType(45));
  listToSplit.PutItem(ItemType(8));
  listToSplit.PutItem(ItemType(-6));
  listToSplit.PutItem(ItemType(15));
  listToSplit.PutItem(ItemType(40));
  listToSplit.PutItem(ItemType(20));
  listToSplit.PutItem(ItemType(2));
  listToSplit.PutItem(ItemType(1));
  listToSplit.PutItem(ItemType(12));

  listToSplit.Print();
  // Split the list on itemType 5
  ItemType item = ItemType(5);
  UnsortedType list1;
  UnsortedType list2;
  listToSplit.SplitLists(listToSplit, item, list1, list2);

  return 0;
}
