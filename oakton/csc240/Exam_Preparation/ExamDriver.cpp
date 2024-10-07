#include "LinkedList.h"

int main() {
  LinkedList list;
  list.PutItem(ItemType(3));
  list.PutItem(ItemType(3));
  list.PutItem(ItemType(3));
  list.PutItem(ItemType(3));
  list.Print();
}
