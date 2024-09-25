#include <string>

using namespace std;

class Bowler {
public:
 Bowler();
// Function :constructor
// Post: Initializes 'firstName' to default firstName

 Bowler(string fName);
// Function: constructor with param
// Post: Initializes 'firstName' to 'firstName'

string getBowler() const;
// Function: Returns the name of the Bowler
// Pre: Bowler has been initialized
// Post: Bowler's name is returned

bool operator==(const Bowler& other) const;
// Function: Creates a Bowler and adds two operands
// Pre: Bowler has been initialized
// Post: Returns a FractionType where operand 2 has been added to operand 1
private:
  string firstName;
};
