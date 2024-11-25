#ifndef LARGEINT_H
#define LARGEINT_H
// This file contains the coded functions from the text.
// The implementations are incomplete.

#include "SpecializedList.h" // Gain access to SpecializedList
#include <bitset>
#include <cmath>
#include <fstream>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

using namespace std;
enum SignType { PLUS, MINUS };
enum RelationType { LESS, GREATER, EQUAL };

class LargeInt {
public:
  LargeInt();
  LargeInt(string);
  LargeInt(const LargeInt &);
  LargeInt &operator=(const LargeInt &);
  bool operator<(LargeInt second);
  bool operator==(LargeInt second);
  LargeInt operator+(LargeInt second);
  LargeInt operator-(LargeInt second);
  LargeInt operator*(LargeInt second);
  LargeInt Multiply(LargeInt second);
  void InsertDigit(int);
  void InsertDigitFront(int);
  friend ostream &operator<<(ostream &, LargeInt &);

private:
  SpecializedList number;
  SignType sign;
};

LargeInt::LargeInt() { sign = PLUS; }

// IT 5/9/2019
LargeInt &LargeInt::operator=(const LargeInt &large) {
  // cout << "Called assignment operator." << endl;
  if (this != &large) {
    sign = large.sign;
    number = large.number; // SpecializedList assignment operator=
  }
  return *this;
}

// IT 5/6/2019
LargeInt::LargeInt(const LargeInt &anotherLargeInt) {
  sign = anotherLargeInt.sign;
  number = anotherLargeInt.number;
}

LargeInt::LargeInt(string num) {
  sign = PLUS;
  int firstDigitPosition; // Position of first digit in intString
  int lastDigitPosition;  // Position of last digit in intString

  // Used to translate character to byte
  char digitChar;
  int digitInt;
  unsigned char digitByte;

  firstDigitPosition = 0;
  if (num[0] == '+') { //  Skip leading plus sign
    firstDigitPosition = 1;
    sign = PLUS;
  } else if (num[0] == '-') // Handle leading minus sign
  {
    firstDigitPosition = 1;
    sign = MINUS;
  }

  lastDigitPosition = num.size() - 1;

  // Skip leading zeros.
  int i = firstDigitPosition;
  while (num[i] == '0') {
    i++;
  }
  firstDigitPosition = i;

  if (firstDigitPosition > lastDigitPosition) { // This number is equal to 0.
    InsertDigit(0);
  } else {
    for (int count = firstDigitPosition; count <= lastDigitPosition; count++) {
      digitChar = num[count];
      digitInt = digitChar - '0';
      digitByte = (unsigned char)digitInt;
      InsertDigit(digitByte);
    }
  }
}

void Add(SpecializedList first, SpecializedList second, SpecializedList &result)
// Post:  result = first + second.
{
  SpecializedList finalResult;
  int carry = 0;
  bool finished1 = false;
  bool finished2 = false;
  int temp;
  int digit1;
  int digit2;

  first.ResetBackward();
  second.ResetBackward();

  // What to do when adding a LargeInt with a value of NULL?
  if (first.IsListNull() && second.IsListNull()) {
    finalResult.PutFront(0);
  } else if (first.IsListNull()) {
    while (!finished2) {
      second.GetPriorItem(digit2, finished2);
      finalResult.PutFront(digit2);
    }
  } else if (second.IsListNull()) {
    while (!finished1) {
      first.GetPriorItem(digit1, finished1);
      finalResult.PutFront(digit1);
    }
  } else {
    while (!finished1 && !finished2) {
      first.GetPriorItem(digit1, finished1);
      second.GetPriorItem(digit2, finished2);
      temp = digit1 + digit2 + carry;
      carry = temp / 10;
      finalResult.PutFront(temp % 10);
    }

    while (!finished1) { // Adds remaining digits (if any) in first to the sum.
      first.GetPriorItem(digit1, finished1);
      temp = digit1 + carry;
      carry = temp / 10;
      finalResult.PutFront(temp % 10);
    }

    while (!finished2) { // Adds remaining digits (if any) in second to the sum.
      second.GetPriorItem(digit2, finished2);
      temp = digit2 + carry;
      carry = temp / 10;
      finalResult.PutFront(temp % 10);
    }

    if (carry != 0) // Adds in carry (if any)
      finalResult.PutFront(carry);
  }

  result = finalResult;
}

void AddThreaded(int multiplier_digit, SpecializedList list, int numZeros,
                 SpecializedList &sum) {
  for (int j = 0; j < multiplier_digit; j++) {
    Add(sum, list, sum);
  }
  for (int k = 0; k < numZeros; k++) {
    sum.PutEnd(0);
  }
}

void Sub(SpecializedList first, SpecializedList second, SpecializedList &result)
// Precondition: first >= second
// IT 5/6/2019
// result a specialized list that is the difference of the two argument lists
{
  int digit1;
  int digit2;
  bool borrow = false;
  bool flag = false;

  int largerLength = first.GetLength();
  int smallerLength = second.GetLength();
  int lengthDiff = (largerLength - smallerLength);

  first.ResetBackward();
  second.ResetBackward();

  // Process both lists while both have digits.
  for (int count = 1; count <= smallerLength; count++) {
    first.GetPriorItem(digit1, flag);
    if (borrow) {
      if (digit1 != 0) {
        digit1 = digit1 - 1;
        borrow = false;
      } else {
        digit1 = 9;
        borrow = true;
      }
    }

    second.GetPriorItem(digit2, flag);
    // Prevent a leading zero when the most significant
    // digits are equal, but allow: 0 - 0 = 0.
    if (digit2 < digit1)
      result.PutFront(digit1 - digit2);
    else if (digit1 == digit2) {
      if (count != smallerLength) {
        result.PutFront(digit1 - digit2);
      } else if (count == smallerLength and (lengthDiff != 0 or count == 1)) {
        result.PutFront(digit1 - digit2);
      }
    } else {
      borrow = true;
      result.PutFront(digit1 + 10 - digit2);
    }
  }

  // Finish processing of leftover digits
  for (int count = 1; count <= lengthDiff; count++) {
    first.GetPriorItem(digit1, flag);

    if (borrow) {
      if (digit1 != 0) {
        digit1 = digit1 - 1;
        borrow = false;
      } else {
        digit1 = 9;
        borrow = true;
      }
    }

    if (!flag or digit1 != 0) {
      result.PutFront(digit1);
    }
  }
}

LargeInt LargeInt::operator+(LargeInt second)
// self is first operand
{
  LargeInt result;

  if (sign == second.sign) {
    Add(number, second.number, result.number);
    result.sign = sign;
  } else {
    if (sign == MINUS) {
      sign = PLUS;
      if (*this < second) {
        Sub(second.number, number, result.number);
        result.sign = PLUS;
        sign = MINUS;
      } else {
        Sub(number, second.number, result.number);
        result.sign = MINUS;
        sign = MINUS;
      }
    } else {
      second.sign = PLUS;
      if (second < *this) {
        Sub(number, second.number, result.number);
        result.sign = PLUS;
        second.sign = MINUS;
      } else {
        Sub(second.number, number, result.number);
        result.sign = MINUS;
        second.sign = MINUS;
      }
    }
  }
  return result;
}

LargeInt LargeInt::operator-(LargeInt second)
// self is first operand
{
  SignType selfSign;
  SignType secondSign;
  LargeInt result;
  selfSign = sign;
  secondSign = second.sign;
  if (selfSign == secondSign) {
    if (*this < second) {
      if (sign == PLUS) {
        Sub(second.number, number, result.number);
        result.sign = MINUS;
      } else {
        sign = PLUS;
        Sub(number, second.number, result.number);
        result.sign = MINUS;
        sign = MINUS;
      }
    } else {
      if (sign == PLUS) {
        Sub(number, second.number, result.number);
        result.sign = PLUS;
      } else {
        sign = PLUS;
        second.sign = PLUS;
        Sub(second.number, number, result.number);
        result.sign = PLUS;
        sign = MINUS;
        second.sign = MINUS;
      }
    }
  } else {
    Add(second.number, number, result.number);
    result.sign = secondSign == MINUS ? PLUS : MINUS;
  }
  return result;
}

RelationType CompareDigits(SpecializedList first, SpecializedList second) {
  bool finished = false;
  int digit1;
  int digit2;

  first.ResetForward();
  second.ResetForward();
  while (!finished) {
    first.GetNextItem(digit1, finished);
    second.GetNextItem(digit2, finished);
    if (digit1 < digit2)
      return LESS;
    if (digit1 > digit2)
      return GREATER;
  }
  return EQUAL;
}

bool LargeInt::operator<(LargeInt second) {
  RelationType relation;

  if (sign == MINUS && second.sign == PLUS)
    return true;
  else if (sign == PLUS && second.sign == MINUS)
    return false;
  else if (sign == PLUS &&
           number.GetLength() < second.number.GetLength()) // both PLUS
    return true;
  else if (sign == PLUS &&
           number.GetLength() > second.number.GetLength()) // both PLUS
    return false;
  else if (sign == MINUS &&
           number.GetLength() > second.number.GetLength()) // both MINUS
    return true;
  else if (sign == MINUS &&
           number.GetLength() < second.number.GetLength()) // both MINUS
    return false;
  else { // Must compare digit by digit
    relation = CompareDigits(number, second.number);
    if (sign == PLUS && relation == LESS) {
      return true;
    } else if (sign == PLUS && relation == GREATER) {
      return false;
    } else if (sign == MINUS && relation == GREATER) {
      return true;
    } else {
      return false;
    }
  }
}

void LargeInt::InsertDigit(int digit) { number.PutEnd(digit); }

void LargeInt::InsertDigitFront(int digit) { number.PutFront(digit); }

ostream &operator<<(ostream &out, LargeInt &largeInt) {
  int digit;
  bool flag = false;
  string largeIntString;
  if (largeInt.sign == PLUS)
    largeIntString = "+";
  else
    largeIntString = "-";

  int length;
  char d;
  length = largeInt.number.GetLength();
  largeInt.number.ResetForward();
  for (int count = length; count >= 1; count--) {
    largeInt.number.GetNextItem(digit, flag);
    d = '0' + digit;
    largeIntString += d;
    if ((((count - 1) % 3) == 0) && (count != 1))
      largeIntString = largeIntString + ",";
  }
  out << largeIntString;
  return out;
}

// Karatsuba implementation
// see https://en.wikipedia.org/wiki/Karatsuba_algorithm
// last referenced: 10/31/24
LargeInt LargeInt::operator*(LargeInt second) {
  // Base case
  if (number.GetLength() == 1 && second.number.GetLength() == 1) {
    int digit1 = 0, digit2 = 0;
    bool finished1 = false, finished2 = false;
    number.ResetForward();
    second.number.ResetForward();
    number.GetNextItem(digit1, finished1);
    second.number.GetNextItem(digit2, finished2);

    int product = digit1 * digit2;
    LargeInt result;

    if (product >= 10) {
      result.InsertDigit(product / 10);
      result.InsertDigit(product % 10);
    } else {
      result.InsertDigit(product);
    }

    result.sign = (sign == second.sign) ? PLUS : MINUS;
    return result;
  }

  // Get lengths and determine split point
  int n1 = number.GetLength();
  int n2 = second.number.GetLength();
  int m = max(n1, n2);
  int m2 = m / 2;

  // Create temp lists
  SpecializedList high1, low1, high2, low2;

  // Split 1st number
  bool finished = false;
  number.ResetForward();
  for (int i = 0; i < n1; i++) {
    int digit;
    number.GetNextItem(digit, finished);
    if (i < n1 - m2) {
      high1.PutEnd(digit);
    } else {
      low1.PutEnd(digit);
    }
  }

  // Split 2nd number
  finished = false;
  second.number.ResetForward();
  for (int i = 0; i < n2; i++) {
    int digit;
    second.number.GetNextItem(digit, finished);
    if (i < n2 - m2) {
      high2.PutEnd(digit);
    } else {
      low2.PutEnd(digit);
    }
  }

  LargeInt x1, x0, y1, y0;
  x1.number = high1;
  x0.number = low1;
  y1.number = high2;
  y0.number = low2;

  // Calculate according to formula.
  // This uses recursion via operator*
  LargeInt z0 = x0 * y0;
  LargeInt z2 = x1 * y1;
  LargeInt sum1 = x1 + x0;
  LargeInt sum2 = y1 + y0;
  LargeInt z1 = sum1 * sum2 - z2 - z0;

  // Combine results
  for (int i = 0; i < 2 * m2; i++) {
    z2.InsertDigit(0);
  }
  for (int i = 0; i < m2; i++) {
    z1.InsertDigit(0);
  }

  LargeInt result = z2 + z1 + z0;
  // Apply the correct sign
  result.sign = (sign == second.sign) ? PLUS : MINUS;

  return result;
}

#endif
