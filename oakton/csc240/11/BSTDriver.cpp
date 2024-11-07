#include "BST.h"
#include <cctype>
#include <cstring>
#include <fstream>
#include <iostream>

int main() {
  TreeType tree;
  OrderType order;
  std::string item;
  std::ofstream outFile;
  std::string outFileName;
  std::cout << "Enter name of output file; press return." << std::endl;
  std::cin >> outFileName;
  outFile.open(outFileName.c_str());
  tree.PutItem('J');
  tree.PutItem('D');
  tree.PutItem('A');
  tree.PutItem('B');
  tree.PutItem('G');
  tree.PutItem('E');
  tree.PutItem('H');
  tree.PutItem('F');
  tree.PutItem('P');
  tree.PutItem('K');
  tree.PutItem('L');
  tree.PutItem('U');
  tree.PutItem('S');
  tree.PutItem('T');
  tree.PutItem('W');
  tree.PutItem('X');
  tree.PutItem('Y');
  order = IN_ORDER;
  tree.ResetTree(order);
  tree.Print(outFile);
  // std::cout << tree.Ancestors('T') << std::endl;
  return 0;
}
