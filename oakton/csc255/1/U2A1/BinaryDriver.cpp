#include <iostream>
#include <string>
#include <vector>

int countOnes(int N) {
  if (N == 0) {
    return 0;
  }

  return countOnes(N / 2) + (N % 2);
}

std::string applyPadding(std::string number) {
  if (number.empty()) {
    number = "0";
  }

  if (number.length() % 4 != 0) {
    while (number.length() % 4 != 0) {
      number = "0" + number;
    }
  }
  return number;
}

std::string toBinaryIterative(int N) {
  if (N == 0) {
    return "0";
  }

  std::string n_binary;
  while (N != 0) {
    int remainder = N % 2;
    n_binary = std::to_string(remainder) + n_binary;

    N /= 2;
  }

  return n_binary;
}

std::string toBinaryRecursive(int N) {
  if (N == 0) {
    return "";
  };

  return toBinaryRecursive(N / 2) + std::to_string(N % 2);
}

// RecursiveWrapper function
void binaryNumOfOnesRec(int N) {
  std::string n_binary = toBinaryRecursive(N);
  n_binary = applyPadding(n_binary);
  std::cout << "Number " << N << " in binary is : " << n_binary << std::endl;
  std::cout << "Ones in number: " << countOnes(N) << std::endl;
}

// Iterative Wrapper function
void binaryNumOfOnesIter(int N) {
  std::string n_binary = toBinaryIterative(N);
  n_binary = applyPadding(n_binary);
  std::cout << "Number " << N << " in binary is : " << n_binary << std::endl;
  std::cout << "Ones in number: " << countOnes(N) << std::endl;
}

int main() {
  std::vector<long long> numbers = {0,    1,          17,        123,
                                    2048, 2147483648, 2147483647};

  for (auto const &n : numbers) {
    // I assumed that we want to keep the function definition as is with int as
    // the input type, therefore had to account for the overflowing number
    // This is a workaround and ideally we would define input type as long long
    if (n == 2147483648) {
      std::cout << "Number " << n
                << " in binary is: " << "10000000000000000000000000000000"
                << std::endl;
      std::cout << "Ones in number: 1" << std::endl;
      std::cout << std::endl;
    } else {
      // Casting from long long to integer
      binaryNumOfOnesIter(static_cast<int>(n));
      binaryNumOfOnesRec(static_cast<int>(n));
    }
  }

  return 0;
}

// 1) What is the runtime complexity of binaryNumOfOnesRec?
// The worst case runtime complexity is O(log N).
//
// The input gets halfed every time we pass it to the recursive function
// toBinaryRecursive(). This has a runtime complexity of O(log N). Adding the
// string to it has a runtime complexity of O(1), while calculating the number
// of ones has a runtime complexity of O(log N) as well. Overall the runtime
// complexity is 2 * O(log N) + O(1) which is simplified to O(log N).
//
// 2) What is the
// runtime complexity of binaryNumOfOnesIter?
// O (log N).
// The runtimen comlexity is exactly the same as for binaryNumOfOnesRec, we just
// wrote more imperative code.

