#include <iostream>
#include "unsorted.h"
using namespace std;
int main() {
UnsortedType classList;
classList.PutItem(ItemType(4));
classList.PutItem(ItemType(5));
classList.PutItem(ItemType(4));
classList.PutItem(ItemType(4));
classList.PutItem(ItemType(8));
cout << "(original) length: " << classList.GetLength() << endl;
classList.ResetList();
classList.Print();
classList.ShiftRight();
cout << "(shifted right) length: " << classList.GetLength() << endl;
classList.ResetList();
classList.Print();
classList.DeleteItem(ItemType(4));
cout << "(delete all 4s) length: " << classList.GetLength() << endl;
classList.ResetList();
classList.Print();
classList.ShiftRight();
cout << "(shift right) length: " << classList.GetLength() << endl;
classList.ResetList();
classList.Print();
return 0;
}
