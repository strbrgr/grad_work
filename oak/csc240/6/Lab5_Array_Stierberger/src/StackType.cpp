#include "StackType.h"
#include "ItemType.h"
#include <iostream>

using namespace std;

StackType::StackType()
// Function :constructor
// Post: Initializes 'limit' to 500
{
  top = -1;
  limit = 500;
  info = new ItemType[limit];
}

StackType::StackType(int max)
// Function: constructor with param
// Post: Initializes 'limit' to 'max'
{
  top = -1;
  limit = max;
  info = new ItemType[limit];
}

StackType::~StackType()
// Destructor
{
  delete[] info;
}

bool StackType::isEmpty() const
// Function: Returns a boolean if the stack is empty
// Pre: Stack has been initialized
// Post: Boolean has been returned, stack is unchanged
{
  return (top == -1);
}

bool StackType::isFull() const
// Function: Returns a boolean if the stack is full
// Pre: Stack has been initialized
// Post: Boolean has been returned, stack is unchanged
{
  return (top == limit - 1);
}

void StackType::Push(ItemType newItem)
// Function: Adds an item to the top of the stack
// Pre: Stack has been initialized
// Post: item is at the top of the stack
{
  if (isFull())
    throw FullStack();
  top++;
  info[top] = newItem;
}

void StackType::Pop()
// Function: Throws Exception if Stack is Empty otherwise Removes the item at
// the top of the stack by decreasing top
// Pre: Stack has been initialized
// Post: Top is decreased by 1
{
  if (isEmpty())
    throw EmptyStack();
  top--;
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
  return info[top];
}

void StackType::Print()
// Function: Prints contents of the stack or empty stack
// post: Value has been sent to the stream out.
{
  if (isEmpty()) {
    cout << "Empty stack." << endl;
  } else {
    cout << "The stack: " << endl;
    for (int i = 0; i <= top; i++) {
      info[i].Print(cout);
      cout << " ";
    }
    cout << endl;
  }
}

int StackType::GetLength() const
// Function: Returns integer top
// Pre: Stack has been initialized
// Post: Length is returned
{
  return top;
}
