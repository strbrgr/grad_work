#include "LinkedQueueType.h"
#include "LinkedQueueTypeIterator.h"
#include "NodeType.h"
#include <iostream>
using namespace std;

LinkedQueueType::LinkedQueueType(const LinkedQueueType &qt) {
  // we start fromt the beginning and overwrite all values
  rear = NULL;
  length = 0;
  if (!qt.IsEmpty()) {
    NodeType *tempPtr = qt.rear->next;
    do {
      Enqueue(tempPtr->info);
      tempPtr = tempPtr->next;
    } while (tempPtr != qt.rear->next);
  }
}

LinkedQueueType LinkedQueueType::operator=(const LinkedQueueType &rhs) {
  // logic is pretty similar to copy contrusctor implementation,
  // however we want to handle differences.
  // if they differ we first make the current queue empty and enqueue all items
  // from rhs
  if (this != &rhs) {
    MakeEmpty();
    if (!rhs.IsEmpty()) {
      NodeType *tempPtr = rhs.rear->next;
      do {
        Enqueue(tempPtr->info);
        tempPtr = tempPtr->next;
      } while (tempPtr != rhs.rear->next);
    }
  }
  return *this;
}

LinkedQueueType::LinkedQueueType() // Default class constructor
// Post: maxQue, front, and rear have been initialized.
//       The array to hold the queue elements has been dynamically
//       allocated.
{

  rear = NULL;
  length = 0;
}

LinkedQueueType::~LinkedQueueType() // Class destructor
{
  MakeEmpty();
}

void LinkedQueueType::MakeEmpty()
// Post: rear and length have been reset to the empty state.
{
  NodeType *tempPtr;
  while (!IsEmpty()) {
    tempPtr = rear->next;
    if (rear == tempPtr) {
      delete rear;
      rear = NULL;
    } else {
      rear->next = tempPtr->next;
      delete tempPtr;
    }
  }
}

bool LinkedQueueType::IsEmpty() const
// Returns true if the queue is empty; false otherwise.
{
  return (length == 0);
}

bool LinkedQueueType::IsFull() const
// This structure can net get full.
{
  return false;
}

void LinkedQueueType::Enqueue(ItemType newItem)
// Post: If (queue is not full) newItem is at the rear of the queue; newItem's
// next is front
//       otherwise a FullQueue exception is thrown.
{
  if (IsFull())
    throw FullQueue();
  else {
    // set up new node
    NodeType *newNode;
    newNode = new NodeType;
    newNode->info = newItem;
    newNode->next = NULL;
    // empty q
    if (rear == NULL) {
      rear = newNode;
      // set up circularity
      rear->next = rear;
    } else {
      // set new nodes next pointer to the front
      newNode->next = rear->next;
      // insert the new node
      rear->next = newNode;
      rear = newNode;
    }
    length++;
  }
}

void LinkedQueueType::Dequeue(ItemType &item)
// Post: If (queue is not empty) the front of the queue has been
//       removed and a copy returned in item;
//       othersiwe a EmptyQueue exception has been thrown.
{
  if (IsEmpty())
    throw EmptyQueue();
  else {
    NodeType *front = rear->next;

    if (rear == front) {
      delete front;
      rear = NULL;
    } else {
      // skip one element by pointer reassignment
      rear->next = front->next;
      delete front;
    }
    length--;
  }
}

void LinkedQueueType::Print() {
  NodeType *node = rear->next;
  int count = 0;
  while (count < length) {
    cout << node->info << " ";
    node = node->next;
    count++;
  }
  cout << endl;
}

//
// The methods below provide the range-based for loop support. These would
// be customized with the companion LinkedQueueTypeIterator class that is
// returned.
//
LinkedQueueTypeIterator LinkedQueueType::begin() {
  NodeType *start = rear->next;
  return LinkedQueueTypeIterator(start, 0);
}

LinkedQueueTypeIterator LinkedQueueType::end() {
  return LinkedQueueTypeIterator(NULL, length);
}
