#include "min_heap.h"
#include <stdexcept>
#include <stdlib.h>

MinHeap::MinHeap(int capacity) : arr_(nullptr), capacity_(capacity), size_(0) {
    arr_ = (int *)malloc(sizeof(int) * (capacity_ + 1));
}

MinHeap::~MinHeap() {
    delete []arr_;
}


MinHeap::MinHeap(int array[], int size) : arr_(nullptr), capacity_(size), size_(size) {
    arr_ = new int[size + 1];

    for (int i = 0; i < size; i++) {
      arr_[i + 1] = array[i];
    }

    int last_parent_index = Parent(size);

    for (int i = last_parent_index; i > 0; i--) {
      Sink(i);
    }
}

void MinHeap::Reserve(int requiresize_) {
	if (capacity_ >= requiresize_)
		return;

	int newcapacity_ = capacity_ ? capacity_ * 2 : INIT_HEAP_CAPACITY ;
	if (newcapacity_ < requiresize_)
		newcapacity_ = requiresize_;

	capacity_ = newcapacity_;

    int *new_arr = new int[capacity_ + 1];

    if (arr_) {
        for (int i = 0; i < size_; i++) {
            new_arr[i + 1] = arr_[i + 1];
        }
        delete []arr_;
    }

    arr_ = new_arr;
}

bool MinHeap::IsEmpty() {
	return size_ == 0;
}

int MinHeap::Top() {

	if (!size_) {
        throw std::runtime_error("minheap is empty");
    }

    return arr_[1];
}

void MinHeap::Pop() {
	int r = arr_[1];

	Swap(1, size_);
	size_--;

	Sink(1);
}

void MinHeap::Sink(int i) {
	int l = LeftChild(i);
	int r = RightChild(i);

	int min_index = i;

	if (l <= size_ && arr_[l] < arr_[min_index])
		min_index = l;
	if (r <= size_ && arr_[r] < arr_[min_index])
		min_index = r;

	if (min_index != i) {
		Swap(i, min_index);
		Sink(min_index);
	}
}

void MinHeap::Swim(int i) {

	int parent = Parent(i);

	while (i != 1 && arr_[i] < arr_[parent]) {
		Swap(i, parent);

		i = parent;
		parent = Parent(i);
	}
}

void MinHeap::InsertKey(int k) {
	Reserve(size_ + 1);
	++size_;
    arr_[size_] = k;

    Swim(size_);
}

void MinHeap::Swap(int i, int j) {
	int k = arr_[i];
	arr_[i] = arr_[j];
	arr_[j] = k;
}
