#include "lazy_prim_mst.h"
#include <iostream>

namespace graph {

LazyPrimMst::LazyPrimMst(WeightedGraph *g) : g_(g), weight_(0) {
    mark_.resize(g->V());
    Visit(g, 0);
}

void LazyPrimMst::Visit(WeightedGraph *g, int v) {

    if (edges_.size() >= g_->V() - 1)
        return;

    mark_[v] = true;
    auto adj_edges = g->Adjacent(v);

    // add the candidates to priority queue
    for (auto &e : adj_edges) {
        pri_queue.push(e);
        std::cout << "push candidate " << e.ToString() << std::endl;
    }

    // select the next target edge
    while (!pri_queue.empty()) {
        auto e = pri_queue.top();
        pri_queue.pop();

        int i = e.Either();
        int j = e.Other(i);
        if (mark_[i] && mark_[j]) {
            continue;
        }

        edges_.push_back(e);
        weight_ += e.Weight();

        if (!mark_[i]) {
            Visit(g, i);
        } else {
            Visit(g, j);
        }
        break;
    }
}

std::vector<WeightedEdge> LazyPrimMst::GetEdges() {
    return edges_; 
}

float LazyPrimMst::Weight() {
    return weight_;
}

} //namespace graph
