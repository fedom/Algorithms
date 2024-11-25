#ifndef LAZY_PRIM_MST_H_
#define LAZY_PRIM_MST_H_
#include "weighted_graph.h"
#include <queue>
#include <vector>

namespace graph {

class LazyPrimMst {
public:
    LazyPrimMst(WeightedGraph *g);

    std::vector<WeightedEdge> GetEdges();
    float Weight();

private:
    void Visit(WeightedGraph *g, int v);

    float weight_;
    WeightedGraph *g_;

    std::vector<int> mark_;
    std::vector<WeightedEdge> edges_;

    std::priority_queue<WeightedEdge, std::vector<WeightedEdge>, std::greater<WeightedEdge>> pri_queue_;
};

}//namespace graph


#endif//LAZY_PRIM_MST_H_
