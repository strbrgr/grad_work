#include "Bowler.h"
#include <iostream>

using namespace std;

Bowler::Bowler()
// Function :constructor
// Post: Initializes 'firstName' to default firstName
{
  firstName = "James";
}

Bowler::Bowler(string fName)
// Function: constructor with param
// Post: Initializes 'firstName' to 'firstName'
{
  firstName = fName;
}

  string Bowler::getBowler() const
// Function: Returns the firstName of the Bowler
// Pre: Bowler has been initialized
// Post: Bowler's firstName is returned
{
    return firstName;
}

bool Bowler::operator==(const Bowler& other) const
// Function: Creates a Bowler and adds two operands
// Pre: Bowler has been initialized
// Post: Returns a FractionType where operand 2 has been added to operand 1
{
  return firstName == other.getBowler();
}
