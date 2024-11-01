#pragma once

#include <vector>
template <typename Comparable> void quickSort(std::vector<Comparable> &items) {
  if (items.size() > 1) {
    std::vector<Comparable> smaller;
    std::vector<Comparable> same;
    std::vector<Comparable> larger;

    auto chosenItem = items[items.size() / 2];

    for (auto &i : items) {
      if (i < chosenItem)
        smaller.push_back(std::move(i));
      else if (chosenItem < i)
        larger.push_back(std::move(i));
      else
        same.push_back(std::move(i));
    }

    quickSort(smaller);
    quickSort(larger);

    std::move(begin(smaller), end(smaller), begin(items));
    std::move(begin(same), end(same), begin(items) + smaller.size());
    std::move(begin(larger), end(larger), end(items) - larger.size());
  }
}
