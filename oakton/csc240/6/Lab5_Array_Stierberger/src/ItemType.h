#ifndef ITEM_TYPE_H
#define ITEM_TYPE_H

#include <fstream>
enum RelationType { LESS, GREATER, EQUAL };

class ItemType {
public:
  ItemType();
  // Function :constructor
  // Post: Initializes 'value' to 0

  ItemType(int x);
  // Function: constructor with param
  // Post: Initializes 'value' to 'x'

  void Initialize(int number);
  // Function: Init the item with a value
  // Pre: 'number' must be a valid integer
  // Post: Sets 'value' to 'number'

  int GetValue();
  // Function Get the value of the item
  // Post: Returns the current value of the item

  RelationType ComparedTo(ItemType other) const;
  // Function: Compare this item to another item
  // Pre: 'other' must be a valid
  // Post: Returns LESS, GREATER, or EQUAL depending on the comparison

  void Print(std::ostream &outStream) const;
  // Funciton: Print the item value
  // Pre: 'outStream' must be a valid output stream
  // Post: Outputs the value

private:
  int value;
};

#endif
