#ifndef KRUSKAL_MST_H_
#define KRUSKAL_MST_H_
#include <memory>
#include <queue>
#include <vector>

#include "weighted_graph.h"
#include "union_find/weighted_quick_union_uf.h"

namespace graph {

class KruskalMst {
public:
    KruskalMst(WeightedGraph *g);

    std::vector<WeightedEdge> GetEdges();
    float Weight();

private:
    void Visit(WeightedGraph *g, int v);

    WeightedGraph *g_;

    std::unique_ptr<WeightedQuickUnionUF> union_find_;

    std::vector<WeightedEdge> mst_;

    std::priority_queue<WeightedEdge, std::vector<WeightedEdge>, std::greater<WeightedEdge> > pri_queue_;
};

}  // namespace graph

#endif  // MST_IMPROVED_H_
