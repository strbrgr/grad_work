#ifndef BINARYHEAP_H
#define BINARYHEAP_H

#include <iostream>
#include <optional>
#include <stdexcept>
#include <vector>

template <typename Comparable> class BinaryHeap {
public:
  explicit BinaryHeap(int capacity = 100);
  explicit BinaryHeap(const std::vector<Comparable> &items);
  bool isEmpty() const;
  const Comparable &findMin() const;
  void insert(const Comparable &x);
  void insert(Comparable &&x);
  void deleteMin();
  void deleteMin(Comparable &minItem);
  void makeEmpty();
  void print() const;
  const std::vector<Comparable> &getArray() const;
  void buildHeapPercolateUp(std::vector<Comparable> input);
  void buildHeapPercolateDown(std::vector<Comparable> input);
  Comparable *getTop();

private:
  std::vector<Comparable> array; // The heap array
  int currentSize;               // Number of elements in heap
  void buildHeap();
  void percolateDown(int hole);
};

// Constructor with default capacity
template <typename Comparable>
BinaryHeap<Comparable>::BinaryHeap(int capacity)
    : array(capacity + 1), currentSize(0) {}

// Constructor to create a heap from a vector
template <typename Comparable>
BinaryHeap<Comparable>::BinaryHeap(const std::vector<Comparable> &items)
    : array(items.size() + 10), currentSize(static_cast<int>(items.size())) {
  for (int i = 0; i < items.size(); ++i) {
    array[i + 1] = items[i];
  }
  buildHeap();
}

// Insert method
template <typename Comparable>
void BinaryHeap<Comparable>::insert(const Comparable &x) {
  if (currentSize == array.size() - 1)
    array.resize(array.size() * 2);

  // Percolate up
  int hole = ++currentSize;
  array[0] = x; // Temporary copy

  for (; hole > 1 && array[hole / 2] > array[0]; hole /= 2)
    array[hole] = std::move(array[hole / 2]);

  array[hole] = std::move(array[0]); // Place the copied value
}

// Delete minimum item
template <typename Comparable> void BinaryHeap<Comparable>::deleteMin() {
  if (isEmpty())
    throw std::underflow_error("Heap is empty");

  array[1] = std::move(array[currentSize--]);
  percolateDown(1);
}

// Delete minimum item and return it
template <typename Comparable>
void BinaryHeap<Comparable>::deleteMin(Comparable &minItem) {
  if (isEmpty())
    throw std::underflow_error("Heap is empty");

  minItem = std::move(array[1]);
  array[1] = std::move(array[currentSize--]);
  percolateDown(1);
}

// Internal method to percolate down in the min heap
template <typename Comparable>
void BinaryHeap<Comparable>::percolateDown(int hole) {
  int child;
  Comparable tmp = std::move(array[hole]);

  for (; hole * 2 <= currentSize; hole = child) {
    child = hole * 2;
    if (child != currentSize && array[child + 1] < array[child])
      ++child;
    if (array[child] < tmp)
      array[hole] = std::move(array[child]);
    else
      break;
  }
  array[hole] = std::move(tmp);
}

// Build heap method
template <typename Comparable> void BinaryHeap<Comparable>::buildHeap() {
  for (int i = currentSize / 2; i > 0; --i)
    percolateDown(i);
}

// Check if heap is empty
template <typename Comparable> bool BinaryHeap<Comparable>::isEmpty() const {
  return currentSize == 0;
}

// Print method
template <typename Comparable> void BinaryHeap<Comparable>::print() const {
  for (int i = 1; i <= currentSize; ++i) {
    std::cout << array[i] << " ";
  }
  std::cout << std::endl;
}

// Get Array method
template <typename Comparable>
const std::vector<Comparable> &BinaryHeap<Comparable>::getArray() const {
  return array;
}

// Wrapper function to insert into heap one by one
template <typename Comparable>
void BinaryHeap<Comparable>::buildHeapPercolateUp(
    std::vector<Comparable> input) {
  currentSize = 0;                // Reset currentSize
  array.resize(input.size() + 1); // Resize for 1-based index

  for (const auto &value : input) {
    insert(value); // Insert directly, which already handles resizing
  }
}

// Wrapper function to build heap in linear time
template <typename Comparable>
void BinaryHeap<Comparable>::buildHeapPercolateDown(
    std::vector<Comparable> input) {
  currentSize = input.size();
  array.resize(currentSize + 1);

  for (int i = 0; i < input.size(); ++i) {
    array[i + 1] = input[i]; // Fill starting from index 1
  }

  buildHeap(); // Call to build the heap from the array
}

template <typename Comparable> Comparable *BinaryHeap<Comparable>::getTop() {
  return &array[1];
}

#endif // BINARYHEAP_H
