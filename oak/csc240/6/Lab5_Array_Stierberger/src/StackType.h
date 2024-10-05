#include "ItemType.h"

class FullStack {};
class EmptyStack {};

class StackType {
public:
  StackType();
  // Function :constructor
  // Post: Initializes 'limit' to 500
  StackType(int max);
  // Function: constructor with param
  // Post: Initializes 'limit' to 'max'
  ~StackType();
  // Destructor
  bool isEmpty() const;
  // Function: Returns a boolean if the stack is empty
  // Pre: Stack has been initialized
  // Post: Boolean has been returned, stack is unchanged
  bool isFull() const;
  // Function: Returns a boolean if the stack is full
  // Pre: Stack has been initialized
  // Post: Boolean has been returned, stack is unchanged
  void Push(ItemType item);
  // Function: Adds an item to the top of the stack
  // Pre: Stack has been initialized
  // Post: item is at the top of the stack
  void Pop();
  // Function: Throws Exception if Stack is Empty otherwise Removes the item at
  // the top of the stack by decreasing top
  // Pre: Stack has been initialized
  // Post: Top is decreased by 1
  ItemType Top() const;
  // Function: Throws Exception if Stack is Empty otherwise returns item at the
  // top
  // Pre: Stack has been initialized
  // Post: Top item is returned, stack is
  // unchanged
  void Print();
  // Function: Prints contents of the stack or empty stack
  // post: Value has been sent to the stream out.
  int GetLength() const;
  // Function: Returns integer top
  // Pre: Stack has been initialized
  // Post: Length is returned
  friend bool Identical(const StackType &stack1, const StackType &stack2);
  // Function: Determines if two stacks are identical.
  // Preconditions: stack1 and stack2 have been initialized.
  // Postconditions: stack1 and stack2 are unchanged.
  // Function return value = stack1 and stack2 are identical

private:
  int top;
  int limit;
  ItemType *info;
};
