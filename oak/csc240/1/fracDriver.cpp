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
}
