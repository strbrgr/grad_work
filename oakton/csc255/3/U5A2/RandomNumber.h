#include <random>

// Random number generator see:
// https://www.techiedelight.com/generate-random-numbers-in-the-specified-range-in-cpp/
// Last accessed 10/21/24
std::vector<int> createLargeVectorRandom() {
  std::random_device rd;
  std::mt19937_64 gen(rd());

  std::uniform_int_distribution<int> dist(1, 2000);

  std::vector<int> largeVector;
  largeVector.reserve(10);

  for (int i = 0; i < 10; i++) {
    largeVector.push_back(dist(gen));
  }

  return largeVector;
}
