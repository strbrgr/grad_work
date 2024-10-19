#include <ostream>
#include <string>

struct Word {
  std::string name;
  int count;

  // Compare by count for BST
  bool operator<(const Word &other) const { return name < other.name; }

  // Compare by count for Heap
  bool operator>(const Word &other) const { return count > other.count; }

  // Used with hashtable
  bool operator==(const Word &other) const { return name == other.name; }
};

// Hash function for Word
namespace std {
template <> struct hash<Word> {
  std::size_t operator()(const Word &c) const {
    return std::hash<std::string>()(c.name);
  }
};
} // namespace std
