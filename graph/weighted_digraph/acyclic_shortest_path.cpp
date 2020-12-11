#include "acyclic_shortest_path.h"

#include <cassert>
#include <cfloat>
#include <stack>

namespace graph {

AcyclicShortestPath::AcyclicShortestPath(WeightedDigraph *g, int s) : s_(s) {
    path_.resize(g->V());
    dist_.resize(g->V());

    for (int i = 0; i < g->V(); i++) {
        dist_[i] = FLT_MAX;
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

        if (dist_[to] <= dist_[v] + e.Weight()) continue;

        dist_[to] = dist_[v] + e.Weight();
        path_[to] = e.From();
    }
}

bool AcyclicShortestPath::HasPathTo(int v) { return dist_[v] < FLT_MAX; }

float AcyclicShortestPath::DistTo(int v) { return dist_[v]; }

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

} //namespace graph
