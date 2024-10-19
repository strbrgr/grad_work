#include "BinaryHeap.h"
#include "BinarySearchTree.h"
#include "Color.h"
#include "HashTable.h"
#include <cstddef>
#include <iostream>
#include <string>

// Search function to search for property in max_heap
//
std::string search_heap_color(const BinaryHeap<Color> &binary_heap, int rank) {
  const std::vector<Color> &heap_array = binary_heap.getArray();

  for (const Color &c : heap_array) {
    if (c.rank == rank) {
      return c.name;
    }
  }

  return "Item not found";
}

int heap_analysis(const std::vector<Color> &colors) {
  // Using a copy here as I don't want to manipulate original vector.
  // I am okay with this due to small input size
  std::vector<Color> colors_copy = colors;
  BinaryHeap<Color> heap(colors_copy);

  std::string rank_5_color = search_heap_color(heap, 5);
  std::string rank_2_color = search_heap_color(heap, 2);
  std::string rank_11_color = search_heap_color(heap, 11);
  std::cout << "Heap solution:" << std::endl;

  std::cout << "Item at rank 5 is: " << rank_5_color << std::endl;
  std::cout << "Item at rank 2 is: " << rank_2_color << std::endl;
  std::cout << "Item at rank 11 is: " << rank_11_color << std::endl
            << std::endl;

  return 0;
}

int hash_table_analysis(std::vector<Color> &colors) {
  HashTable<Color> hash_table(11);

  for (const Color &c : colors) {
    hash_table.insert(c);
  }

  Color pink = {"pink", 0};
  Color green = {"green", 0};
  Color grey = {"grey", 0};

  int color_pink_rank = hash_table.get(pink);
  int color_green_rank = hash_table.get(green);
  int color_grey_rank = hash_table.get(grey);
  std::cout << "Hash Table solution:" << std::endl;

  std::cout << "Rank at color pink is: " << color_pink_rank << std::endl;
  std::cout << "Rank at color green is: " << color_green_rank << std::endl;
  std::cout << "Rank at color grey is: " << color_grey_rank << std::endl
            << std::endl;

  return 0;
}

int bst_analysis(std::vector<Color> &colors) {
  BinarySearchTree<Color> bst;

  // Insert colors into the BST
  for (Color &c : colors) {
    bst.insert(c);
  }

  // Retrieve ranks of specific colors
  int color_white_rank = bst.getRank("white");
  int color_black_rank = bst.getRank("black");
  int color_violet_rank = bst.getRank("violet");

  std::cout << "BST solution:" << std::endl;
  std::cout << "Rank at color white is: " << color_white_rank << std::endl;
  std::cout << "Rank at color black is: " << color_black_rank << std::endl;
  std::cout << "Rank at color violet is: " << color_violet_rank << std::endl;

  return 0;
}

int main() {
  std::vector<Color> color_pairs = {
      {"orange", 4}, {"blue", 7},  {"pink", 5}, {"black", 6},   {"green", 8},
      {"yellow", 1}, {"brown", 2}, {"red", 3},  {"purple", 10}, {"white", 9}};

  heap_analysis(color_pairs);

  hash_table_analysis(color_pairs);

  bst_analysis(color_pairs);

  return 0;
}
