#include "LinkedQueueType.h"
#include <iostream>

using namespace std;

LinkedQueueType::LinkedQueueType()
// Class constructor. Because there is a default
// constructor, the precondition that the queue has been
// initialized is omitted.
{
  rear = NULL;
  length = 0;
}

LinkedQueueType::LinkedQueueType(const LinkedQueueType &qt)
// Copy Constructor
{
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

LinkedQueueType LinkedQueueType::operator=(const LinkedQueueType &rhs)
// Overloaded assignment operator=
{
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

LinkedQueueType::~LinkedQueueType()
// Destructor
{
  MakeEmpty();
}

void LinkedQueueType::MakeEmpty()
// Function: Initializes the queue to an empty state.
// Post: Queue is empty.
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
// Function: Determines whether the queue is empty.
// Post: Function value = (queue is empty)
{
  return (rear == NULL);
}

bool LinkedQueueType::IsFull() const
// Function: Determines whether the queue is full.
// Post: Function value = (queue is full)
{
  NodeType *location;
  try {
    location = new NodeType;
    delete location;
    return false;
  } catch (std::bad_alloc exc) {
    return true;
  }
}

void LinkedQueueType::Enqueue(ItemType newItem)
// Function: Adds newItem to the rear of the queue.
// Post: newItem is at rear of queue.
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
  }
}

void LinkedQueueType::Dequeue(ItemType &item)
// Function: Removes front item from the queue and returns it in item.
// Post: If (queue is empty) EmptyQueue exception is thrown and item is
// undefined else front element has been removed from queue and item is a copy
// of removed element.
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
  }
}

void LinkedQueueType::Print()
// Function: Prints contents of the queue or empty queue
// post: Value has been sent to the stream out.
{
  if (IsEmpty()) {
    cout << "Empty queue." << endl;
  } else {
    cout << "The queue: " << endl;
    NodeType *tempPtr = rear->next;

    do {
      cout << tempPtr->info << " ";
      tempPtr = tempPtr->next;
    } while (tempPtr != rear->next);
    cout << endl;
  }
  cout << endl;
}
