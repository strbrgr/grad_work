#include "pointType.h"
#include <iostream>
#include <ostream>

using namespace std;

void pointType::setPoint(double x, double y)
// Function: Setter function to set x and y coordinates
// Pre: Valid x and y doubles have been passed
// Post: X and y have been initialized
{
    xCoordinate = x;
    yCoordinate = y;
}
void pointType::print() const
// Function: Prints x and y coordinates to the console
// Pre: PointType has been initialized with x and y
// Post: Prints the coordinates in parentheses to the console
{
    cout << "(" << xCoordinate << " , " << yCoordinate << ")" << endl;
}
void pointType::setX(double x)
// Function: Setter for the x coordinate
// Pre: Valid double has been passed for x
// Post: Sets the x coordinate
{
    xCoordinate = x;
}
void pointType::setY(double y)
// Function: Setter for the y coordinate
// Pre: Valid double has been passed for y
// Post: Sets the y coordinate
{
    yCoordinate = y;
}
double pointType::getX() const
// Function: Getter for the x coordinate
// Pre: X has been initialized
// Post: Returns the x coordinate
{
    return xCoordinate;
}
double pointType::getY() const
// Function: Getter for the y coordinate
// Pre: Y has been initialized
// Post: Returns the y coordinate
{
    return yCoordinate;
}
pointType::pointType(double x, double y)
// Function: Constructor function for a pointType
// Pre: Valid double values for x and y has been passed
// Post: Returns a pointType with either 0.0 and 0.0 or valid double values
{
    xCoordinate = x;
    yCoordinate = y;
}