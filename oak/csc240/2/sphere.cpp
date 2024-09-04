#include "sphere.h"

Sphere::Sphere(double x, double y, double z, double r)
    : circleType(x, y, r)
    , zCoordinate(z)
// Function: Initializes the base circleType with x and y
// Pre: Valid double values need to be passed
// Post: Creates the sphere
{
}
double Sphere::volume() const
// Function: Calculates the volume of a sphere
// Pre: circleType has been initialized
// Post: Returns the volume calculation
{
    double radius = getRadius();
    // do not use integer divison as it will be truncated to 1
    return (4.0 / 3.0) * PI * radius * radius * radius;
}
double Sphere::getZ() const
// Function: Getter for the z coordinate
// Pre: Z has been initialized
// Post Returns the z coordinate
{
    return zCoordinate;
}
