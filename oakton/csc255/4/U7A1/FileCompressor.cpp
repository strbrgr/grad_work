#include "BinaryHeap.h"
#include <cassert>
#include <fstream>
#include <string>
#include <tuple>
#include <unordered_map>

struct NodeType {
  char character;
  int frequency;
  NodeType *left;
  NodeType *right;

  // Overload operator for comparison
  bool operator<(const NodeType &other) const {
    return frequency < other.frequency; // for min-heap
  }
  bool operator>(const NodeType &other) const {
    return frequency > other.frequency; // for min-heap
  }
};

std::string decode(NodeType *root, std::string sequence,
                   std::string decodeEncodedValue = "") {
  NodeType *current = root;
  for (char bit : sequence) {
    if (!current)
      return "";

    current = (bit == '1') ? current->right : current->left;

    if (!current->left && !current->right) {
      decodeEncodedValue += current->character;
      // REstart
      current = root;
    }
  }

  return decodeEncodedValue;
}

std::optional<std::string> encodeHelper(std::string path, NodeType *root,
                                        char character) {
  // base case
  if (root == nullptr) {
    return std::nullopt;
  }

  if (root->left == nullptr && root->right == nullptr) {
    // found case
    if (root->character == character) {
      return path;
    }
  }

  path.push_back('0');
  auto leftResult = encodeHelper(path, root->left, character);
  if (leftResult) {
    return leftResult;
  }
  // This would run if at some point we don't find the character in the
  // recursive calss
  path.pop_back();

  path.push_back('1');
  auto rightResult = encodeHelper(path, root->right, character);
  if (rightResult) {
    return rightResult;
  }
  // This would run if at some point we don't find the character in the
  // recursive calss
  path.pop_back();

  return std::nullopt;
}

NodeType *huffman(std::string &input, std::unordered_map<char, int> char_freq) {

  BinaryHeap<NodeType> q;

  // Build the min heap
  for (const auto &[key, value] : char_freq) {
    // Create a single-node binary tree T storing c
    NodeType node = {key, value, nullptr, nullptr};
    q.insert(node);
  }

  // While length(Q) > 1
  while (!q.isEmpty()) {
    NodeType f1 = *q.getTop();
    q.deleteMin();

    if (q.isEmpty())
      break; // Check if there's only one node left

    NodeType f2 = *q.getTop();
    q.deleteMin();

    // Create a new binary tree T with left subtree T1 and right subtree T2
    NodeType combinedNode = {' ', f1.frequency + f2.frequency, new NodeType(f1),
                             new NodeType(f2)};
    q.insert(combinedNode);
  }

  return new NodeType(*q.getTop()); // Return a copy of the top node
}

void createTable(std::unordered_map<char, int> char_freq, std::string result,
                 std::unordered_map<char, std::string> codeMap) {
  std::cout << "---------------------------------------------------\n";
  std::cout << "Character\tCode\tFrequency\tTotal Bits\n";
  std::cout << "---------------------------------------------------\n";
  int totalBits = 0;

  for (const auto &[key, value] : char_freq) {
    int bits = codeMap[key].size() * value;
    totalBits += bits;
    std::string code = codeMap[key];
    std::cout << key << "\t\t" << code << "\t\t" << value << "\t\t" << bits
              << "\n";
  }
  std::cout << "---------------------------------------------------\n";
  std::cout << "Total\t\t\t\t\t\t" << totalBits << "\n";
  std::cout << "---------------------------------------------------\n";
}
std::tuple<std::string, std::unordered_map<char, std::string>>
encode(std::string input, std::unordered_map<char, int> char_freq,
       NodeType *tree) {
  std::string result;
  // Stores code at 1 and char at 0
  std::unordered_map<char, std::string> codeMap;

  // Encode input
  for (const auto &character : input) {
    auto encodedValue = encodeHelper("", tree, character);
    if (encodedValue.has_value()) {
      codeMap[character] = *encodedValue;
      // Keep track of encodedValue to create map
      result += *encodedValue;
    }
  };

  return std::make_tuple(result, codeMap);
}

std::unordered_map<char, int> createFreqMap(std::string input) {
  std::unordered_map<char, int> char_freq;
  // Compute the frequency f(c) of each character c of input
  for (const auto &character : input) {
    char_freq[character]++;
  }

  return char_freq;
}

std::string readInput() {
  std::ifstream file("src/huffman.in");
  std::string line;
  std::string input;

  // Read file
  if (!file.is_open()) {
    std::cout << "Unable to open file";
  }

  while (getline(file, line)) {
    input += line;
  }
  file.close();

  return input;
}

void writeToFile(std::string encodedValue) {
  // write encoded input to file
  std::ofstream outfile("src/huffman.out");
  if (!outfile) {
    std::cerr << "File could not be opened for writing." << std::endl;
  }

  outfile << encodedValue << std::endl;
  outfile.close();

  std::cout << "Encoded Output: " << encodedValue << std::endl;
}

int main() {
  std::string input = readInput();
  std::unordered_map<char, int> char_freq = createFreqMap(input);
  NodeType *tree = huffman(input, char_freq);
  std::tuple<std::string, std::unordered_map<char, std::string>>
      encodedValueTuple = encode(input, char_freq, tree);
  std::string encodedValue = std::get<0>(encodedValueTuple);
  std::unordered_map<char, std::string> codeMap =
      std::get<1>(encodedValueTuple);
  createTable(char_freq, encodedValue, codeMap);
  writeToFile(encodedValue);
  std::string decodeEncodedValue = decode(tree, encodedValue);
  std::cout << decodeEncodedValue << "\n";
  assert(input == decodeEncodedValue);

  std::cout << "Unencoded Bits needed" << decodeEncodedValue.size() << "\n";

  std::cout << "Encoded Bits needed: 38 (see above) \n";

  std::cout << "Assertion passed. ";

  return 0;
}
