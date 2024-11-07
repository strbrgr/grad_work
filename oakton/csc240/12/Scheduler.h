#include "PQType.h"

template <class ItemType> class Scheduler : public PQType<ItemType> {
public:
  Scheduler(int s);
  int getNumJobs() const;
  void setCurrentJob(ItemType &j);
  void addJob(ItemType &j);
  void removeJob(ItemType &j);

private:
  int numJobs;
  ItemType currentJob;
};

template <class ItemType>
Scheduler<ItemType>::Scheduler(int size) : PQType<ItemType>(size) {
  numJobs = 0;
}

template <class ItemType> int Scheduler<ItemType>::getNumJobs() const {}

template <class ItemType>
void Scheduler<ItemType>::setCurrentJob(ItemType &j) {}

template <class ItemType> void Scheduler<ItemType>::addJob(ItemType &j) {}

template <class ItemType> void Scheduler<ItemType>::removeJob(ItemType &j) {}
