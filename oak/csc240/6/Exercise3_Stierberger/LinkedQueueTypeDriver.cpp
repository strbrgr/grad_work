#include "LinkedQueueType.h"
#include <iostream>

using namespace std;

int main() {
  LinkedQueueType q;
  q.Enqueue(8);
  q.Enqueue(6);
  q.Enqueue(7);
  q.Enqueue(5);
  q.Enqueue(3);
  q.Enqueue(0);
  q.Enqueue(9);
  q.Print();
  int item;
  q.Dequeue(item);
  cout << item << endl;
  q.Dequeue(item);
  cout << item << endl;
  q.Print();
  LinkedQueueType q2(q);
  // call copy constructor
  q2.Print();
  q2.Dequeue(item);
  cout << item << endl;
  q2.Print();
  LinkedQueueType q1;
  q1 = q; // call assignment operator=
  q1.Print();
  return 0;
}
