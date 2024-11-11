#ifndef JOB_H
#define JOB_H
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
Job::Job(int p, int l) : priority(p), length(l) {}
int Job::getLength() const { return length; }
void Job::decrementLength() { length--; }
int Job::getPriority() const { return priority; }
bool Job::operator<(Job otherJob) { return priority < otherJob.priority; }
bool Job::operator>(Job otherJob) { return priority > otherJob.priority; }
bool Job::operator==(Job otherJob) { return priority == otherJob.priority; }
bool Job::operator<=(Job otherJob) { return priority <= otherJob.priority; }

#endif
