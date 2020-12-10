#include "kruskal_mst.h"

namespace graph {

KruskalMst::KruskalMst(WeightedGraph *g) : g_(g) {

    union_find_.reset(new WeightedQuickUnionUF(g->V()));

    auto edges = g_->GetEdges();

    for (auto e : edges) {
        pri_queue_.push(e);
    }

    while (mst_.size() < g->V() && !pri_queue_.empty()) {
    
        const auto &e = pri_queue_.top();
        pri_queue_.pop();

        int i = e.Either();
        int j = e.Other(i);

        if (union_find_->IsConnected(i, j)) continue;
    
        union_find_->Connect(i, j);
        mst_.push_back(e);
    }
}

std::vector<WeightedEdge> KruskalMst::GetEdges() { return mst_; }

float KruskalMst::Weight() {

    float sum = 0;
    for (auto &e : mst_) {
        sum += e.Weight();
    }

    return sum;
}

}  // namespace graph
