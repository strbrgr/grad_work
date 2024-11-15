#include "Input.h"
#include <charconv>
#include <format>
#include <optional>
#include <set>
#include <string>
#include <unordered_map>

typedef std::vector<std::vector<std::string>> Book;
typedef std::unordered_map<std::string, std::set<int>> Index;

Index createIndex(Book &book) {
  Index index;
  for (const auto &page : book) {
    for (size_t i = 0; i < page.size(); ++i) {
      Index::const_iterator itr;
      std::string word = page[i];
      itr = index.find(word);
      // Not found condition
      if (itr == index.end()) {
        std::set<int> pageNumbers;
        pageNumbers.insert(i);
        index[word] = pageNumbers;
      } else { // Found condition
        index[word].insert(i);
      }
    }
  }

  return index;
}

std::optional<std::set<int>> lookup(std::string word, Index &index) {
  Index::const_iterator itr;
  itr = index.find(word);
  // Not found condition
  if (itr == index.end()) {
    return std::nullopt;
  } else { // Found condition
    return index[word];
  }
}

void writeIndex(Index &index) {
  std::ofstream outfile("result/Orwell_1984_Index.txt");
  if (!outfile) {
    std::cerr << "File could not be opened for writing." << std::endl;
    return;
  }

  for (auto &[key, value] : index) {
    std::ostringstream pageNumbersStream;

    // Using an iterator so that we can check for last elelemt and avoid adding
    // a comma
    for (auto it = value.begin(); it != value.end(); ++it) {
      pageNumbersStream << *it;
      // Check if this is not the last element
      if (std::next(it) != value.end()) {
        pageNumbersStream << ", ";
      }
    }

    std::ostringstream lineStream;
    lineStream << key << ", " << pageNumbersStream.str();

    outfile << lineStream.str() << std::endl;
  }

  outfile.close();
}

void testIndex(Index &index) {
  std::cout << "\nTesting Lookup in Index\n";
  std::cout << "Trying to find word 'you'" << std::endl;
  std::optional<std::set<int>> pageNumbers = lookup("you", index);

  if (pageNumbers.has_value()) {
    std::cout << "Found on pages: " << std::endl;
    for (auto &i : pageNumbers.value()) {
      std::cout << i << ' ';
    }
  } else {
    std::cout << "Word not found in Index." << std::endl;
  }

  std::cout << "\nTesting Lookup in Index\n";
  std::cout << "Trying to find word 'thunderstorm'" << std::endl;
  std::optional<std::set<int>> pageNumbers2 = lookup("thunderstorm", index);

  if (pageNumbers2.has_value()) {
    std::cout << "Found on pages: " << std::endl;
    for (auto &i : pageNumbers2.value()) {
      std::cout << i << ' ';
    }
  } else {
    std::cout << "Word not found in Index." << std::endl;
  }
}

int main() {
  // Book
  Book book = read_file_and_extract_words();
  // Index I, Map where key is each word and value is a set of page numbers
  Index index = createIndex(book);
  testIndex(index);
  writeIndex(index);

  return 0;
}
