int main() {
  // Priority queues are used by operating systems for scheduling jobs on a CPU.
  // For this example, each iteration of the scheduler will correspond to one
  // cycle of the CPU. Assume each cycle requires one nanosecond. A job will be
  // assigned a name (i.e. “P1”), a priority, and a length. The value of
  // priority will be an integer from -19 to 20 such that 20 is the highest
  // priority and -19 is the lowest priority. The value of length will be an
  // integer from 1 to 100, indicating the number of cycles that are needed to
  // complete the job. A job cannot be interrupted—once a job is scheduled on
  // the CPU, it runs for a number of cycles equal to its length. During each
  // cycle, the CPU will process its current job, add new jobs to the queue, sit
  // and wait until another job is scheduled, or terminate execution (shutdown).
  // Write a program that simulates this job scheduler.
  //
  //
  // We can compute the **average number of jobs in the heap per cycle** by
  // tallying up the total number of jobs in the heap at each clock cycle, and
  // then divide that sum by the total number of cycles required to process the
  // 50 jobs (if it is the case that they all get processed).
  //
  // Each iteration of the scheduler === one cycle of CPU
  // Job = Name, priority, length (number of cycles to complete the job)
  // -19 < priorty < 20
  // 1 < length < 100
  // a job runs for a number of cycles equal to its length
  return 0;
}
