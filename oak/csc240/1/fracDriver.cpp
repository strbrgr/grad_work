// Test driver
#include <fstream>
#include <iostream>
#include <string>
#include "frac.h"
int main() {
  FractionType one;
  FractionType two;
  one.Initialize(2, 3);
  two.Initialize(4, 5);
  FractionType three = one + two;
  three.print();

  // Test the + operator
  FractionType x;
  FractionType y;
  x.Initialize(1, 3);
  y.Initialize(2, 3);
  FractionType z = x + y;
  z.print();

  z.reduce();
  z.print();

  FractionType g;
  g.Initialize(15, 20);
  g.reduce();
  g.print();

  // Test the - operator
  FractionType four;
  FractionType five;
  four.Initialize(1, 3);
  five.Initialize(4, 3);
  FractionType six = five - four;
  six.print();

  // Test the / operator
  FractionType seven;
  FractionType eight;
  seven.Initialize(5, 3);
  eight.Initialize(8, 9);
  FractionType nine = seven / eight;
  nine.print();

  // Test the * operator
  FractionType ten;
  FractionType eleven;
  ten.Initialize(3, 2);
  eleven.Initialize(5, 12);
  FractionType twelve = ten * eleven;
  twelve.print();
}
