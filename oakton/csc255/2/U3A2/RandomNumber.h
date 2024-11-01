#include <random>

// Random number generator see:
// https://www.techiedelight.com/generate-random-numbers-in-the-specified-range-in-cpp/
// Last accessed 10/21/24
std::random_device rd;
std::mt19937 gen(rd());

int random(int low, int high) {
  std::uniform_int_distribution<> dist(low, high);
  return dist(gen);
}

std::vector<int> createLargeVectorRandom() {
  std::vector<int> largeVector;

  for (int i = 0; i <= 500000; i++) {
    largeVector.push_back(random(1, 5000));
  };

  return largeVector;
}
