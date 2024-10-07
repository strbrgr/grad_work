#ifndef LINKEDQUEUETYPEITERATOR_H
#define LINKEDQUEUETYPEITERATOR_H
#include "NodeType.h"
#include <stddef.h>

class LinkedQueueTypeIterator {
public:
  // Customize the constructor to work with the ADT.
  LinkedQueueTypeIterator(NodeType *start, int loc);

  ItemType &operator*();

  // Customize to return the proper iterator class.
  LinkedQueueTypeIterator &operator++();

  // Customize to receive the correct Iterator class.
  bool operator!=(const LinkedQueueTypeIterator &it) const;

private:
  // The start of the linked list.
  NodeType *item;
  int location;
  NodeType *start;
};
#endif
