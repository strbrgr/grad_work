#ifndef STUDENTTYPE_H
#define STUDENTTYPE_H
#include "PersonType.h"
enum StudentStatus {
  NON_ATTENDING,
  ENROLLED,
  GRADUATED
}; // notice the enumeration here for status
class StudentType : public PersonType {
public:
  void Initialize(string, DateType, int);
  // Function: Inits the StudnetType
  // Pre: Name, birthdate, and status are provided.
  // Post: StudentType is initialized
  int GetStatus() const;
  // Function :Returns the status of the student.
  // Post: The student's status is returned as integer
  RelationType ComparedTo(StudentType &someStudent);
  // Function: Compares self StudentType with someStudent
  // Pre: A valid StudentType object is provided.
  // Post: Returns RelationType depending on status
  DateType BirthdateIs();
  // Function: Returns the birthdate of the student.
  // Post: DateType is returned
  void Print();
  // Function: Prints the name, birthdate, and status of the student.
  // Post: Prints name and status

private:
  int status;
};
typedef StudentType ItemType; // notice this is used to allow ItemType to be
                              // identified as a StudentType
// The only way around this line of code above would be to use a template,
// but the author doesn't get into it until Chapter 6...
#endif
