#include "min_heap.h"
#include <iostream>
#include "indexed_priority_queue.h"


static void test_minheap() {

	int data[] = {12,3,4,92 ,29,  72, 115 ,181, 101, 131, 146,  94,   4,  50, 162,  48,  80,  43,  65,  39, 194,  26,  56};

    {
  	    MinHeap heap(10);

        std::cout << "========ori data========" << std::endl;
  	    for (int &i : data) {
            std::cout << i << ",";
	    	heap.InsertKey(i);
	    }
        std::cout << std::endl;

        std::cout << "========min heap sorted========" << std::endl;
	    while(!heap.IsEmpty()) {
            std::cout << heap.Top() << ",";
            heap.Pop();
	    }
        std::cout << std::endl;
    }

    {
	    MinHeap heap(data, sizeof(data)/sizeof(data[0]));

        std::cout << "========min heap from array========" << std::endl;
	    while(!heap.IsEmpty()) {
            std::cout << heap.Top() << ",";
            heap.Pop();
	    }
        std::cout << std::endl;
    }
}

static void test_indexed_pq() {
    IndexedPriorityQueue ipq(10);
    
    ipq.Insert(0, 2.1);
    ipq.Insert(1, 10.2);
    ipq.Insert(2, 3.2);
    ipq.Insert(3, 1.2);
    ipq.Insert(4, 9.2);
    ipq.Insert(5, 4.2);

    ipq.Change(3, 20);
    ipq.Change(1, 0.5);

    ipq.Delete(4);

    while (!ipq.Empty()) {
        std::cout << "(" << ipq.TopIndex() << "," << ipq.WeightOf(ipq.TopIndex()) << ")" << std::endl;
        ipq.Pop();
    }



}

int main(int argc, char *argv[]) {

//	test_minheap();
    test_indexed_pq();
	return 0;
}
