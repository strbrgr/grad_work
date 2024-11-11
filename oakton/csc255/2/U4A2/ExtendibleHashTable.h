#ifndef EXTENDIBLE_HASH_TABLE_H
#define EXTENDIBLE_HASH_TABLE_H

#include <bitset>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

class ExtendibleHashTable {
private:
  struct Bucket {
    std::vector<uint64_t> items;
    int localDepth;

    Bucket() : localDepth(1) {}
  };

  std::vector<Bucket *> directory;
  int globalDepth;
  const int bucketSize; // M value
  int maxDepth;         // D value
  int rehashCount;
  int duplicateCount;

  // See
  // https://stackoverflow.com/questions/22746429/c-decimal-to-binary-converting
  // Last accessed: 10/26/24
  std::string getBinaryString(uint64_t value) const {
    return std::bitset<64>(value).to_string();
  }

  // See
  // https://www.geeksforgeeks.org/substring-in-cpp/
  // and
  // https://en.cppreference.com/w/cpp/string/basic_string/stol
  // Last accessed: 10/26/24
  int getHash(uint64_t value) const {
    std::string binary = getBinaryString(value);
    std::string suffix = binary.substr(64 - globalDepth);
    return std::stoi(suffix, nullptr, 2);
  }

  void splitBucket(int index) {
    Bucket *oldBucket = directory[index];
    Bucket *newBucket = new Bucket();

    // Update local depths
    newBucket->localDepth = oldBucket->localDepth + 1;
    oldBucket->localDepth = newBucket->localDepth;

    std::vector<uint64_t> items = oldBucket->items;
    oldBucket->items.clear();

    // If global depth needs to increase
    if (oldBucket->localDepth > globalDepth) {
      int oldSize = directory.size();
      globalDepth++;
      directory.resize(1 << globalDepth);

      // Update directory pointers
      for (int i = 0; i < oldSize; i++) {
        directory[i + oldSize] = directory[i];
      }
    }

    // Determine which entries point to newly created buckt
    int mask =
        1 << (oldBucket->localDepth - 1); // If localDepth = 3 1<<2 will be 0100
    // Gets the base index
    // Bitwise AND
    // see: https://www.geeksforgeeks.org/cpp-bitwise-operators/
    // last referenced 10/27/24
    int directoryIndex = index & (mask - 1);
    for (int i = 0; i < directory.size(); i++) {
      // Does the index match our pattern?
      if ((i & (mask - 1)) == directoryIndex) {
        if (i & mask) {
          // point to new bucket
          directory[i] = newBucket;
        } else {
          // point to old bucket
          directory[i] = oldBucket;
        }
      }
    }

    // Redistribute items
    for (uint64_t item : items) {
      insert(item);
    }
  }

public:
  ExtendibleHashTable(int M, int D)
      : globalDepth(1), bucketSize(M), maxDepth(D), rehashCount(0),
        duplicateCount(0) {
    directory.resize(2); // D = 1 initially so resize to 2^1
    directory[0] = new Bucket();
    directory[1] = new Bucket();
  }

  // Destructor
  ~ExtendibleHashTable() {
    std::vector<Bucket *> deleted;
    for (Bucket *bucket : directory) {
      if (std::find(deleted.begin(), deleted.end(), bucket) == deleted.end()) {
        deleted.push_back(bucket);
        delete bucket;
      }
    }
  }

  bool insert(uint64_t value) {
    if (globalDepth >= maxDepth) {
      return false;
    }

    rehashCount++;
    int index = getHash(value);
    Bucket *bucket = directory[index];

    // Check for duplicates
    for (uint64_t item : bucket->items) {
      if (item == value) {
        duplicateCount++;
        return false;
      }
    }

    // size() returns size_t so we need to cast to be able to compare
    if (bucket->items.size() < static_cast<size_t>(bucketSize)) {
      bucket->items.push_back(value);
      return true;
    }

    // Need to split bucket
    splitBucket(index);
    return insert(value); // Try inserting again
  }

  bool remove(uint64_t value) {
    int index = getHash(value);
    Bucket *bucket = directory[index];

    for (auto it = bucket->items.begin(); it != bucket->items.end(); ++it) {
      if (*it == value) {
        bucket->items.erase(it);
        return true;
      }
    }
    return false;
  }

  bool find(uint64_t value) const {
    int index = getHash(value);
    Bucket *bucket = directory[index];

    for (uint64_t item : bucket->items) {
      if (item == value) {
        return true;
      }
    }
    return false;
  }

  void print() const {
    std::cout << "Global Depth: " << globalDepth << std::endl;
    std::cout << "Directory Size: " << directory.size() << std::endl;

    std::vector<Bucket *> uniqueBuckets;
    for (size_t i = 0; i < directory.size(); i++) {
      Bucket *bucket = directory[i];
      if (std::find(uniqueBuckets.begin(), uniqueBuckets.end(), bucket) ==
          uniqueBuckets.end()) {
        uniqueBuckets.push_back(bucket);
        std::cout << "Directory " << i << " Local Depth: " << bucket->localDepth
                  << ": ";
        for (uint64_t item : bucket->items) {
          std::cout << item << " ";
        }
        std::cout << std::endl;
      }
    }

    std::cout << "Unique Buckets: " << uniqueBuckets.size() << std::endl;
    std::cout << "Rehash Count: " << rehashCount << std::endl;
    std::cout << "Duplicate Count: " << duplicateCount << std::endl;

    // Calculate expected number of leaves
    // (N/M) * log 2 e
    double expectedLeaves =
        (rehashCount / static_cast<double>(bucketSize)) * log2(exp(1));
    std::cout << "Expected number of leaves: " << expectedLeaves << std::endl;
  }

  int getGlobalDepth() const { return globalDepth; }
  int getRehashCount() const { return rehashCount; }
  int getDuplicateCount() const { return duplicateCount; }
  int getUniqueLeafCount() const {
    std::vector<Bucket *> uniqueBuckets;
    for (Bucket *bucket : directory) {
      if (std::find(uniqueBuckets.begin(), uniqueBuckets.end(), bucket) ==
          uniqueBuckets.end()) {
        uniqueBuckets.push_back(bucket);
      }
    }
    return uniqueBuckets.size();
  }
};

#endif
