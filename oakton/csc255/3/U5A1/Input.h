#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

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

std::vector<std::vector<std::string>> read_file_and_extract_words() {
  // Reading file according to documentation:
  // https://cplusplus.com/doc/tutorial/files/
  std::string line;
  std::ifstream file("src/Orwell_1984.txt");
  // Will hold a vector of lines
  std::vector<std::string> input;
  // Will hold a vector of words after cleaning each line
  std::vector<std::string> words;
  std::unordered_map<std::string, int> words_freq;
  // Will hold a vector of words and their freq

  if (!file.is_open()) {
    std::cout << "Unable to open file";
  }

  while (getline(file, line)) {
    // Reading lines into vector
    input.push_back(line);
  }
  file.close();

  std::vector<std::vector<std::string>> pages;
  std::vector<std::string> page;

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
        page.push_back(cleaned_word);
      }

      if (page.size() == 250) {
        pages.push_back(page);
        page.clear();
      }
    }
  }

  return pages;
}
