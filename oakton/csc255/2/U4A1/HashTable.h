#include <iostream>
#include <semaphore>
#include <string>
#include <utility>
#include <vector>

enum ProbingStrategy { LINEAR, QUADRATIC, DOUBLE_HASHING };

bool isPrime(int n) {
  if (n <= 1)
    return false;
  if (n == 2 || n == 3)
    return true;
  if (n % 2 == 0 || n % 3 == 0)
    return false;
  for (int i = 5; i * i <= n; i += 6)
    if (n % i == 0 || n % (i + 2) == 0)
      return false;
  return true;
}

int nextPrime(int n) {
  if (n <= 1)
    return 2;
  while (!isPrime(n))
    ++n;
  return n;
}

int findLargestPrimeSmallerThan(int number) {
  for (int i = number - 1; i > 1; --i) {
    if (isPrime(i)) {
      return i;
    }
  }
  return -1;
}

template <typename HashedObj> class HashTable {
public:
  explicit HashTable(int size = 1231);
  void makeEmpty();
  bool insert(const HashedObj &x, ProbingStrategy p);
  bool insert(HashedObj &&x, ProbingStrategy p);
  bool remove(const HashedObj &x, ProbingStrategy p);
  enum EntryType { ACTIVE, EMPTY, DELETED };
  int getCollisionsLinear() const;
  int getCollisionsQuadratic() const;
  int getCollisionsDouble() const;
  void print() const;

private:
  struct HashEntry {
    HashedObj element;
    EntryType info;
    HashEntry(const HashedObj &e = HashedObj{}, EntryType i = EMPTY)
        : element{e}, info{i} {}
    HashEntry(HashedObj &&e, EntryType i = EMPTY)
        : element{std::move(e)}, info{i} {}
  };

  std::vector<HashEntry> array;
  int currentSize;
  bool isActive(int currentPos) const;
  int findPos(const HashedObj &x, ProbingStrategy p);
  void rehash(ProbingStrategy p);
  size_t myhash(const HashedObj &x) const;
  size_t myhash2(const HashedObj &x) const;
  int collisionsLinear = 0;
  int collisionsQuadratic = 0;
  int collisionsDouble = 0;
};

template <typename HashedObj>
HashTable<HashedObj>::HashTable(int size) : array(nextPrime(size)) {
  makeEmpty();
}

template <typename HashedObj> void HashTable<HashedObj>::makeEmpty() {
  currentSize = 0;
  for (auto &entry : array)
    entry.info = EMPTY;
}

template <typename HashedObj>
int HashTable<HashedObj>::findPos(const HashedObj &x, ProbingStrategy p) {
  int currentPos = myhash(x);

  switch (p) {
  case LINEAR: {
    int currentCollisions = 0;
    while (array[currentPos].info != EMPTY && array[currentPos].element != x) {
      currentPos++;
      currentCollisions++;
      // wrap around
      if (currentPos >= array.size())
        currentPos = 0;
    }
    collisionsLinear += currentCollisions;
    break;
  }
  case QUADRATIC: {
    int offset = 1;
    int currentCollisions = 0;
    while (array[currentPos].info != EMPTY && array[currentPos].element != x) {
      currentPos += offset * offset;
      offset++;
      currentCollisions++;
      if (currentPos >= array.size())
        currentPos -= array.size();
    }
    collisionsQuadratic += currentCollisions;
    break;
  }
  case DOUBLE_HASHING: {
    int currentCollisions = 0;
    int i = 0;
    int hash2 = myhash2(x);

    int originalPos = currentPos;

    while (array[currentPos].info != EMPTY && array[currentPos].element != x) {
      currentPos = (originalPos + i * hash2) % array.size();
      i++;
      currentCollisions++;

      if (i >= array.size()) {
        currentPos = originalPos; // wraparound
        break;
      }
    }
    collisionsDouble += currentCollisions;
    break;
  }
  }

  return currentPos;
}

template <typename HashedObj>
bool HashTable<HashedObj>::isActive(int currentPos) const {
  return array[currentPos].info == ACTIVE;
}

template <typename HashedObj>
bool HashTable<HashedObj>::insert(const HashedObj &x, ProbingStrategy p) {
  int currentPos = findPos(x, p);

  // Safeguard but technically should not happen due to doubling of size
  if (isActive(currentPos)) {
    return false;
  }

  array[currentPos] = {x, ACTIVE};

  if (++currentSize > array.size() / 2)
    rehash(p);

  return true;
}

template <typename HashedObj>
bool HashTable<HashedObj>::insert(HashedObj &&x, ProbingStrategy p) {
  int currentPos = findPos(x, p);
  if (isActive(currentPos))
    return false;

  array[currentPos] = {std::move(x), ACTIVE};

  // Rehash when half full
  if (++currentSize > array.size() / 2)
    rehash(p);

  return true;
}

template <typename HashedObj>
bool HashTable<HashedObj>::remove(const HashedObj &x, ProbingStrategy p) {
  int currentPos = findPos(x, p);
  if (!isActive(currentPos))
    return false;

  array[currentPos].info = DELETED;
  return true;
}

template <typename HashedObj>
void HashTable<HashedObj>::rehash(ProbingStrategy p) {
  collisionsLinear = 0;
  collisionsQuadratic = 0;
  collisionsDouble = 0;
  std::vector<HashEntry> oldArray = array;

  // Create a new larger table
  array.resize(nextPrime(2 * oldArray.size()));
  makeEmpty(); // Reset current size

  // Copy entries over
  for (const auto &entry : oldArray) {
    if (entry.info == ACTIVE)
      insert(std::move(entry.element), p); // Insert active entries
  }
}

template <typename HashedObj>
size_t HashTable<HashedObj>::myhash(const HashedObj &x) const {
  static std::hash<HashedObj> hashFn;
  return hashFn(x) % array.size();
}

template <typename HashedObj>
size_t HashTable<HashedObj>::myhash2(const HashedObj &x) const {
  // h2(K) = 1 + (K mod (M-1))
  return 1 + (x % (array.size() - 1));
}

template <typename HashedObj>
int HashTable<HashedObj>::getCollisionsLinear() const {
  return collisionsLinear;
}

template <typename HashedObj>
int HashTable<HashedObj>::getCollisionsQuadratic() const {
  return collisionsQuadratic;
}

template <typename HashedObj>
int HashTable<HashedObj>::getCollisionsDouble() const {
  return collisionsDouble;
}

template <typename HashedObj> void HashTable<HashedObj>::print() const {
  for (const auto &entry : array) {
    if (entry.info == ACTIVE) {
      std::cout << entry.element << std::endl;
    }
  }
}

