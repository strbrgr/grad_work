class FractionType {
 public:
  void Initialize(int numerator, int denominator);
  // Function: Initialize the fraction
  // Pre:  None
  // Post: Fraction is initialized
  int NumeratorIs();
  // Function: Returns the value of the numerator
  // Pre:  Fraction has been initialized
  // Post: numerator is returned
  int DenominatorIs();
  // Function: Returns the value of the denominator
  // Pre:  Reaction has been initialized
  // Post: denominator is returned
  bool IsZero();
  // Function: Determines if fraction is zero
  // Pre:  Fraction has been initialized
  // Post: Returns true if numerator is zero
  bool IsNotProper();
  // Function: Determines if fraction is a proper fraction
  // Pre:  Fraction has been initialized
  // Post: Returns true if fraction is greater than one
  int ConvertToProper();
  // Function: Converts the fraction to a whole number and a
  //       fractional part
  // Pre:  Fraction has been initialized, is in reduced form, and
  //       is not a proper fraction
  // Post: Returns whole number
  //       Remaining fraction is original fraction minus the
  //       whole number; fraction is in reduced form
  FractionType operator+(const FractionType& addend);
  // Function: Creates a FractionType and adds two operands
  // Pre: Fraction has been initialized
  // Post: Returns a FractionType where operand 2 has been added to operand 1
  FractionType operator-(const FractionType& subtrahend);
  // Function: Creates a FractionType and subtracts two operands
  // Pre: Fraction has been initialized
  // Post: Returns a FractionType where operand 2 has been subtracted from
  // operand 1
  FractionType operator*(const FractionType& factor);
  // Function: Creates a FractionType and multiplies two operands
  // Pre: Fraction has been initialized
  // Post: Returns a FractionType where operand 1 was multiplied by operand 2
  FractionType operator/(const FractionType& divisor);
  // Function: Creates a FractionType and divides operand 1 by operand 2
  // Pre: Fraction has been initialized
  // Post: Returns a FractionType where operand 1 was divided by operand 2
  void print();
  // Function: Prints the result of the calculation
  // Pre: Fraction has been initialized and calculated
  // Post: Prints the result of the calculates to the console
  void reduce();
  // Function: Checks whether numerator and denominator have a common factor,
  // and if they do divides both by the common factor
  // Pre: Fraction has been initialized and calculated
  // Post: Updates the result to its simplest form
  int gcf(int num, int denom);
  // Function: Helper functon which returns the GCF of num and denom, see: https://en.wikipedia.org/wiki/Euclidean_algorithm
  // Pre: Fraction has been initialized and calculated
  // Post: Returns the GCF of two numbers
 private:
  int num;
  int denom;
};
