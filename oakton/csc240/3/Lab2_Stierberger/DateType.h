#ifndef DATETYPE_H
#define DATETYPE_H
#include <fstream>
#include <string>

using namespace std;
// Declare a class to represent the Date ADT
// This is file DateType.h.
enum RelationType { LESS, EQUAL, GREATER };
// Compares self with someDate.
class DateType {
public:
  void Initialize(int newMonth, int newDay, int newYear);
  // Post: If newMonth, newDay and newYear represent a valid date,
  //       year is set to newYear;
  //       month is set to newMonth;
  //       day is set to newDay;
  //       otherwise a string exception is thrown, stating the
  //       first incorrect parameter.
  int GetMonth() const;
  // Accessor function for data member month.
  int GetYear() const;
  // Accessor function for data member year.
  int GetDay() const;
  // Accessor function for data member day.
  string GetMonthAsString() const;
  // Returns month as a string
  DateType Adjust(int daysAway) const;
  // Pre:  Self has been initialized
  // Post: Function value = newDate daysAway from self
  RelationType ComparedTo(DateType someDate) const;
  // Function: Compares DateType self with DateType someDate and returns
  // ReltionType
  // Pre:  Self and aDate have been initialized. Post: Function
  // value = LESS, if self comes before aDate.
  //                      = EQUAL, if self is the same as aDate.
  //                      = GREATER, if self comes after aDate.

private:
  int year;
  int month;
  int day;
};
#endif
