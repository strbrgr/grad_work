#include "circleType.h"
#include "pointType.h"
#include <iostream>

using namespace std;

// Hardcoding PI to avoid calculation time and
// std::numbers::pi not available until C++20
const double PI = 3.14159265358979323846;

void circleType::print() const {
  cout << "center: ";
  pointType::print();
  cout << "radius = " << radius << endl;
};
//
void circleType::setRadius(double r)
//
{
  radius = r;
}
double circleType::getRadius() const
//
{
  return radius;
}
double circleType::getCircumference() const
//
{
  return 2 * PI * radius;
};
double circleType::getArea() const
//
{
  return PI * radius * radius;
}
circleType::circleType(double x, double y, double r)
    : pointType(x, y)
//
{
  radius = r;
};

void circleType::setCenter(pointType &) {};
