#ifndef INDEXED_PRIORITY_QUEUE_H_
#define INDEXED_PRIORITY_QUEUE_H_
#include <vector>

// 1-based heap
class IndexedPriorityQueue {
public:
  IndexedPriorityQueue(int capacity);

  bool Empty();
  bool Contains(int key);
  int Size();
  int TopIndex();   // return the key index of on the heap top
  float WeightOf(int key);

  void Pop();
  void Insert(int key, float weight);
  void Delete(int key);
  void Change(int key, float weight);

private:

  bool Less(int i, int j);
  
  void Swim(int i);
  void Sink(int i);
  void Swap(int i, int j);
  void DeleteHeapIndex(int i);

  int Parent(int i);
  int LeftChild(int i);
  int RightChild(int i);


  int capacity_;
  int size_;

  std::vector<int> heap_index_; // key index -> heap index
  std::vector<float> weights_;  // key index -> weight
  std::vector<int> heap_;       // heap index -> key index
};

#endif // INDEXED_PRIORITY_QUEUE_H_
