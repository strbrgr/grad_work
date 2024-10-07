#include "PersonType.h"
#include <iostream>
using namespace std;
void PersonType::Initialize(string n, DateType dob)
// Function: Inits PersonType with a name and birthdate.
// Pre: Name and birthdate are provided.
// Post: PersonType initialized with name and birthdate.
{
  name = n;
  birthdate = dob;
}

string PersonType::NameIs()
// Function: Returns the name of the person.
// Post: Name as string returned
{
  return name;
}

RelationType PersonType::ComparedTo(PersonType &somePerson)
// Function: Compares self with somePerson
// Pre: Valid PersonType is provided
// Post: RelationType is returned
{
  return birthdate.ComparedTo(somePerson.birthdate);
}

DateType PersonType::BirthdateIs()
// Function: Returns birthdate DateType
// Pre: PersonType is initialized
{
  return birthdate;
}

void PersonType::Print()
// Function: Prints the name
// Pre: PersonType is initialized
{
  cout << "Name: " << name << endl;
}
