#include "acyclic_shortest_path.h"

#include <cassert>
#include <cfloat>
#include <stack>

namespace graph {

AcyclicShortestPath::AcyclicShortestPath(WeightedDigraph *g, int s, bool reverse/* = false*/) : s_(s), reverse_(reverse) {
    if (!reverse_) {
        init_dist_ = FLT_MAX;
    } else {
        init_dist_ = -FLT_MAX;
    }

    path_.resize(g->V());
    dist_.resize(g->V());

    for (int i = 0; i < g->V(); i++) {
        dist_[i] = init_dist_;
    }

    dist_[s] = 0;
    path_[s] = s;

    WeightedDiTopological topo(g);

    assert(topo.IsDAG());

    std::vector<int> topo_order = topo.Order();

    for (int i : topo_order) {
        Relax(g, i);
    }
}

void AcyclicShortestPath::Relax(WeightedDigraph *g, int v) {
    const auto &adj = g->Adjacent(v);

    for (const auto &e : adj) {
        int to = e.To();

        if (Less(dist_[v] + e.Weight(), dist_[to])) {
            dist_[to] = dist_[v] + e.Weight();
            path_[to] = e.From();
        }
    }
}

bool AcyclicShortestPath::HasPathTo(int v) { return dist_[v] != init_dist_; }

float AcyclicShortestPath::DistTo(int v) { return dist_[v]; }

int AcyclicShortestPath::Predecessor(int v) { return path_[v]; }

std::vector<int> AcyclicShortestPath::GetPath(int v) {
    std::stack<int> reverse_path;

    reverse_path.push(v);
    while (v != s_) {
        reverse_path.push(path_[v]);
        v = path_[v];
    }

    std::vector<int> path;

    while (!reverse_path.empty()) {
        path.push_back(reverse_path.top());
        reverse_path.pop();
    }
    return path;
}


bool AcyclicShortestPath::Less(float lhs, float rhs) {
    if (!reverse_)
        return lhs < rhs;
    return lhs > rhs;
}

} //namespace graph
