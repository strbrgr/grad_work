// Class circleType

#ifndef H_CircleType
#define H_CircleType

#include "pointType.h"

class circleType : public pointType {
public:
    void print() const;
    // Function: Prints Center and Radius of a Circle
    // Pre: Circle has been initialized
    // Post: Coordinates and radius have been printer
    void setRadius(double r);
    // Function: Sets the radius of a circle
    // Pre: Radius is a valid double
    // Post: Radius has been set to either 0 or the radius
    double getRadius() const;
    // Function: Getter for the radius
    // Pre: Radius has been set
    // Post: Returns the radius
    double getCircumference() const;
    // Function: Calculates the circumeference of a circle
    // Pre: Radius has been initialized
    // Post: Returns circumference calculation
    double getArea() const;
    // Function: Calculates the area of a circle
    // Pre: Radius has been initialized
    // Post: Returns area calculation
    circleType(double x = 0.0, double y = 0.0, double r = 0.0);
    // Function: Constructor function for a circle
    // Pre: Correct double values were provided
    // Post: Sets the radius and inits a PointType with x and y
    void setCenter(pointType&);
    // Function: Sets the Center with a passed pointType
    // Pre: A Valid pointType has been passed
    // Post: x and y will get the point coordinates of the passed point

protected:
    double x;
    double y;
    double radius;
    // Hardcoding PI to avoid calculation time and
    // std::numbers::pi not available until C++20
    const double PI = 3.14159265358979323846;
};

#endif