#ifndef UNSORTED_H
#define UNSORTED_H
#include "ItemType.h"
// File ItemType.h must be provided by the user of this class.
//  ItemType.h must contain the following definitions:
//  MAX_ITEMS:     the maximum number of items on the list
//  ItemType:      the definition of the objects on the list
//  RelationType:  {LESS, GREATER, EQUAL}
//  Member function ComparedTo(ItemType item) which returns
//       LESS, if self "comes before" item
//       GREATER, if self "comes after" item
//       EQUAL, if self and item are the same
//  Iterator: currentPos, GetNextItem
//  When the end of the list is reached, currentPos
//  is reset to begin again.
const int MAX_ITEMS = 5;
class UnsortedType {
public:
  UnsortedType();
  // Constructor
  void MakeEmpty();
  // Function: Returns the list to the empty state.
  // Post:  List is empty.
  bool IsFull() const;
  // Function:  Determines whether list is full.
  // Pre:  List has been initialized.
  // Post: Function value = (list is full)
  int GetLength() const;
  // Function: Determines the number of elements in list.
  // Pre:  List has been initialized.
  // Post: Function value = number of elements in list
  ItemType GetItem(ItemType &item, bool &found);
  // Function: Retrieves list element whose key matches item's key (if
  //           present).
  // Pre:  List has been initialized.
  //       Key member of item is initialized.
  // Post: If there is an element someItem whose key matches
  //       item's key, then found = true and someItem is returned;
  // 	 otherwise found = false and item is returned.
  //       List is unchanged.
  void PutItem(ItemType item);
  // Function: Adds item to list.
  // Pre:  List has been initialized.
  //       List is not full.
  //       item is not in list.
  // Post: item is in list.
  void DeleteItem(ItemType item);
  // Function: Deletes the element whose key matches item's key.
  // Pre:  List has been initialized.
  //       Key member of item is initialized.
  //       One and only one element in list has a key matching item's key.
  // Post: No element in list has a key matching item's key.
  void ResetList();
  // Function: Initializes current position for an iteration through the list.
  // Pre:  List has been initialized.
  // Post: Current position is prior to list.
  ItemType GetNextItem();
  // Function: Gets the next element in list.
  // Pre:  List has been initialized and has not been changed since last call.
  //       Current position is defined.
  //       Element at current position is not last in list.
  //
  // Post: Current position is updated to next position.
  //       item is a copy of element at current position.
  void Print();
  // Function: Prints contents of the list or empty list
  // post: Value has been sent to the stream out.
  void SplitLists(UnsortedType &list, ItemType item, UnsortedType &list1,
                  UnsortedType &list2);
  // Function: Divides list into two lists according to the value of item.
  // Pre: list has been initialized and is not empty. list1 and list2 are
  // empty.
  // Post: list1 contains all the items of list whose values are less
  // than or equal to the value of item. list2 contains all of the items of
  // list whose values are greater than the value of item.
  void ShiftRight();
  // Function: Shifts the contents of the list one element to the right.
  // Pre: List has been initialized and is not empty.
  // Post: Last item is at the front

private:
  int length;
  ItemType info[MAX_ITEMS];
  int currentPos;
};
#endif