#ifndef HASHTYPE_H
#define HASHTYPE_H

#include <cmath>
#include <iostream>
#include <string>

const int MAX_ITEMS = 11;

template <class ItemType> class HashType {
public:
  HashType();
  HashType(int s, int factor);
  void MakeEmpty();
  // Function: Returns the list to the empty state.
  // Post: List is empty.
  bool IsFull() const;
  // Function: Determines whether list is full
  // Pre: List has been initialized.
  // Post: Function value = (list is full)
  int GetNumItems() const;
  // Function: Determines the number of elements in list.
  // Pre: List has been initialized.
  // Post: Function value = number of elements in list
  void RetrieveItem(ItemType &item, bool &found);
  // Function: Retrieves list element whose key matches item's key (if //
  // present).
  // Pre: List has been initialized.
  // Key member of item is initialized. // Post: If there is an element someItem
  // whose value matches // item's value, then found = true and item contains
  // the contents // of the item if it is found. // otherwise found = false and
  // item is returned unchanged. // List is unchanged.
  int Hash(ItemType item) const;
  // This is the hash function for this class unsigned long int GetCollisions()
  // const; return the number of collisions that occured during the build of the
  // hash table
  void InsertItemLinear(ItemType item);
  // Function: Adds item to list and uses a linear probing technique to
  // resolve collisions.
  // Pre: List has been initialized. List is not full.
  // item is not in list.
  // Post: item is in list.
  void InsertItemQuadratic(ItemType item);
  // Function: Adds item to list and uses a quadratic probing technique to
  // resolve collisions.
  // Pre: List has been initialized. List is not full. item is not in
  // list.
  // Post: item is in list.
  void Print() const;
  void DeleteItem(ItemType item);
  // Function: Deletes the element whose key matches item's key.
  // Pre: List has been initialized.
  // Key member of item is initialized.
  // One and only one element in list has a key matching item's key.
  // Post: No element in list has a key matching item's key.
  unsigned long int GetCollisions() const;

private:
  unsigned long int numCollisions;
  int numItems;
  int size;
  int a;
  ItemType *info;
  ItemType emptyItem = "";
};

template <class ItemType> HashType<ItemType>::HashType() {
  a = 33;
  numItems = 0;
  size = 11;
  numCollisions = 0;
  info = new ItemType[size];
  for (int i = 0; i < size; i++) {
    info[i] = emptyItem;
  }
}

template <class ItemType> HashType<ItemType>::HashType(int s, int factor) {
  a = factor;
  numItems = 0;
  size = s;
  numCollisions = 0;
  info = new ItemType[size];
  for (int i = 0; i < size; i++) {
    info[i] = emptyItem;
  }
}

template <class ItemType> int HashType<ItemType>::Hash(ItemType item) const {
  int hash = 0;
  int length = item.length();
  for (int i = 0; i < length; i++) {
    hash = a * hash + item[i];
  }
  return abs(hash % size);
}

template <class ItemType>
void HashType<ItemType>::InsertItemLinear(ItemType item) {
  int index = Hash(item);
  int originalIndex = index;

  while (info[index] != emptyItem) {
    numCollisions++;
    index = (index + 1) % size;
    if (index == originalIndex)
      break;
  }

  info[index] = item;
  numItems++;
}

template <class ItemType>
void HashType<ItemType>::InsertItemQuadratic(ItemType item) {
  int index = Hash(item);
  int originalIndex = index;
  int i = 1;

  while (info[index] != emptyItem) {
    numCollisions++;
    index = (originalIndex + i * i) % size;
    i++;
    if (index == originalIndex)
      break;
  }

  info[index] = item;
  numItems++;
}

template <class ItemType> void HashType<ItemType>::MakeEmpty() {
  numItems = 0;
  for (int i = 0; i < size; i++) {
    info[i] = emptyItem;
  }
}

template <class ItemType> bool HashType<ItemType>::IsFull() const {
  return numItems == size;
}

template <class ItemType> int HashType<ItemType>::GetNumItems() const {
  return numItems;
}

template <class ItemType>
unsigned long int HashType<ItemType>::GetCollisions() const {
  return numCollisions;
}

template <class ItemType> void HashType<ItemType>::Print() const {
  std::cout << "Hash table size: " << size << std::endl;
  std::cout << "Number of collisions  with a = " << a << ": " << numCollisions
            << std::endl;
}

template <class ItemType>
void HashType<ItemType>::RetrieveItem(ItemType &item, bool &found) {
  int location = Hash(item);
  int startLoc = location;
  bool moreToSearch = true;

  while (info[location] != emptyItem && moreToSearch) {
    if (info[location] == item) {
      found = true;
      item = info[location];
      return;
    }
    location = (location + 1) % size;
    moreToSearch = (location != startLoc);
  }
  found = false;
}

template <class ItemType> void HashType<ItemType>::DeleteItem(ItemType item) {
  int location = Hash(item);
  int startLoc = location;

  while (info[location] != emptyItem) {
    if (info[location] == item) {
      info[location] = emptyItem;
      numItems--;
      return;
    }
    location = (location + 1) % size;
    if (location == startLoc)
      break;
  }
}

template <class ItemHash>
std::ostream &operator<<(std::ostream &out, const HashType<ItemHash> &items) {
  for (int i = 0; i < items.size; i++) {
    if (items.info[i] != items.emptyItem) {
      out << items.info[i] << " ";
    }
  }
  return out;
}

#endif
