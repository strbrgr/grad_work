#ifndef ITEMTYPE_H
#define ITEMTYPE_H

#include <fstream>
#include <iostream>
#include <string>

const int MAX_ITEMS = 5;
enum RelationType { LESS, GREATER, EQUAL };

class ItemType {
public:
  ItemType();
  RelationType ComparedTo(const ItemType &) const;
  void Print(std::ostream &) const;
  void Initialize(const std::string &value);
  int Hash() const;

private:
  std::string key;
};

ItemType::ItemType() : key("") {}

RelationType ItemType::ComparedTo(const ItemType &otherItem) const {
  if (key < otherItem.key)
    return LESS;
  else if (key > otherItem.key)
    return GREATER;
  else
    return EQUAL;
}

void ItemType::Initialize(const std::string &value) { key = value; }

void ItemType::Print(std::ostream &out) const { out << key; }

int ItemType::Hash() const {
  int hashValue = 0;
  for (char c : key) {
    hashValue += static_cast<int>(c);
  }
  return hashValue % MAX_ITEMS;
}

#endif

