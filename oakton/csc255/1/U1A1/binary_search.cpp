#include "iostream"
#include <vector>
const int NOT_FOUND = -1;

template <typename Comparable>
int binarySearch(const std::vector<Comparable> &a, const Comparable &x, int low,
                 int high) {
  while (low <= high) {
    int mid = (low + high) / 2;
    Comparable midPointValue = a[mid];

    if (midPointValue <= x) {
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }

  return low - 1;
}

int main() {
  std::vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; // Sample sorted array
  int target = 9;

  int index = binarySearch(arr, target, 0, arr.size() - 1);

  if (index != NOT_FOUND) {
    std::cout << "Element found at index: " << index << std::endl;
  } else {
    std::cout << "Element not found." << std::endl;
  }

  return 0;
}

// 1) What is the count of comparisons of binary_search given an input array of
// size N for the original version?
// The original version has a time complexity of O(log N) with N being the size
// of the input array.
//
// 2) What is the count of comparisons of
// binary_search given an input array of size N for the updated and improved
// version?
// The improved versioon of binary search also has a time complexity of O(log
// N), but due to the reduced number of comparisons it might be slighlty better.
