// Implementation file for class FractionType
#include "frac.h"
#include <stdlib.h>
#include <iostream>

void FractionType::Initialize(int numerator, int denominator)
// Function: Initialize the fraction
// Pre:  None
// Post: numerator is stored in num; denominator is stored in
//       denom
{
  if (denominator == 0) {
	  throw std::invalid_argument("Denominator cannot be zero");
  }
  num = numerator;
  denom = denominator;
}

int FractionType::NumeratorIs()
// Function: Returns the value of the numerator
// Pre:  Fraction has been initialized
// Post: numerator is returned
{
  return num;
}

int FractionType::DenominatorIs()
// Function: Returns the value of the denominator
// Pre:  Reaction has been initialized
// Post: denominator is returned
{
  return denom;
}

bool FractionType::IsZero()
// Function: Determines if fraction is zero
// Pre:  Fraction has been initialized
// Post: Returns true if numerator is zero
{
  return (num == 0);
}

bool FractionType::IsNotProper()
// Function: Determines if fraction is a proper fraction
// Pre:  Fraction has been initialized
// Post: Returns true if num is greater than or equal to denom
{
  return (abs(num) >= abs(denom));
}

int FractionType::ConvertToProper()
// Function: Converts the fraction to a whole number and a
//       fractional part
// Pre:  Fraction has been initialized, is in reduced form, and
//       is not a proper fraction
// Post: Returns num divided by denom
//       num is original num % denom; denom is not changed
{
  int result;
  result = num / denom;
  num = num % denom;
  return result;
}

FractionType FractionType::operator+(const FractionType& addend)
// Function: Creates a FractionType and adds two operands
// Pre: Fraction has been initialized
// Post: Returns a FractionType where operand 2 has been added to operand 1
{
  FractionType fra;
  fra.num = ((num * addend.denom) + (denom * addend.num));
  fra.denom = denom * addend.denom;
  fra.reduce();
  return fra;
}

FractionType FractionType::operator-(const FractionType& subtrahend)
// Function: Creates a FractionType and subtracts two operands
// Pre: Fraction has been initialized
// Post: Returns a FractionType where operand 2 has been subtracted from operand
// 1
{
  FractionType fra;
  fra.num = ((num * subtrahend.denom) - (denom * subtrahend.num));
  fra.denom = denom * subtrahend.denom;
  fra.reduce();
  return fra;
}

FractionType FractionType::operator*(const FractionType& factor)
// Function: Creates a FractionType and multiplies two operands
// Pre: Fraction has been initialized
// Post: Returns a FractionType where operand 1 was multiplied by operand 2
{
  FractionType fra;
  fra.num = num * factor.num;
  fra.denom = denom * factor.denom;
  fra.reduce();
  return fra;
}

FractionType FractionType::operator/(const FractionType& divisor)
// Function: Creates a FractionType and divides operand 1 by operand 2
// Pre: Fraction has been initialized
// Post: Returns a FractionType where operand 1 was divided by operand 2
{
  if (divisor.num == 0) {
	throw std::invalid_argument("Divisors numerator cannot be zero.");
  }
  FractionType fra;
  fra.num = num * divisor.denom;
  fra.denom = denom * divisor.num;
  fra.reduce();
  return fra;
}

void FractionType::print()
// Function: Prints the result of the calculation
// Pre: Fraction has been initialized and calculated
// Post: Prints the result
{
  if (denom == 1) {
	std::cout << num << std::endl;

  } else {
	std::cout << num << "/" << denom << std::endl;
  }
}

void FractionType::reduce()
// Function: Reduces a fraction to its simplest form
// Pre: Fraction has been initialized and calculated
// Post: Updates the result to its simples form
{
  int greatest_common_factor = FractionType::gcf(num, denom);
  num = num / greatest_common_factor;
  denom = denom / greatest_common_factor;
}

int FractionType::gcf(int num, int denom)
// Function: Helper functon which returns the GCF of num and denom, see: https://en.wikipedia.org/wiki/Euclidean_algorithm
// Pre: Fraction has been initialized and calculated
// Post: Returns the GCF of two numbers
{
  while (denom != 0) {
    int temp = denom;
    denom = num % denom;
    num = temp;
  }
  return num;
}
