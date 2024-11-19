// -Initialize a skip list so that it can hold at most 500 items.
// skip_list = SkipList()
// -Insert ten (10) items with a random key in the range of 1 to 2000
// -into the skip list. size = 10 i = 1 while i < size + 1 do key = random int
// in range of 1 to 2000
// skip_list.insert(key, "Value” + i) i = i + 1
// -Search for some nodes.
// -For example: result = skip_list.search(10) if result is true
// then output "Value found” else output "Value not found"
// -Remove some nodes.
// -For example: skip_list.remove(5)
// -Display the skip list skip_list.display()
#include "RandomNumber.h"
#include "SkipList.h"
#include <iostream>
#include <string>
#include <vector>

int main() {
  SkipList<std::string> skip_list(9, 0.5);
  std::vector<int> randomNumbers = createLargeVectorRandom();

  // Insert
  for (size_t i = 0; i < randomNumbers.size() - 1; i++) {
    std::string value = "Value" + std::to_string(i);
    skip_list.insert(randomNumbers[i], value);
  }

  std::cout << "\nAfter insertion:" << std::endl;
  skip_list.display();

  // Search
  std::cout << "\nSearching for values..." << std::endl;
  for (int i = 0; i < 10; i += 5) {
    bool result = skip_list.search(i);
    std::string output = result ? "Value found" : "Value not found";
    std::cout << output << std::endl;
  }

  skip_list.display();

  // Remove
  std::cout << "\nRemoving values..." << std::endl;
  for (int i = 0; i < 500; i += 5) {
    bool result = skip_list.remove(i);
  }

  std::cout << "\nFinal  state:" << std::endl;
  skip_list.display();
}
