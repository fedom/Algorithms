#ifndef MIN_HEAP_H_
#define MIN_HEAP_H_

#define INIT_HEAP_CAPACITY	8

class MinHeap {
public:
	MinHeap(int capacity);
    MinHeap(int array[], int size);
	~MinHeap(); 
	
	bool IsEmpty();
    int  Top();
	void Pop();

	void InsertKey(int k);

private:

	void Reserve(int capacity);

	int Parent(int i) { return i / 2; }
	int LeftChild(int i) { return 2 * i; }
	int RightChild(int i) { return 2 * i + 1; }

	void Swap(int l, int r);
	void Sink(int i);
    void Swim(int i);

	int *arr_;

    // specify the max item count could be filled, the actual memory size should be 
    // capacity_ + 1 because we reserve the 0 item.
	int capacity_;

    // current item count
	int size_;
};

#endif//MIN_HEAP_H_
