#include <algorithm>
#include <iostream>
#include <queue>
#include <string>

struct Color {
  std::string name;
  int rank;
};

// Comparison structure to build out max_heap
//
// https://stackoverflow.com/questions/13190269/c-stl-make-heap-with-pairint-string-as-data-type
// Last accessed: 10/16/24
struct Comp {
  bool operator()(const Color &s1, const Color &s2) {
    return s1.rank < s2.rank;
  }
};

// Print function
//
// https://en.cppreference.com/w/cpp/algorithm/make_heap
// Last accessed: 10/16/24
void print(std::string_view text, const std::vector<Color> &v = {}) {
  std::cout << text << ": ";
  for (const auto &e : v)
    std::cout << e.name << ' ';
  std::cout << '\n';
}

// Search function to search for property in max_heap
//
std::string search_heap_color(const std::vector<Color> max_heap, int rank) {
  for (const auto &e : max_heap) {
    if (e.rank == rank) {
      return e.name;
    }
  }
  return "Item not found";
}

int heap_analysis(const std::vector<Color> &colors) {
  // Using a copy here as I don't want to manipulate original vector.
  // I am okay with this due to small input size
  std::vector<Color> colors_copy = colors;
  std::make_heap(colors_copy.begin(), colors_copy.end(), Comp());
  std::string rank_5_color = search_heap_color(colors, 5);
  std::string rank_2_color = search_heap_color(colors, 2);
  std::string rank_11_color = search_heap_color(colors, 11);

  std::cout << "Item at rank 5 is: " << rank_5_color << std::endl;
  std::cout << "Item at rank 2 is: " << rank_2_color << std::endl;
  std::cout << "Item at rank 11 is: " << rank_11_color << std::endl;
  return 0;
}

int main() {
  std::vector<Color> color_pairs = {
      {"orange", 4}, {"blue", 7},  {"pink", 5}, {"black", 6},   {"green", 8},
      {"yellow", 1}, {"brown", 2}, {"red", 3},  {"purple", 10}, {"white", 9}};

  // Not passing by reference due to in-place manipulation of max_heap
  heap_analysis(color_pairs);

  return 0;
}

int hash_table_analysis(std::vector<Color> &colors) { return 0; }

int bst_analysis(std::vector<Color> &colors) { return 0; }
