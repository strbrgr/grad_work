#include "StackType.h"
#include "ItemType.h"
#include <iostream>

using namespace std;

StackType::StackType()
// Function :constructor
// Post: Initializes empty list
{
  topPtr = NULL;
  currentPos = NULL;
  length = 0;
}

StackType::~StackType()
// Destructor
{
  NodeType *tempPtr;
  while (topPtr != NULL) {
    tempPtr = topPtr;
    topPtr = topPtr->next;
    delete tempPtr;
  }
}

bool StackType::isEmpty() const
// Function: Returns a boolean if the stack is empty
// Pre: Stack has been initialized
// Post: Boolean has been returned, stack is unchanged
{
  return (topPtr == NULL);
}

bool StackType::isFull() const
// Function: Returns a boolean if the stack is full
// Pre: Stack has been initialized
// Post: Boolean has been returned, stack is unchanged
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

void StackType::Push(ItemType newItem)
// Function: Adds an item to the top of the stack
// Pre: Stack has been initialized
// Post: item is at the top of the stack
{
  if (isFull())
    throw FullStack();
  else {
    NodeType *location;
    location = new NodeType;
    location->info = newItem;
    location->next = topPtr;
    topPtr = location;
    length++;
  }
}

void StackType::Pop()
// Function: Throws Exception if Stack is Empty otherwise Removes the item at
// the top of the stack by decreasing top
// Pre: Stack has been initialized
// Post: Top is decreased by 1
{
  if (isEmpty())
    throw EmptyStack();
  else {
    NodeType *tempPtr;
    tempPtr = topPtr;
    topPtr = topPtr->next;
    delete tempPtr;
    length--;
  }
}

ItemType StackType::Top() const
// Function: Throws Exception if Stack is Empty otherwise returns item at the
// top
// Pre: Stack has been initialized
// Post: Top item is returned, stack is
// unchanged
{
  if (isEmpty())
    throw EmptyStack();
  else {
    return topPtr->info;
  }
}

void StackType::Print()
// Function: Prints contents of the stack or empty stack
// post: Value has been sent to the stream out.
{
  if (isEmpty()) {
    cout << "Empty stack." << endl;
  } else {
    cout << "The list: " << endl;
    currentPos = NULL;
    while (currentPos == NULL || currentPos->next != NULL) {
      GetNextItem().Print(cout);
      cout << " ";
    }
  }
  cout << endl;
}

int StackType::GetLength() const
// Function: Returns integer top
// Pre: Stack has been initialized
// Post: Length is returned
{
  return length;
}

ItemType StackType::GetNextItem()
// Function: Gets the next element in list.
// Pre:  List has been initialized and has not been changed since last call.
//       Current position is defined.
//       Element at current position is not last in list.
//
// Post: Current position is updated to next position.
//       item is a copy of element at current position.
{
  if (currentPos == NULL) // start at the beginning
    currentPos = topPtr;
  else // move to the next item
    currentPos = currentPos->next;
  ItemType item((currentPos->info).GetValue());
  return item;
}
