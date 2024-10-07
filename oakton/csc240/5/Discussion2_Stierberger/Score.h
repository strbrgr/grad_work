#include <string>

using namespace std;

class Score {
public:
  Score();
// Function :constructor
// Post: Initializes 'score' to default 0

  Score(int score);
// Function: constructor with param
// Post: Initializes 'score' to 'score'

  int getScore() const;

private:
  int score;
};
