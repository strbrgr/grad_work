#include "LargeInt.h"
#include <iostream>

using namespace std;

int main() {
  LargeInt num1("123456789");
  LargeInt num2("123456789");

  LargeInt result = num1 * num2;

  std::cout << result << std::endl;

  return 0;
}
