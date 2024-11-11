#include "Job.h"
#include "Scheduler.h"

int main() {
  for (int i = 0; i < 5; i++) {
    std::cout << "\nTest " << (i + 1) << ":\n";
    int completedCount = 0;

    Scheduler<Job> scheduler(50, 2700);
    for (int j = 0; j < 1000; j++) {
      scheduler.startProcessing();
      if (scheduler.isComplete()) {
        completedCount++;
      }
    }

    std::cout << "\nSummary:\n";
    std::cout << "Completed simulations: " << completedCount << "\n";
    std::cout << "Incomplete simulations: " << (1000 - completedCount) << "\n";
  }
  return 0;
}
