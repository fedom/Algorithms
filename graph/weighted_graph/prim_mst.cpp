#include <iostream>
#include <cfloat>

#include "prim_mst.h"


namespace graph {

PrimMst::PrimMst(WeightedGraph *g)
    : g_(g) {
    mark_.resize(g->V());

    dist_to_.resize(g->V());
    for (auto &i : dist_to_) {
        i = FLT_MAX; 
    }

    dist_to_[0] = 0;
    edge_to_.resize(g->V());

    pri_queue_.reset(new IndexedPriorityQueue(g->V()));
    pri_queue_->Insert(0, 0);
    
    while (!pri_queue_->Empty()) {
        int v = pri_queue_->TopIndex();
        pri_queue_->Pop();

        Visit(g, v);
    }
}

void PrimMst::Visit(WeightedGraph *g, int v) {

    mark_[v] = true;
    auto adj_edges = g->Adjacent(v);

    // add the candidates to priority queue
    for (auto &e : adj_edges) {
        int j = e.Other(v);
        if (mark_[j]) {
            continue;
        }
        if (e.Weight() >= dist_to_[j]) {
            continue;
        }

        dist_to_[j] = e.Weight();
        edge_to_[j] = v;

        if (pri_queue_->Contains(j)) {
            pri_queue_->Change(j, e.Weight());
        } else {
            pri_queue_->Insert(j, e.Weight());
        }
    }
}

std::vector<WeightedEdge> PrimMst::GetEdges() {
    std::vector<WeightedEdge> tmp;

    for (int i = 0; i < edge_to_.size(); i++) {
        if (i != edge_to_[i]) {
            tmp.push_back(WeightedEdge(i, edge_to_[i], dist_to_[i]));
        }
    }
    return tmp;
}

float PrimMst::Weight() { 
    float weight = 0;
    
    for (auto i : dist_to_) {
        weight += i; 
    }
}

}  // namespace graph
