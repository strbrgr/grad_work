#include <ostream>

using namespace std;

class Job {
public:
  Job();
  Job(int p, int l);
  int getLength() const;
  void decrementLength();
  int getPriority() const;
  friend ostream &operator<<(ostream &out, const Job &j);
  bool operator<(Job otherJob);
  bool operator>(Job otherJob);
  bool operator==(Job otherJob);
  bool operator<=(Job otherJob);

private:
  int length;
  int priority;
};

Job::Job() {}
Job::Job(int p, int l) {}
int Job::getLength() const {}
void Job::decrementLength() {}
int Job::getPriority() const {}
bool Job::operator<(Job otherJob) {}
bool Job::operator>(Job otherJob) {}
bool Job::operator==(Job otherJob) {}
bool Job::operator<=(Job otherJob) {}
