#include "ItemType.h"
#include "StackType.h"
#include <iostream>

using namespace std;

// Implement ReplaceItem and Identical here in the driver file.
void ReplaceItem(StackType &stack, ItemType oldItem, ItemType newItem)
// Function: Replaces all occurrences of oldItem with newItem.
// Precondition: stack has been initialized.
// Postcondition: Each occurrence of oldItem in stack has been replaced by
// newItem.
{
  StackType temp;
  while (!stack.isEmpty()) {
    ItemType curr = stack.Top();
    stack.Pop();
    if (curr.ComparedTo(oldItem) == EQUAL) {
      temp.Push(newItem);
    } else {
      temp.Push(curr);
    }
  }

  while (!temp.isEmpty()) {
    ItemType curr = temp.Top();
    temp.Pop();
    stack.Push(curr);
  }
}

bool Identical(const StackType &stack1, const StackType &stack2)
// Function: Determines if two stacks are identical.
// Preconditions: stack1 and stack2 have been initialized.
// Postconditions: stack1 and stack2 are unchanged.
// Function return value = stack1 and stack2 are identical
{
  if (stack1.GetLength() != stack2.GetLength()) {
    return false;
  }

  // This is inefficient for large stacks, however the stack
  // implementation does not allow modifications
  StackType stack1_copy = stack1;
  StackType stack2_copy = stack2;

  while (!stack1_copy.isEmpty() && !stack2_copy.isEmpty()) {
    ItemType stack1_copy_item = stack1_copy.Top();
    stack1_copy.Pop();
    ItemType stack2_copy_item = stack2_copy.Top();
    stack2_copy.Pop();

    if (stack1_copy_item.ComparedTo(stack2_copy_item) != EQUAL) {
      return false;
    }
  }

  return true;
}

int main() {
  try {
    StackType stack;
    stack.Print();
    stack.Push(4);
    stack.Push(4);
    stack.Push(5);
    stack.Push(4);
    stack.Push(3);
    stack.Push(4);
    stack.Print();
    ReplaceItem(stack, 4, 8);
    stack.Print();
    StackType myStack;
    myStack.Print();
    myStack.Push(4);
    myStack.Push(4);
    myStack.Push(5);
    myStack.Push(4);
    myStack.Push(3);
    myStack.Push(4);
    myStack.Print();
    if (Identical(stack, myStack)) {
      cout << "The stacks are identical." << endl;
    } else {
      cout << "The stacks are NOT identical." << endl;
    }
  } catch (const FullStack &e) {
    cout << "Stack is full!" << endl;
  } catch (const EmptyStack &e) {
    cout << "Stack is empty!" << endl;
  }
  return 0;
}
