#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "Job.h"
#include "PQType.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>

enum cpuStatus { PROCESSING, IDLE };

template <class ItemType> class Scheduler : public PQType<ItemType> {
private:
  int numJobs;
  int nanoSeconds;
  ItemType currentJob;
  cpuStatus status;
  int completedJobs;
  long long totalJobsInHeap;
  int cycleCount;

  std::mt19937 rng;
  std::uniform_int_distribution<int> priorityDist;
  std::uniform_int_distribution<int> lengthDist;
  // Coinflip according to:
  // https://en.cppreference.com/w/cpp/numeric/random/bernoulli_distribution
  // last accessed: 11/08/24
  std::bernoulli_distribution coinFlip;

  void reset() {
    // Clear the priority queue
    while (!this->IsEmpty()) {
      ItemType temp;
      this->Dequeue(temp);
    }

    completedJobs = 0;
    totalJobsInHeap = 0;
    status = IDLE;
    nanoSeconds = cycleCount;
    currentJob = ItemType(); // Reset current job
  }

public:
  // TODO: look into formatting entries on separate line
  Scheduler(int size, int seconds)
      : PQType<ItemType>(size), numJobs(0), nanoSeconds(seconds), status(IDLE),
        completedJobs(0), totalJobsInHeap(0), cycleCount(seconds),
        rng(std::random_device{}()), priorityDist(-19, 20), lengthDist(1, 100),
        coinFlip(0.5) {}

  Job createJob() { return Job(priorityDist(rng), lengthDist(rng)); }

  bool shouldAddJob() { return coinFlip(rng); }

  void startProcessing() {
    // Clear old simu
    reset();
    int jobsInHeap = 0;
    int cycles = 0;

    while (nanoSeconds > 0 && completedJobs < 50) {
      // Initially add a job if heap is empty
      if (this->IsEmpty() && jobsInHeap < 50 - completedJobs) {
        Job job = createJob();
        this->Enqueue(job);
        jobsInHeap++;
      }

      if (status == IDLE) {
        if (!this->IsEmpty()) {
          this->Dequeue(currentJob);
          jobsInHeap--;
          status = PROCESSING;
        }
      }

      if (status == PROCESSING) {
        currentJob.decrementLength();
        if (currentJob.getLength() == 0) {
          completedJobs++;
          status = IDLE;
        }
      }

      // interarrival
      if (nanoSeconds % 20 == 0) {
        if (!this->IsFull() && jobsInHeap < 50 - completedJobs) {
          if (shouldAddJob()) {
            Job job = createJob();
            this->Enqueue(job);
            jobsInHeap++;
          }
        }
      }

      totalJobsInHeap += jobsInHeap;
      nanoSeconds--;
      cycles++;
    }

    // At this point we are done no matter what
    double avgJobsInHeap = static_cast<double>(totalJobsInHeap) / cycles;
    std::cout << "Average number of jobs in the heap per cycle: "
              << avgJobsInHeap << "\n";

    if (completedJobs == 50) {
      std::cout << "The scheduler completed all 50 jobs.\n";
      std::cout << "It took " << cycles << " cycles to complete them.\n";
    } else {
      std::cout << "The scheduler did not complete all 50 jobs.\n";
      std::cout << "Jobs processed: " << completedJobs << "\n";
    }
  }

  // Helper function for driver logs
  //
  bool isComplete() const { return completedJobs == 50; }
};

#endif
