#include "circleType.h"
#include "pointType.h"
#include <iostream>

using namespace std;

int main() {

  pointType point1(3.5, 2.5);
  pointType point2;
  cout << "Point 1: ";
  point1.print();
  cout << endl;

  point2.setPoint(-2.5, 7);
  cout << "Point 2: ";
  point2.print();
  cout << endl;
}
