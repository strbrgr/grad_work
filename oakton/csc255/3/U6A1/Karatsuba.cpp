#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>

int getLength(long num) {
  if (num == 0) {
    return 1;
  }
  return std::floor(std::log10(num)) + 1;
}

// We are using base 10
long long powerOf10(int exponent) {
  long long result = 1;
  while (exponent > 0) {
    result *= 10;
    exponent--;
  }
  return result;
}

long karatsuba(long long x, long long y) {
  if (x < 10 || y < 10) {
    return x * y;
  }

  int n = std::max(getLength(x), getLength(y));
  // This divides the longest number in half but we need to round up
  int m = (n + 1) / 2;

  long long power = powerOf10(m);

  long long x1 = x / power;
  long long x0 = x % power;
  long long y1 = y / power;
  long long y0 = y % power;

  long long z2 = karatsuba(x1, y1);
  long long z0 = karatsuba(x0, y0);
  long z1 = karatsuba(x1 + x0, y1 + y0) - z2 - z0;

  return z2 * powerOf10(2 * m) + z1 * powerOf10(m) + z0;
}
int main() {
  long result = karatsuba(5919, 2819);
  assert(result == 16685661);
  std::cout << result << std::endl;
  return 0;
}
