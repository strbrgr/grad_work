#include <vector>
const int NOT_FOUND = -1;

template <typename Comparable>
// FUNCTION: Recursive Function to implement binary search on a vector.
// POST: Vector, Comparable, low, and high are passed as input
//
int binarySearch(const std::vector<Comparable> &a, const Comparable &x, int low,
                 int high) {
  // Base case, low pointer went beyond high pointer
  if (low > high) {
    return NOT_FOUND;
  }

  int mid = (low + high) / 2;
  Comparable midPointValue = a[mid];
  // general case,
  if (midPointValue == x) {
    return mid;
  }

  // Recursive case
  if (midPointValue < x) {
    return binarySearch(a, x, mid + 1, high);
  }

  return binarySearch(a, x, low, mid - 1);
}

// 1) What is the count of comparisons of binary_search given an input array of
// size N for the original version?
// Worst case of O(log N) due to splitting the input in half.
//
// 2) What is the count of comparisons of
// binary_search given an input array of size N for the updated and improved
// version?
// Worst case of O(log N) due to splitting the input in half.

