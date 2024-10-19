#include <ostream>
#include <string>

struct Color {
  std::string name;
  int rank;

  bool operator<(const Color &other) const {
    return name < other.name; // Compare by name for BST
  }

  bool operator>(const Color &other) const {
    return rank > other.rank; // Compare by rank for Heap
  }

  // Used with hashtable
  bool operator==(const Color &other) const { return name == other.name; }
};

// Hash function for Color
namespace std {
template <> struct hash<Color> {
  std::size_t operator()(const Color &c) const {
    return std::hash<std::string>()(c.name);
  }
};
} // namespace std
