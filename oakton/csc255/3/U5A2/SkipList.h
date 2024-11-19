#include <cstdlib>
#include <iostream>
#include <limits>
#include <ostream>
#include <vector>

template <typename T> struct SkipListNode {
  int key;
  T value;
  // Holds a the next pointer per level of each node
  std::vector<SkipListNode *> forward;
  // Level of the node in the SL
  int level;

  SkipListNode(int key, T value, int level)
      : key(key), value(value), level(level) {
    forward.resize(level, nullptr);
  }
};

template <typename T> class SkipList {
private:
  SkipListNode<T> *head;
  int max_level;
  float probability;

public:
  SkipList(int max_level, float probability)
      : max_level(max_level), probability(probability) {
    // Head should have -inf as key, and max_level as level. It has to be as
    // high as possible
    head = new SkipListNode<T>(std::numeric_limits<int>::min(), T(), max_level);
    head->level = max_level;
  };

  ~SkipList() {
    SkipListNode<T> *current = head;
    while (current != nullptr) {
      SkipListNode<T> *next = current->forward[0];
      delete current;
      current = next;
    }
  }

  bool search(int K) {
    SkipListNode<T> *node = head;
    // Traverse from the top level
    for (int i = head->level - 1; i >= 0; i--) {
      // This moves while we are not at the end
      // and while the nodes key is smaller than K
      // If either is false we break out of the while loop and move one level
      // down
      while (node->forward[i] != nullptr && node->forward[i]->key < K) {
        node = node->forward[i];
      }
    }
    // We must be in front of the key we want to find so we should advance one
    // more time
    node = node->forward[0];
    // Are we at the end or did we find Key?
    return (node != nullptr && node->key == K);
  };

  void insert(int K, T value) {
    // This will hold the pointers to the traversed levels so that we can
    // connect each level of the inserted node
    std::vector<SkipListNode<T> *> update(max_level, nullptr);
    SkipListNode<T> *node = head;
    // Same logic as search.
    // Traverse from the top level
    for (int i = max_level - 1; i >= 0; i--) {
      // This moves while we are not at the end
      // and while the nodes key is smaller than K
      // If either is false we break out of the while loop and move one level
      // down
      while (node->forward[i] != nullptr && node->forward[i]->key < K) {
        node = node->forward[i];
      }
      // Whenever we move down a level we want to record this in update vector
      update[i] = node;
    }
    // We must be in front of the key we want to find so we should advance one
    // more time
    node = node->forward[0];

    // Already there so let's update
    if (node != nullptr && node->key == K) {
      node->value = value;
    } else {
      int lvl = randomLevel();
      // If the lvl is bigger than the level we need to account for the update
      // pointers, and increase the lists level
      if (lvl > head->level) {
        // This loop will start a level above the current max and go towards lvl
        for (int i = head->level + 1; i <= lvl; i++) {
          // So if current level is 5 this would start at update[6]
          update[i] = head;
        }
        // Here we update level to be of height lvl
        head->level = lvl;
      }

      // Create new node which will be used to connect level
      SkipListNode<T> *newNode = new SkipListNode<T>(K, value, lvl);

      for (int i = 0; i < lvl; i++) {
        newNode->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = newNode;
      }
    }
  }

  bool remove(int K) {
    std::vector<SkipListNode<T> *> update(head->level, nullptr);
    SkipListNode<T> *node = head;

    for (int i = max_level - 1; i >= 0; i--) {
      while (node->forward[i] != nullptr && node->forward[i]->key < K) {
        node = node->forward[i];
      }

      update[i] = node;
    }
    // We must be in front of the key we want to find so we should advance one
    // more time
    node = node->forward[0];

    if (node != nullptr && node->key == K) {
      for (int i = 0; i < max_level; i++) {
        if (update[i]->forward[i] != node) {
          break;
        }
        update[i]->forward[i] = node->forward[i];
      }
      delete node;
      return true;
    }
    return false;
  }

  void display() {
    for (int i = max_level - 1; i >= 0; i--) {
      std::cout << "Traverse through level: " << i << std::endl;
      SkipListNode<T> *node = head;
      while (node != nullptr) {
        std::cout << "Key: " << node->key << ", Value: " << node->value
                  << std::endl;
        node = node->forward[i];
      }
      std::cout << "nullptr" << std::endl;
    }
  };

  // IMplementation according to original paper from pugh:
  // https://15721.courses.cs.cmu.edu/spring2018/papers/08-oltpindexes1/pugh-skiplists-cacm1990.pdf
  // Last referenced: 10/29/24
  int randomLevel() {
    float r = (float)rand() / RAND_MAX;
    int lvl = 1;
    while (r < probability && lvl < max_level) {
      lvl++;
      r = (float)rand() / RAND_MAX;
    }
    return lvl;
  };
};
