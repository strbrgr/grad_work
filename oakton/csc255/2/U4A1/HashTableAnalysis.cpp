#include "HashTable.h"
#include "RandomNumber.h"
#include "iostream"

void linearAnalysis() {
  int total = 0;
  for (int i = 1; i < 11; i++) {
    std::vector<unsigned long long> randomNums = createLargeVectorRandom();
    HashTable<unsigned long long> hashTable(1231);
    for (const auto &n : randomNums) {
      hashTable.insert(n, LINEAR);
    }
    int collisionsLinear = hashTable.getCollisionsLinear();
    total += collisionsLinear;

    std::cout << "Collisions with Linear Probing, Run " << i << ": "
              << collisionsLinear << std::endl;
  }

  std::cout << "Average Collisions over 10 Runs: " << total / 10 << std::endl;
}

void quadraticAnalysis() {
  int total = 0;
  for (int i = 1; i < 11; i++) {
    std::vector<unsigned long long> randomNums = createLargeVectorRandom();
    HashTable<unsigned long long> hashTable(1231);
    for (const auto &n : randomNums) {
      hashTable.insert(n, QUADRATIC);
    }
    int collisionsQuadratic = hashTable.getCollisionsQuadratic();
    total += collisionsQuadratic;

    std::cout << "Collisions with Quadratic Probing, Run " << i << ": "
              << collisionsQuadratic << std::endl;
  }

  std::cout << "Average Collisions over 10 Runs: " << total / 10 << std::endl;
}

void doubleAnalysis() {
  int total = 0;

  for (int i = 1; i < 11; i++) {
    std::vector<unsigned long long> randomNums = createLargeVectorRandom();
    HashTable<unsigned long long> hashTable(1231);
    for (const auto &n : randomNums) {
      hashTable.insert(n, DOUBLE_HASHING);
    }
    int collisionsDouble = hashTable.getCollisionsDouble();
    total += collisionsDouble;

    std::cout << "Collisions with Double Hashing, Run " << i << ": "
              << collisionsDouble << std::endl;
  }

  std::cout << "Average Collisions over 10 Runs: " << total / 10 << std::endl;
}

int main() {
  linearAnalysis();
  quadraticAnalysis();
  doubleAnalysis();
  return 0;
}

