#include <chrono>
#include <iostream>
#include <stdlib.h>
#include <thread>

using namespace std;

const int MAX_ITEMS = 20000000;
int numbers[MAX_ITEMS];
int temp[MAX_ITEMS];
int chunk;

template <class ItemType>
void Merge(ItemType values[], int leftFirst, int leftLast, int rightFirst,
           int rightLast, ItemType tempArray[]) {
  int index = leftFirst;
  int saveFirst = leftFirst;

  while ((leftFirst <= leftLast) && (rightFirst <= rightLast)) {
    if (values[leftFirst] <= values[rightFirst]) {
      tempArray[index] = values[leftFirst];
      leftFirst++;
    } else {
      tempArray[index] = values[rightFirst];
      rightFirst++;
    }
    index++;
  }

  while (leftFirst <= leftLast) {
    tempArray[index] = values[leftFirst];
    leftFirst++;
    index++;
  }

  while (rightFirst <= rightLast) {
    tempArray[index] = values[rightFirst];
    rightFirst++;
    index++;
  }

  for (index = saveFirst; index <= rightLast; index++) {
    values[index] = tempArray[index];
  }
}

template <class ItemType>
void SerialMergeSort(ItemType values[], int first, int last,
                     ItemType tempArray[])

// Post: The elements in values are sorted by key.
{
  if (first < last) {
    int middle = (first + last) / 2;
    SerialMergeSort<ItemType>(values, first, middle, tempArray);
    SerialMergeSort<ItemType>(values, middle + 1, last, tempArray);
    Merge<ItemType>(values, first, middle, middle + 1, last, tempArray);
  }
}

template <class ItemType>
void ParallelMergeSort(ItemType values[], int first, int last,
                       ItemType tempArray[], int chunkSize)
// Post: The elements in values are sorted by key.
{
  if (first < last) {
    int middle = (first + last) / 2;

    if ((last - first + 1) <= chunkSize) {
      // If the size of the current segment is below the chunk threshold,
      // perform a serial sort
      SerialMergeSort<ItemType>(values, first, last, tempArray);
    } else {
      // Create threads for parallel sorting
      std::thread left(ParallelMergeSort<ItemType>, values, first, middle,
                       tempArray, chunkSize);
      std::thread right(ParallelMergeSort<ItemType>, values, middle + 1, last,
                        tempArray, chunkSize);
      left.join();
      right.join();
    }

    // Merge the two halves
    Merge<ItemType>(values, first, middle, middle + 1, last, tempArray);
  }
}

int main(int argc, const char *argv[]) {
  chrono::time_point<chrono::system_clock> start;
  chrono::time_point<chrono::system_clock> end;

  // Initialize the array with random integers
  for (int index = 0; index < MAX_ITEMS; index++) {
    numbers[index] = rand() % 1000000000;
  }

  cout << "Starting Serial Merge Sort:" << endl;
  start = chrono::system_clock::now();
  SerialMergeSort<int>(numbers, 0, MAX_ITEMS - 1, temp);
  end = chrono::system_clock::now();
  chrono::duration<double> diff = end - start;
  cout << "Serial Merge Sort duration:" << diff.count() << " seconds." << endl;

  // Reinit
  for (int index = 0; index < MAX_ITEMS; index++) {
    numbers[index] = rand() % 1000000000;
  }

  cout << "Starting Parallel Merge Sort:" << endl;
  start = chrono::system_clock::now();
  ParallelMergeSort<int>(numbers, 0, MAX_ITEMS - 1, temp,
                         MAX_ITEMS / thread::hardware_concurrency());
  end = chrono::system_clock::now();
  diff = end - start;
  cout << "Parallel Merge Sort duration:" << diff.count() << " seconds."
       << endl;

  return 0;
}

