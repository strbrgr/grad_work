#include "circleType.h"
#include "pointType.h"
#include "sphere.h"
#include <iostream>

using namespace std;

int main()
{

    // Create point1
    pointType point1(3.5, 2.5);
    cout << "Point 1: ";
    point1.print();
    cout << endl;

    // Create point2
    pointType point2;
    point2.setPoint(-2.5, 7);
    cout << "Point 2: ";
    point2.print();
    cout << endl;

    // Create point3 by asking for user input
    double x, y, radius;
    pointType point3;

    cout << "Enter x coordinate: ";
    cin >> x;
    cout << endl;

    cout << "Enter y coordinate: ";
    cin >> y;
    cout << endl;

    cout << "Enter radius: ";
    cin >> radius;
    cout << endl;

    point3.setPoint(x, y);

    cout << "Point 3: ";
    point3.print();
    cout << endl;

    // Create circle1 with coordinates of point3
    circleType circle1(point3.getX(), point3.getY(), radius);
    // Test member functions
    double circle1_circumference = circle1.getCircumference();
    double circle1_area = circle1.getArea();
    cout << "The circumference of a circle with your provided x and y coordinates is: " << circle1_circumference << endl;
    cout << "The area of a circle with your provided x and y coordinates is: " << circle1_area << endl;

    // Create sphere1 with values from circle1
    Sphere sphere1(point3.getX(), point3.getY(), 0.0, radius);
    // Test volume function
    double sphere1_volume = sphere1.volume();
    cout << "The volume of a sphere with the provided radius is: "
         << sphere1_volume << endl;

    return 0;
}
