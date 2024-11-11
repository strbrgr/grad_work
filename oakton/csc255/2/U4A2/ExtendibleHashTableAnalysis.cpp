#include "ExtendibleHashTable.h"
#include <random>
#include <vector>

// Random number generator see:
// https://www.techiedelight.com/generate-random-numbers-in-the-specified-range-in-cpp/
// Last accessed 10/21/24
std::vector<uint64_t> generateRandomNumbers(int count) {
  std::random_device rd;
  std::mt19937_64 gen(rd());
  std::uniform_int_distribution<uint64_t> dis;

  std::vector<uint64_t> numbers;
  for (int i = 0; i < count; i++) {
    numbers.push_back(dis(gen));
  }
  return numbers;
}

void binaryAnalysis() {
  std::cout << "\nBinary numbers input, M = 4\n";
  ExtendibleHashTable eht(4, 6);

  std::vector<uint64_t> inputs = {
      0b10111101, 0b00000010, 0b10011011, 0b10111110, 0b01111111, 0b01010001,
      0b10010110, 0b00001011, 0b11001111, 0b10011110, 0b11011011, 0b00101011,
      0b01100001, 0b11110000, 0b01101111, 0b00000101, 0b01000101, 0b01000000};

  for (uint64_t value : inputs) {
    eht.insert(value);
  }
  eht.print();
}

void integerAnalyis() {
  std::cout << "\nIntegers,M = 3\n";
  ExtendibleHashTable eht(3, 6);

  std::vector<int> inputs = {16, 4, 6, 22, 24, 10, 31, 7, 9, 20, 26, 3, 1};

  for (int value : inputs) {
    eht.insert(value);
  }
  eht.print();
}

void randomAnalysis() {
  std::cout << "\nRandom numbers\n";

  ExtendibleHashTable eht1(4, 6);
  std::vector<uint64_t> randomNumbers = generateRandomNumbers(500);

  for (uint64_t value : randomNumbers) {
    eht1.insert(value);
  }

  std::cout << "\nWith M=4, D=6:\n";
  eht1.print();

  ExtendibleHashTable eht2(8, 7);
  for (uint64_t value : randomNumbers) {
    eht2.insert(value);
  }

  std::cout << "\nWith M=8, D=7:\n";
  eht2.print();
}

int main() {
  binaryAnalysis();
  integerAnalyis();
  randomAnalysis();
  return 0;
}
