#include <random>

// Random number generator see:
// https://www.techiedelight.com/generate-random-numbers-in-the-specified-range-in-cpp/
// Last accessed 10/21/24
int createRandomNumber(int min, int max) {
  std::random_device rd;
  std::mt19937_64 gen(rd());

  std::uniform_int_distribution<int> dist(min, max);

  return dist(gen);
}
