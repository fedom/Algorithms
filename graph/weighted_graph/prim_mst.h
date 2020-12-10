#ifndef LAZY_PRIM_MST_IMPROVED_H_
#define LAZY_PRIM_MST_IMPROVED_H_
#include "weighted_graph.h"
#include "heap/indexed_priority_queue.h"
#include <queue>
#include <vector>
#include <memory>

namespace graph {

class PrimMst {
public:
    PrimMst(WeightedGraph *g);

    std::vector<WeightedEdge> GetEdges();
    float Weight();

private:
    void Visit(WeightedGraph *g, int v);

    WeightedGraph *g_;

    std::vector<int> mark_;

    std::vector<float> dist_to_;
    std::vector<int> edge_to_;

    std::unique_ptr<IndexedPriorityQueue> pri_queue_;
};

}//namespace graph


#endif//LAZY_PRIM_MST_IMPROVED_H_
