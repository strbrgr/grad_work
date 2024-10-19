#include "BinaryHeap.h"
#include "BinarySearchTree.h"
#include "HashTable.h"
#include "Word.h"
#include <cstddef>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

// Search function to search for max frequent word in heap
//
std::string search_heap_word(const BinaryHeap<Word> &binary_heap,
                             std::string word) {
  const std::vector<Word> &heap_array = binary_heap.getArray();

  // This will have an early return if the word is found
  for (const Word &c : heap_array) {
    if (c.name == word) {
      return c.name;
    }
  }

  return "Item not found";
}

int heap_analysis(const std::vector<Word> &words) {
  // Using a copy here as I don't want to manipulate original vector.
  // I am okay with this due to small input size
  std::vector<Word> words_copy = words;
  BinaryHeap<Word> heap(words_copy);

  // Logic to find most frequently occuring word
  // In a max_heap the value at index 0 is empty
  //
  // Start runtime computing for words
  // see:
  // https://stackoverflow.com/questions/876901/calculating-execution-time-in-c
  auto start_max_item_timer = std::chrono::steady_clock::now();
  Word max_item = heap.getArray().at(1);
  auto end_max_item_timer = std::chrono::steady_clock::now();
  auto diff_max_item_timer = end_max_item_timer - start_max_item_timer;

  // Logic to find 3 words
  auto start_three_words_timer = std::chrono::steady_clock::now();
  std::string terrorists = search_heap_word(heap, "terrorists");
  std::string the = search_heap_word(heap, "the");
  std::string freedom = search_heap_word(heap, "freedom");
  auto end_three_words_timer = std::chrono::steady_clock::now();
  auto diff_three_words_timer = end_three_words_timer - start_three_words_timer;

  std::cout << "Heap solution:" << std::endl;
  std::cout << "Printing item terrorists: " << terrorists << std::endl;
  std::cout << "Printing item the: " << the << std::endl;
  std::cout << "Printing item freedom: " << freedom << std::endl;
  std::cout << "a) Runtime of finding the max item in the max Heap is: "
            << std::endl;
  std::cout
      << std::chrono::duration<double, std::milli>(diff_max_item_timer).count()
      << " ms" << std::endl;
  std::cout << "Max item's count is: " << max_item.count << std::endl;
  std::cout << "Max item's name is: " << max_item.name << std::endl;
  std::cout << "b) Runtime of finding these 3 words in the  maxHeap is: "
            << std::endl;
  std::cout << std::chrono::duration<double, std::milli>(diff_three_words_timer)
                   .count()
            << " ms" << std::endl
            << std::endl;

  return 0;
}

int hash_table_analysis(std::vector<Word> &words) {
  HashTable<Word> hash_table(1723);
  int current_max = 0;
  Word max_item;
  // Insert entries into hashtable
  for (const Word &w : words) {
    // Logic to keep track of max item used later to analyze runtime
    if (w.count > current_max) {
      current_max = w.count;
      max_item = w;
    }
    hash_table.insert(w);
  }

  // Logic to find most frequently occuring word
  // Start runtime computing for words
  // see:
  // https://stackoverflow.com/questions/876901/calculating-execution-time-in-c
  auto start_max_item_timer = std::chrono::steady_clock::now();
  hash_table.get(max_item);
  auto end_max_item_timer = std::chrono::steady_clock::now();
  auto diff_max_item_timer = end_max_item_timer - start_max_item_timer;

  // Logic to find the three words
  Word terrorists = {"terrorists", 0};
  Word the = {"the", 0};
  Word freedom = {"freedom", 0};
  auto start = std::chrono::steady_clock::now();
  int terrorists_rank = hash_table.get(terrorists);
  int the_rank = hash_table.get(the);
  int freedom_rank = hash_table.get(freedom);
  std::cout << "Hash Table solution:" << std::endl;
  auto end = std::chrono::steady_clock::now();
  auto diff = end - start;

  std::cout << "Rank of word terrorists is: " << terrorists_rank << std::endl;
  std::cout << "Rank of word the is: " << the_rank << std::endl;
  std::cout << "Rank of word freedom is: " << freedom_rank << std::endl;
  std::cout << "a) Runtime of finding the max item in the Hash Table is: "
            << std::endl;
  std::cout
      << std::chrono::duration<double, std::milli>(diff_max_item_timer).count()
      << " ms" << std::endl;
  std::cout << "Max item's count is: " << max_item.count << std::endl;
  std::cout << "Max item's name is: " << max_item.name << std::endl;
  std::cout << "b) Runtime of finding these 3 words in the Hash Table is: "
            << std::endl;
  std::cout << std::chrono::duration<double, std::milli>(diff).count() << " ms"
            << std::endl
            << std::endl;

  return 0;
}

int bst_analysis(std::vector<Word> &words) {
  BinarySearchTree<Word> bst;

  int current_max_count = 0;
  // Insert colors into the BST
  for (Word &w : words) {
    if (w.count > current_max_count) {
      current_max_count = w.count;
    }

    bst.insert(w);
  }

  // Logic to find most frequently occuring word
  // Start runtime computing for words
  // see:
  // https://stackoverflow.com/questions/876901/calculating-execution-time-in-c
  auto start_max_item_timer = std::chrono::steady_clock::now();
  Word max_item = bst.findMax();
  auto end_max_item_timer = std::chrono::steady_clock::now();
  auto diff_max_item_timer = end_max_item_timer - start_max_item_timer;

  // Logic to find the three words
  //
  // Start runtime computing for words in bst
  // see:
  // https://stackoverflow.com/questions/876901/calculating-execution-time-in-c
  auto start = std::chrono::steady_clock::now();
  // Retrieve ranks of specific colors
  int terrorists_rank = bst.getRank("terrorists");
  int the_rank = bst.getRank("the");
  int freedom_rank = bst.getRank("freedom");
  auto end = std::chrono::steady_clock::now();
  auto diff = end - start;

  std::cout << "BST solution:" << std::endl;
  std::cout << "Rank of word terrorist is: " << terrorists_rank << std::endl;
  std::cout << "Rank of word the is: " << the_rank << std::endl;
  std::cout << "Rank of word freedom is: " << freedom_rank << std::endl;
  std::cout << "a) Runtime of finding the max item in BST is: " << std::endl;
  std::cout
      << std::chrono::duration<double, std::milli>(diff_max_item_timer).count()
      << " ms" << std::endl;
  std::cout << "Max item's count is: " << max_item.count << std::endl;
  std::cout << "Max item's name is: " << max_item.name << std::endl;
  std::cout << "b) Runtime of finding these 3 words in the BST is: "
            << std::endl;
  std::cout << std::chrono::duration<double, std::milli>(diff).count() << " ms"
            << std::endl;
  return 0;
}

std::string clean_word(std::string word) {
  std::string cleaned_word;
  // Loop over each character, only add actual characters to the word
  for (char c : word) {
    if (std::isalpha(static_cast<unsigned char>(c))) {
      cleaned_word += c;
    }
  }

  return cleaned_word;
}

std::vector<Word> read_file_and_extract_words() {
  // Reading file according to documentation:
  // https://cplusplus.com/doc/tutorial/files/
  std::string line;
  std::ifstream file("src/PatriotAct.txt");
  // Will hold a vector of lines
  std::vector<std::string> input;
  // Will hold a vector of words after cleaning each line
  std::vector<std::string> words;
  std::unordered_map<std::string, int> words_freq;
  // Will hold a vector of words and their freq
  std::vector<Word> word_pairs;

  if (!file.is_open()) {
    std::cout << "Unable to open file";
  }

  while (getline(file, line)) {
    // Reading lines into vector
    input.push_back(line);
  }
  file.close();

  // Loop over input so that we can work on each line
  for (const std::string &line : input) {

    // Using isstringstream as it provides better handling of whitespace when
    // iterating over words
    // see;
    // https://www.tutorialspoint.com/how-to-process-strings-using-std-istringstream
    std::istringstream iss(line);
    std::string word;

    while (iss >> word) {
      std::string cleaned_word = clean_word(word);
      // std::cout << cleaned_word << std::endl;
      // Need to account for empty strings that come back due to words that
      // consist of only numbers
      if (!cleaned_word.empty()) {
        // cleaned word is not yet in map
        if (words_freq.find(cleaned_word) == words_freq.end()) {
          words_freq[cleaned_word] = 1;
        } else {
          words_freq[cleaned_word] += 1;
        }
      }
    }
  }

  // Using structured binding, available in C++ 17
  // see:
  // https://stackoverflow.com/questions/50870951/iterating-over-unordered-map-c
  for (auto &[key, value] : words_freq) {
    Word word = {key, value};
    word_pairs.push_back(word);
  };

  return word_pairs;
}

int main() {
  std::vector<Word> words = read_file_and_extract_words();

  heap_analysis(words);

  hash_table_analysis(words);

  bst_analysis(words);

  return 0;
}
