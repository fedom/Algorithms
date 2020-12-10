#include "dijkstra_shortest_path.h"

#include <stack>
#include <cfloat>
#include <cassert>

namespace graph {

DijkstraShortestPath::DijkstraShortestPath(WeightedDigraph *g, int s)
    : s_(s) {
    dist_.resize(g->V());
    path_.resize(g->V());

    pri_queue_.reset(new IndexedPriorityQueue(g->V()));

    for (int i = 0; i < dist_.size(); i++) {
        dist_[i] = FLT_MAX;
    }

    dist_[s] = 0;

    pri_queue_->Insert(s, 0);

    while (!pri_queue_->Empty()) {
        int v = pri_queue_->TopIndex();
        pri_queue_->Pop();

        Visit(g, v);
    }
}

void DijkstraShortestPath::Visit(WeightedDigraph *g, int v) {
    const auto &adj = g->Adjacent(v);

    for (auto &e : adj) {
        assert(v == e.From());

        int to = e.To();
        // update the vertex path info
        if (dist_[to] <= dist_[v] + e.Weight()) {
            continue;
        }

        path_[to] = v;
        dist_[to] = dist_[v] + e.Weight();

        if (pri_queue_->Contains(to)) {
            pri_queue_->Change(to, dist_[to]);
        } else {
            pri_queue_->Insert(to, dist_[to]);
        }
    }
}

bool DijkstraShortestPath::HasPathTo(int v) { return dist_[v] < FLT_MAX; }

float DijkstraShortestPath::DistTo(int v) { return dist_[v]; }

std::vector<int> DijkstraShortestPath::GetPath(int v) {
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

} // namespace graph
