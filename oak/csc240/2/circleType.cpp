#include "circleType.h"
#include "pointType.h"
#include <iostream>

using namespace std;

void circleType::print() const
// Function: Prints Center and Radius of a Circle
// Pre: Circle has been initialized
// Post: Coordinates and radius have been printer
{
    cout << "center: ";
    pointType::print();
    cout << "radius = " << radius << endl;
}
void circleType::setRadius(double r)
// Function: Sets the radius of a circle
// Pre: Radius is a valid double
// Post: Radius has been set to either 0 or the radius
{
    if (r >= 0) {
        radius = r;
    } else {
        radius = 0;
    }
}
double circleType::getRadius() const
// Function: Getter for the radius
// Pre: Radius has been set
// Post: Returns the radius
{
    return radius;
}
double circleType::getCircumference() const
// Function: Calculates the circumeference of a circle
// Pre: Radius has been initialized
// Post: Returns circumference calculation
{
    return 2 * PI * radius;
}
double circleType::getArea() const
// Function: Calculates the area of a circle
// Pre: Radius has been initialized
// Post: Returns area calculation
{
    return PI * radius * radius;
}
circleType::circleType(double x, double y, double r)
    : pointType(x, y)
    , radius(r)
// Function: Constructor function for a circle
// Pre: Correct double values were provided
// Post: Sets the radius and inits a PointType with x and y
{
}
void circleType::setCenter(pointType& point)
// Function: Sets the Center with a passed pointType
// Pre: A Valid pointType has been passed
// Post: x and y will get the point coordinates of the passed point
{
    setX(point.getX());
    setY(point.getY());
}
