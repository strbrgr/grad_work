#include "circleType.h"

class Sphere : public circleType {
public:
    Sphere(double x = 0.0, double y = 0.0, double z = 0.0, double r = 0.0);
    // Function: Constructor for Sphere
    // Pre: Valid double values for x, y, and z
    // Post: Initializes the base circleType with x and y, and sets z coordinate to z
    double volume() const;
    // Function: Calculates the volume of a sphere
    // Pre: circleType has been initialized
    // Post: Returns the volume calculation
    double getZ() const;
    // Function: Getter for the z coordinate
    // Pre: Z has been initialized
    // Post Returns the z coordinate

protected:
    double zCoordinate;
};
