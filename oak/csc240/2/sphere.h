#include "circleType.h"

class Sphere : public circleType {
public:
  double volume();

protected:
  double xCoordinate;
  double yCoordinate;
  double zCoordinate;
  double radius;
};
