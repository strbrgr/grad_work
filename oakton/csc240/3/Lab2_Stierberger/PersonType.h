#ifndef PERSONTYPE_H
#define PERSONTYPE_H
#include <string>
using namespace std;
#include "DateType.h"
class PersonType {
public:
  void Initialize(string, DateType);
  // Function: Inits PersonType with a name and birthdate.
  // Pre: Name and birthdate are provided.
  // Post: PersonType initialized with name and birthdate.
  string NameIs();
  // Function: Returns the name of the person.
  // Post: Name as string returned
  RelationType ComparedTo(PersonType &somePerson);
  // Function: Compares self with somePerson
  // Pre: Valid PersonType is provided
  // Post: RelationType is returned
  DateType BirthdateIs();
  // Function: Returns birthdate DateType
  // Pre: PersonType is initialized
  void Print();
  // Function: Prints the name
  // Pre: PersonType is initialized

private:
  string name;
  DateType birthdate;
};

#endif
