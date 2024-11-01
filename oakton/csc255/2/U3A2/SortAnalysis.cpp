#include "HeapSort.h"
#include "InsertionSort.h"
#include "MergeSort.h"
#include "QuickSort.h"
#include "RandomNumber.h"
#include <iostream>

// Unit 3 Assignment 2
//     : As an added observation,
//       try a much larger data set.For example,
//       try 500,
//       000 randomly generated integers.You may have to scale down a little bit
//           to 100,
//       000 depending on the machine you run your code on.
void heapSortAnalysis() {
  std::cout << "Time for heap sort to sort a vector with 500_000 random "
               "integers in range 1-5000:"
            << std::endl;
  for (int i = 0; i < 5; i++) {
    std::vector<int> input = createLargeVectorRandom();
    auto heapSortStart = std::chrono::steady_clock::now();
    heapSort(input);
    auto heapSortEnd = std::chrono::steady_clock::now();
    auto heapSortDiff = heapSortEnd - heapSortStart;

    std::cout << "Run" << i + 1 << std::endl;
    std::cout << std::chrono::duration<double, std::milli>(heapSortDiff).count()
              << " ms" << std::endl;
    std::cout << std::endl;
  }
}

void insertionSortAnalysis() {
  std::cout << "Time for insertion sort to sort a vector with 500_000 random "
               "integers in range 1-5000:"
            << std::endl;
  for (int i = 0; i < 5; i++) {
    std::vector<int> input = createLargeVectorRandom();
    auto insertionSortStart = std::chrono::steady_clock::now();
    insertionSort(input);
    auto insertionSortEnd = std::chrono::steady_clock::now();
    auto insertionSortDiff = insertionSortEnd - insertionSortStart;

    std::cout << "Run" << i + 1 << std::endl;
    std::cout
        << std::chrono::duration<double, std::milli>(insertionSortDiff).count()
        << " ms" << std::endl;
    std::cout << std::endl;
  }
}

void mergeSortAnalysis() {
  std::cout << "Time for merge sort to sort a vector with 500_000 random "
               "integers in range 1-5000:"
            << std::endl;
  for (int i = 0; i < 5; i++) {
    std::vector<int> input = createLargeVectorRandom();
    auto mergeSortStart = std::chrono::steady_clock::now();
    mergeSort(input);
    auto mergeSortEnd = std::chrono::steady_clock::now();
    auto mergeSortDiff = mergeSortEnd - mergeSortStart;

    std::cout << "Run" << i + 1 << std::endl;
    std::cout
        << std::chrono::duration<double, std::milli>(mergeSortDiff).count()
        << " ms" << std::endl;
    std::cout << std::endl;
  }
}

void quickSortAnalysis() {
  std::cout << "Time for quick sort to sort a vector with 500_000 random "
               "integers in range 1-5000:"
            << std::endl;
  for (int i = 0; i < 5; i++) {
    std::vector<int> input = createLargeVectorRandom();
    auto quickSortStart = std::chrono::steady_clock::now();
    quickSort(input);
    auto quickSortEnd = std::chrono::steady_clock::now();
    auto quickSortDiff = quickSortEnd - quickSortStart;

    std::cout << "Run" << i + 1 << std::endl;
    std::cout
        << std::chrono::duration<double, std::milli>(quickSortDiff).count()
        << " ms" << std::endl;
    std::cout << std::endl;
  }
}

int main() {

  quickSortAnalysis();
  // mergeSortAnalysis();
  // heapSortAnalysis();
  // insertionSortAnalysis();
  return 0;
};
