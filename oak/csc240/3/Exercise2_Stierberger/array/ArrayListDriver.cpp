//============================================================================
// Name        : ArrayList.cpp
// Author      : Jochen Stierberger
// Version     : 09/04/2024
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
  myList.PutItem(ItemType(5));
  myList.Print();
  cout << endl;
  // Should print 5 5 5
  FindAllItems(myList, ItemType(5)).Print();
  cout << endl;
  // Should print 8 2 7
  DeleteAllItems(myList, ItemType(5)).Print();
  cout << endl;
  UnsortedType newList;
  newList.PutItem(ItemType(9));
  newList.PutItem(ItemType(7));
  newList.PutItem(ItemType(2));
  newList.PutItem(ItemType(3));
  newList.PutItem(ItemType(4));
  // Should print 9 7 2 3 4
  newList.Print();
  cout << endl;
  newList.DeleteItem(ItemType(2));
  // Should print 9 7 3 4
  newList.Print();
  cout << endl;

  ItemType itemToLookFor = ItemType(2);
  bool found = false;
  ItemType itemFound = newList.GetItem(itemToLookFor, found);
  // Should Print 2
  cout << "Testing the GetItem method with ItemType 2. Result is: " << endl;
  itemFound.Print(cout);
  cout << endl;
  cout << endl;

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
