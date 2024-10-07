// Class pointType

#ifndef H_PointType
#define H_PointType

class pointType {
public:
    void setPoint(double x, double y);
    // Function: Setter function to set x and y coordinates
    // Pre: Valid x and y doubles have been passed
    // Post: X and y have been initialized
    void print() const;
    // Function: Prints x and y coordinates to the console
    // Pre: PointType has been initialized with x and y
    // Post: Prints the coordinates in parentheses to the console
    void setX(double x);
    // Function: Getter for the x coordinate
    // Pre: Valid double has been passed for x
    // Post: Sets the x coordinate
    void setY(double y);
    // Function: Setter for the x coordinate
    // Pre: Valid double has been passed for y
    // Post: Sets the y coordinate
    double getX() const;
    // Function: Getter for the x coordinate
    // Pre: X has been initialized
    // Post: Returns the x coordinate
    double getY() const;
    // Function: Getter for the y coordinate
    // Pre: Y has been initialized
    // Post: Returns the y coordinate
    pointType(double x = 0.0, double y = 0.0);
    // Function: Constructor function for a pointType
    // Pre: Valid double values for x and y has been passed
    // Post: Returns a pointType with either 0.0 and 0.0 or valid double values

protected:
    double xCoordinate;
    double yCoordinate;
};

#endif
