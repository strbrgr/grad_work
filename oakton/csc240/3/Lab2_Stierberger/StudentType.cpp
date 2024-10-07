#include "StudentType.h"
#include "DateType.h"
#include <iostream>
using namespace std;
void StudentType::Initialize(string newName, DateType newBirthdate,
                             int newStatus)
// Function: Inits the StudnetType
// Pre: Name, birthdate, and status are provided.
// Post: StudentType is initialized
{
  status = newStatus;
  PersonType::Initialize(newName, newBirthdate);
}

int StudentType::GetStatus() const
// Function :Returns the status of the student.
// Post: The student's status is returned as integer
{
  return status;
}

RelationType StudentType::ComparedTo(StudentType &student) {
  // Function: Compares self StudentType with someStudent
  // Pre: A valid StudentType object is provided.
  // Post: Returns RelationType depending on status
  int aStatus = student.GetStatus();

  if (status < aStatus)
    return LESS;
  else if (status > aStatus)
    return GREATER;
  else
    return EQUAL;
}

DateType StudentType::BirthdateIs()
// Function: Returns the birthdate of the student.
// Post: DateType is returned
{
  return PersonType::BirthdateIs(); // notice the use of the scope for
                                    // PersonType here.
}

void StudentType::Print()
// Function: Prints the name, birthdate, and status of the student.
// Post: Prints name and status
{
  PersonType::Print(); // use the Print function of PersonType here.
  cout << "Status: " << status << endl;
}
