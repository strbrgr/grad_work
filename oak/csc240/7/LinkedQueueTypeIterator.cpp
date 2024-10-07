#include "LinkedQueueTypeIterator.h"

LinkedQueueTypeIterator::LinkedQueueTypeIterator(NodeType *start, int loc) {
  this->item = start;
  this->location = loc;
  this->start = start;
}

ItemType &LinkedQueueTypeIterator::operator*() { return item->info; }

LinkedQueueTypeIterator &LinkedQueueTypeIterator::operator++() {
  if (item == NULL || item->next == NULL) {
    item = NULL;
  } else {
    item = item->next;
  }
  if (item == start) {
    item = NULL;
  }
  location++;
  return *this;
}

bool LinkedQueueTypeIterator::operator!=(
    const LinkedQueueTypeIterator &it) const {
  return item != it.item;
}
