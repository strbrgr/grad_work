#include "LinkedList.h"

int main() {
  LinkedList list;
  list.PutItemFront(ItemType(3));
  list.PutItemFront(ItemType(3));
  list.PutItemFront(ItemType(3));
  list.PutItemFront(ItemType(3));
  list.Print();
}
