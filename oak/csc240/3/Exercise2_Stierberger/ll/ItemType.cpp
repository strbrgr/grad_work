#include "ItemType.h"
#include <iostream>

ItemType::ItemType(int x) { value = x; }

ItemType::ItemType() { value = 0; }

int ItemType::GetValue() { return value; }

RelationType ItemType::ComparedTo(ItemType otherItem) const {
  if (value < otherItem.value)
    return LESS;
  else if (value > otherItem.value)
    return GREATER;
  else
    return EQUAL;
}

void ItemType::Initialize(int number) { value = number; }

void ItemType::Print(std::ostream &out) const { out << value; }
