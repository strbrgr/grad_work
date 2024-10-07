#include "Score.h"
#include <iostream>

using namespace std;

Score::Score()
// Function :constructor
// Post: Initializes 'score' to 0
{
  score = 0;
}

Score::Score(int s)
// Function: constructor with param
// Post: Initializes 'score' to 'score'
{
  score = s;
}

int Score::getScore() const
{
  return score;
}
