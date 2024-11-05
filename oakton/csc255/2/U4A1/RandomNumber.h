#include <random>

// Random number generator see:
// https://www.techiedelight.com/generate-random-numbers-in-the-specified-range-in-cpp/
// Last accessed 10/21/24
std::vector<unsigned long long> createLargeVectorRandom() {
  std::random_device rd;
  std::mt19937_64 gen(rd());

  std::uniform_int_distribution<unsigned long long> dist(1ULL,
                                                         (1ULL << 63) - 1);

  std::vector<unsigned long long> largeVector;
  largeVector.reserve(1000);

  for (int i = 0; i < 1000; i++) {
    largeVector.push_back(dist(gen));
  }

  return largeVector;
}
