#include <string>
#include <vector>

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

template <typename HashedObj> class HashTable {
public:
  explicit HashTable(int size = 1723);
  bool contains(const HashedObj &x) const;
  void makeEmpty();
  bool insert(const HashedObj &x);
  bool insert(HashedObj &&x);
  bool remove(const HashedObj &x);
  int get(const HashedObj &x) const;
  enum EntryType { ACTIVE, EMPTY, DELETED };

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
  int findPos(const HashedObj &x) const;
  void rehash();
  size_t myhash(const HashedObj &x) const;
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
bool HashTable<HashedObj>::contains(const HashedObj &x) const {
  return isActive(findPos(x));
}

template <typename HashedObj>
int HashTable<HashedObj>::findPos(const HashedObj &x) const {
  int currentPos = myhash(x);
  int k = 0;

  // Use quadratic probing
  while (array[currentPos].info != EMPTY && array[currentPos].element != x) {
    k++;
    currentPos = (myhash(x) + k * k) % array.size();

    // Handle wrap-around
    if (currentPos >= array.size())
      currentPos -= array.size();
  }

  return currentPos;
}

template <typename HashedObj>
bool HashTable<HashedObj>::isActive(int currentPos) const {
  return array[currentPos].info == ACTIVE;
}

template <typename HashedObj>
bool HashTable<HashedObj>::insert(const HashedObj &x) {
  // Insert x as active
  int currentPos = findPos(x);
  if (isActive(currentPos))
    return false;

  array[currentPos].element = x;
  array[currentPos].info = ACTIVE;

  if (++currentSize > array.size() / 2)
    rehash();

  return true;
}

template <typename HashedObj> bool HashTable<HashedObj>::insert(HashedObj &&x) {
  int currentPos = findPos(x);
  if (isActive(currentPos))
    return false;

  array[currentPos] = {std::move(x), ACTIVE};

  if (++currentSize > array.size() / 2)
    rehash();

  return true;
}

template <typename HashedObj>
bool HashTable<HashedObj>::remove(const HashedObj &x) {
  int currentPos = findPos(x);
  if (!isActive(currentPos))
    return false;

  array[currentPos].info = DELETED;
  return true;
}

template <typename HashedObj> void HashTable<HashedObj>::rehash() {
  std::vector<HashEntry> oldArray = array;

  // Create new double-sized, empty table
  array.resize(nextPrime(2 * oldArray.size()));
  for (auto &entry : array)
    entry.info = EMPTY;

  // Copy table over
  currentSize = 0;
  for (auto &entry : oldArray)
    if (entry.info == ACTIVE)
      insert(std::move(entry.element));
}

template <typename HashedObj>
size_t HashTable<HashedObj>::myhash(const HashedObj &x) const {
  static std::hash<HashedObj> hashFn;
  return hashFn(x) % array.size();
}

template <typename HashedObj>
int HashTable<HashedObj>::get(const HashedObj &x) const {
  int currentPos = findPos(x);
  if (!isActive(currentPos)) {
    return -1;
  }
  return array[currentPos].element.count;
}
