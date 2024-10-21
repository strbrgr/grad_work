#include "iostream"
#include <optional>
#include <vector>

// optional doc:
// https://devblogs.microsoft.com/cppblog/stdoptional-how-when-and-why/
std::optional<int> find_majority_element_candidate(std::vector<int> &input) {
  std::vector<int> b;
  if (input.empty()) {
    return std::nullopt;
  }
  // recursive base case
  if (input.size() == 1) {
    return input.at(0);
  }

  for (int i = 0; i < input.size(); i += 2) {
    // Handle out of bounds err
    if (i + 1 < input.size() && input.at(i) == input.at(i + 1)) {
      b.push_back(input.at(i));
    } else if (i + 1 == input.size()) {
      // If odd count, push the last element
      b.push_back(input.at(i));
    }
  }

  return find_majority_element_candidate(b);
};

std::optional<int> find_majority_element(std::vector<int> &input) {
  std::optional<int> candidate = find_majority_element_candidate(input);

  if (candidate.has_value()) {
    int count = 0;
    for (const int &n : input) {
      if (n == candidate.value()) {
        count++;
      }
    }

    if (count > input.size() / 2) {
      return candidate;
    };
  }

  return std::nullopt;
};

int main() {
  std::vector<int> a_with_majority = {3, 3, 4, 2, 4, 4, 2, 4, 4};
  std::vector<int> a_without_majority = {3, 3, 4, 2, 4, 4, 2, 4};

  std::optional<int> majority_element = find_majority_element(a_with_majority);

  if (majority_element.has_value()) {
    std::cout << "Majority Element is: " << majority_element.value()
              << std::endl;
  } else {
    std::cout << "No Majority element" << std::endl;
  }

  std::optional<int> majority_element2 =
      find_majority_element(a_without_majority);

  if (majority_element2.has_value()) {
    std::cout << "Majority Element is: " << majority_element2.value()
              << std::endl;
  } else {
    std::cout << "No Majority element" << std::endl;
  }

  return 0;
}
