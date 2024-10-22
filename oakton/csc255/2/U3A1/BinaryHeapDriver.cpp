#include "BinaryHeap.h"
#include <random>
#include <vector>

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

  for (int i = 5000; i >= 1; i--) {
    largeVector.push_back(random(1, 5000));
  };

  return largeVector;
}

std::vector<int> createLargeVector() {
  std::vector<int> largeVector;

  for (int i = 1; i < 5001; i++) {
    largeVector.push_back(i);
  };

  return largeVector;
}

std::vector<int> createLargeVectorReversed() {
  std::vector<int> largeVector;

  for (int i = 5000; i >= 1; i--) {
    largeVector.push_back(i);
  };

  return largeVector;
}

void setup() {
  std::vector<int> input = {2, 45, 12, 1, 56, 78, 13, 14, 5, 8, 9, 3, 11, 34};

  std::cout << "Confirming we set up correctly..." << std::endl;
  BinaryHeap<int> setupHeap1;
  setupHeap1.buildHeapPercolateDown(input);
  setupHeap1.print();
  BinaryHeap<int> setupHeap2;
  setupHeap2.buildHeapPercolateUp(input);
  setupHeap2.print();
  std::cout << std::endl;
}

void analyzeLargeVector() {
  std::vector<int> largeVector = createLargeVector();

  // Start timer and create min heap
  BinaryHeap<int> heapLargeVectorPercolateDown;
  auto heapLargeVectorPercolateDownStart = std::chrono::steady_clock::now();
  heapLargeVectorPercolateDown.buildHeapPercolateDown(largeVector);
  auto heapLargeVectorPercolateDownEnd = std::chrono::steady_clock::now();
  auto heapLargeVectorPercolateDownDiff =
      heapLargeVectorPercolateDownEnd - heapLargeVectorPercolateDownStart;
  heapLargeVectorPercolateDown.print();

  std::cout
      << "Time in ms to create min heap with large vector and percolateDown: "
      << std::endl;
  std::cout << std::chrono::duration<double, std::milli>(
                   heapLargeVectorPercolateDownDiff)
                   .count()
            << " ms" << std::endl;
  std::cout << std::endl;

  // Start timer and create min heap
  BinaryHeap<int> heapLargeVectorPercolateUp;
  auto heapLargeVectorPercolateUpStart = std::chrono::steady_clock::now();
  heapLargeVectorPercolateUp.buildHeapPercolateUp(largeVector);
  auto heapLargeVectorPercolateUpEnd = std::chrono::steady_clock::now();
  auto heapLargeVectorPercolateUpDiff =
      heapLargeVectorPercolateUpEnd - heapLargeVectorPercolateUpStart;
  heapLargeVectorPercolateUp.print();

  std::cout
      << "Time in ms to create min heap with large vector and percolateUp: "
      << std::endl;
  std::cout << std::chrono::duration<double, std::milli>(
                   heapLargeVectorPercolateUpDiff)
                   .count()
            << " ms" << std::endl;
  std::cout << std::endl;
}

void analyzeLargeVectorReversed() {
  std::vector<int> largeVectorReversed = createLargeVectorReversed();

  // Start timer and create min heap
  BinaryHeap<int> heapLargeVectorReversedPercolateDown;
  auto heapLargeVectorReversedPercolateDownStart =
      std::chrono::steady_clock::now();
  heapLargeVectorReversedPercolateDown.buildHeapPercolateDown(
      largeVectorReversed);
  auto heapLargeVectorReversedPercolateDownEnd =
      std::chrono::steady_clock::now();
  auto heapLargeVectorReversedPercolateDownDiff =
      heapLargeVectorReversedPercolateDownEnd -
      heapLargeVectorReversedPercolateDownStart;
  heapLargeVectorReversedPercolateDown.print();

  std::cout << "Time in ms to create min heap with large vector reversed and "
               "percolateDown: "
            << std::endl;
  std::cout << std::chrono::duration<double, std::milli>(
                   heapLargeVectorReversedPercolateDownDiff)
                   .count()
            << " ms" << std::endl;
  std::cout << std::endl;

  // Start timer and create min heap
  BinaryHeap<int> heapLargeVectorReversedPercolateUp;
  auto heapLargeVectorReversedPercolateUpStart =
      std::chrono::steady_clock::now();
  heapLargeVectorReversedPercolateUp.buildHeapPercolateUp(largeVectorReversed);
  auto heapLargeVectorReversedPercolateUpEnd = std::chrono::steady_clock::now();
  auto heapLargeVectorReversedPercolateUpDiff =
      heapLargeVectorReversedPercolateUpEnd -
      heapLargeVectorReversedPercolateUpStart;
  heapLargeVectorReversedPercolateUp.print();

  std::cout << "Time in ms to create min heap with large vector reversed and "
               "percolateUp: "
            << std::endl;
  std::cout << std::chrono::duration<double, std::milli>(
                   heapLargeVectorReversedPercolateUpDiff)
                   .count()
            << " ms" << std::endl;
  std::cout << std::endl;
}

void analyzeLargeVectorRandom() {
  std::vector<int> largeVectorRandom = createLargeVectorRandom();

  // Start timer and create min heap
  BinaryHeap<int> heapLargeVectorRandomPercolateDown;
  auto heapLargeVectorRandomPercolateDownStart =
      std::chrono::steady_clock::now();
  heapLargeVectorRandomPercolateDown.buildHeapPercolateDown(largeVectorRandom);
  auto heapLargeVectorRandomPercolateDownEnd = std::chrono::steady_clock::now();
  auto heapLargeVectorRandomPercolateDownDiff =
      heapLargeVectorRandomPercolateDownEnd -
      heapLargeVectorRandomPercolateDownStart;
  heapLargeVectorRandomPercolateDown.print();

  std::cout << "Time in ms to create min heap with large vector random and "
               "percolateDown: "
            << std::endl;
  std::cout << std::chrono::duration<double, std::milli>(
                   heapLargeVectorRandomPercolateDownDiff)
                   .count()
            << " ms" << std::endl;
  std::cout << std::endl;

  // Start timer and create min heap
  BinaryHeap<int> heapLargeVectorRandomPercolateUp;
  auto heapLargeVectorRandomPercolateUpStart = std::chrono::steady_clock::now();
  heapLargeVectorRandomPercolateUp.buildHeapPercolateUp(largeVectorRandom);
  auto heapLargeVectorRandomPercolateUpEnd = std::chrono::steady_clock::now();
  auto heapLargeVectorRandomPercolateUpDiff =
      heapLargeVectorRandomPercolateUpEnd -
      heapLargeVectorRandomPercolateUpStart;
  heapLargeVectorRandomPercolateUp.print();

  std::cout << "Time in ms to create min heap with large vector random and "
               "percolateUp: "
            << std::endl;
  std::cout << std::chrono::duration<double, std::milli>(
                   heapLargeVectorRandomPercolateUpDiff)
                   .count()
            << " ms" << std::endl;
  std::cout << std::endl;
}

int main() {
  setup();
  analyzeLargeVector();
  analyzeLargeVectorReversed();
  analyzeLargeVectorRandom();

  return 0;
}

