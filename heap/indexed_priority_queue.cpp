#include "indexed_priority_queue.h"
#include <iostream>
#include <cassert>

IndexedPriorityQueue::IndexedPriorityQueue(int capacity) : capacity_(capacity), size_(0) {
  heap_index_.resize(capacity + 1); 
  weights_.resize(capacity + 1);    
  heap_.resize(capacity + 1);       
}

bool IndexedPriorityQueue::Empty() {
    return size_ == 0;
}

bool IndexedPriorityQueue::Contains(int key) {
    // Our heap is 1-based, so 0 is used to check validity
    return heap_index_[key] != 0;
}

int IndexedPriorityQueue::Size() {
    return size_;
}

// return the key index of on the heap top
int IndexedPriorityQueue::TopIndex() {
    assert(size_ != 0);
    return heap_[1];
}

float IndexedPriorityQueue::WeightOf(int key) {
    return weights_[key];
}

void IndexedPriorityQueue::Pop() {
    assert(size_ > 0);
    DeleteHeapIndex(1);
}

void IndexedPriorityQueue::Insert(int key, float weight) {
    assert(size_ < capacity_);

    weights_[key] = weight;
    size_++;
    heap_index_[key] = size_;
    heap_[size_] = key;

    Swim(size_);
}

void IndexedPriorityQueue::Delete(int key) {
    assert(Contains(key));

    DeleteHeapIndex(heap_index_[key]);
}

void IndexedPriorityQueue::Change(int key, float weight) {
    assert(Contains(key));

    weights_[key] = weight;
    Swim(heap_index_[key]);
    Sink(heap_index_[key]);
}

void IndexedPriorityQueue::Swim(int i) {
    int parent = Parent(i);
    while (i > 1 && Less(i, parent)) {
       Swap(i, parent); 
       i = parent;
       parent = Parent(i);
    }
}

void IndexedPriorityQueue::Sink(int i) {

    while (i <= size_) {
        int left_child = LeftChild(i);
        int right_child = RightChild(i);

        int min_index = i;
        if (left_child <= size_ && Less(left_child, min_index)) {
            min_index = left_child;
        }
        if (right_child <= size_ && Less(right_child, min_index)) {
            min_index = right_child;
        }

        if (min_index != i) {
            Swap(i, min_index);
            i = min_index;
            continue;
        }

        break;
    }
}

void IndexedPriorityQueue::Swap(int i, int j) {
    std::swap(heap_index_[heap_[i]], heap_index_[heap_[j]]);
    std::swap(heap_[i], heap_[j]);
}

int IndexedPriorityQueue::Parent(int i) {
    return i / 2;
}

int IndexedPriorityQueue::LeftChild(int i) {
    return 2 * i;
}

int IndexedPriorityQueue::RightChild(int i) {
    return 2 * i + 1;
}

bool IndexedPriorityQueue::Less(int i, int j) {
    return weights_[heap_[i]] < weights_[heap_[j]];
}

void IndexedPriorityQueue::DeleteHeapIndex(int i) {
    assert(i >= 1 && i <= size_);

    size_--;
    Swap(i, size_ + 1);
    Sink(i);
    heap_index_[heap_[size_ + 1]] = 0;
}

