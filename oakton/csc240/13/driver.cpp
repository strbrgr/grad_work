#include "HashType.h"
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void buildHashTable(std::ifstream &inFile, HashType<std::string> &hashTable,
                    int type) {
  std::string word;
  int length;
  if (inFile.is_open()) {
    while (inFile >> word) {
      length = word.size();
      for (int i = 0; i < length; i++) {
        if (ispunct(word[i])) {
          word.erase(i--, 1);
          length = word.size();
        }
      }
      if (type == 1)
        hashTable.InsertItemLinear(word);
      else
        hashTable.InsertItemQuadratic(word);
    }
  }
}

int main() {
  std::vector<int> a = {33, 37, 39, 41};
  std::vector<std::string> filePaths = {
      "src/hashText1.txt", "src/hashText2.txt", "src/hashText3.txt",
      "src/hashText4.txt"};

  for (const auto &filePath : filePaths) {
    std::cout << "\nWorking on filepath: " << filePath << "...\n";
    std::ifstream file(filePath);
    int prime;

    if (file >> prime) {
      // LINEAR
      for (int factor : a) {
        // This handles issues with reading the file and skipping to the second
        // line
        file.clear();
        file.seekg(0);
        file >> prime;

        HashType<std::string> linearTable(prime, factor);
        buildHashTable(file, linearTable, 1);
        std::cout << "\nLinear:\n";
        linearTable.Print();
      }
      // QUADRATIC
      for (int factor : a) {
        // This handles issues with reading the file and skipping to the second
        // line
        file.clear();
        file.seekg(0);
        file >> prime;

        HashType<std::string> quadraticTable(prime, factor);
        buildHashTable(file, quadraticTable, 2);
        std::cout << "\nQuadratic:\n";
        quadraticTable.Print();
      }
    }
    file.close();
  }
  return 0;
}
