#include "Bowler.h"
#include "Score.h"
#include <iostream>
#include <unordered_map>

using namespace std;

struct BowlerHash {
    std::size_t operator()(const Bowler& b) const
    {
        // Use a standard hashing functor for strings
        return std::hash<std::string> {}(b.getBowler());
    }
};

int main()
{
    string bowler1FirstName;
    bowler1FirstName = "Bob";
    Bowler bowler1 = Bowler(bowler1FirstName);
    string bowler2FirstName;
    bowler2FirstName = "Alice";
    Bowler bowler2 = Bowler(bowler2FirstName);
    string bowler3FirstName;
    bowler3FirstName = "Tina";
    Bowler bowler3 = Bowler(bowler3FirstName);

    // Creating an unordered_map with string keys and int values
    unordered_map<Bowler, Score, BowlerHash> bowlerDict;

    // Inserting key-value pairs
    bowlerDict[bowler1] = Score(20);
    bowlerDict[bowler2] = Score(10);
    bowlerDict[bowler3] = Score(12);

    cout << "Let's make sure the operator overload for == works" << endl;
    cout << endl;
    cout << "Is Bowler 2 different from Bowler 1?" << endl;
    if (bowler2 == bowler1) {
        cout << "No, Bowler 2 equals Bowler 1" << endl;
    } else {
        cout << "Yes, Bowler 2 is different compared to Bowler 1" << endl;
    }
    cout << endl;
    cout << "Let's print all dictionary entries:" << endl;
    // Iterating through the unordered_map
    for (const auto& entry : bowlerDict) {
        std::cout << entry.first.getBowler() << ": " << entry.second.getScore() << std::endl;
    }

    return 0;
}
