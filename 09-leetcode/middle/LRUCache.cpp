#include <iostream>
#include <map>
using namespace std;
struct DLinkedNode {
  int key, value;
  DLinkedNode* prev;
  DLinkedNode* next;
  DLinkedNode() : key(0), value(0), prev(nullptr), next(nullptr) {}
  DLinkedNode(int _key, int _value) : key(_key), value(_value), prev(nullptr), next(nullptr) {}
};

class LRUCache {
 private:
  unordered_map<int, DLinkedNode*> cache;
  DLinkedNode* head;
  DLinkedNode* tail;
  int size;
  int capacity;

 public:
  LRUCache(int _capacity) : capacity(_capacity), size(0) {
    head = new DLinkedNode();
    tail = new DLinkedNode();
    head->next = tail;
    tail->prev = head;
  }

  int get(int key) {
    if (!cache.count(key)) {
      return -1;
    }
    DLinkedNode* node = cache[key];
    moveToHead(node);
    return node->value;
  }

  void put(int key, int value) {
    if (!cache.count(key)) {
      DLinkedNode* node = new DLinkedNode(key, value);
      cache[key] = node;
      addToHead(node);
      ++size;
      if (size > capacity) {
        DLinkedNode* removed = removeTail();
        cache.erase(removed->key);
        delete removed;
        --size;
      }
    } else {
      DLinkedNode* node = cache[key];
      node->value = value;
      moveToHead(node);
    }
  }

  void addToHead(DLinkedNode* node) {
    node->prev = head;
    node->next = head->next;
    head->next->prev = node;
    head->next = node;
  }

  void removeNode(DLinkedNode* node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
  }

  void moveToHead(DLinkedNode* node) {
    removeNode(node);
    addToHead(node);
  }

  DLinkedNode* removeTail() {
    DLinkedNode* node = tail->prev;
    removeNode(node);
    return node;
  }
};

int main(int argc, char const* argv[]) {
  LRUCache* cache = new LRUCache(2);
  cache->put(1, 1);
  cache->put(2, 2);
  cout << cache->get(1) << endl;
  cache->put(3, 3);
  cout << cache->get(2) << endl;

  cache->put(4, 4);
  cout << cache->get(1) << endl;
  cout << cache->get(3) << endl;
  cout << cache->get(4) << endl;

  return 0;
}
