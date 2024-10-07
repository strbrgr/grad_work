#include "ItemType.h"
#include <iostream>

ItemType::ItemType(int x)
// Function: constructor with param
// Post: Initializes 'value' to 'x'
{
  value = x;
}

ItemType::ItemType()
// Function :constructor
// Post: Initializes 'value' to 0
{
  value = 0;
}

void ItemType::Initialize(int number)
// Function: Init the item with a value
// Pre: 'number' must be a valid integer
// Post: Sets 'value' to 'number'
{
  value = number;
}

int ItemType::GetValue()
// Function :Get the value of the item
// Post: Returns the current value of the item
{
  return value;
}

RelationType ItemType::ComparedTo(ItemType otherItem) const
// Function: Compare this item to another item
// Pre: 'other' must be a valid
// Post: Returns LESS, GREATER, or EQUAL depending on the comparison
{
  if (value < otherItem.value)
    return LESS;
  else if (value > otherItem.value)
    return GREATER;
  else
    return EQUAL;
}

void ItemType::Print(std::ostream &out) const
// Funciton: Print the item value
// Pre: 'outStream' must be a valid output stream
// Post: Outputs the value
{
  out << value;
}
