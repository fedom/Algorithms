#include "bellman_ford_sp.h"
#include <cfloat>


namespace graph {
BellmanFordSp::BellmanFordSp(WeightedDigraph *g, int s) : s_(s) {

    predecessor_.resize(g->V());
    dist_.resize(g->V(), FLT_MAX);

    dist_[s] = 0;
    predecessor_[s] = s;

    queue_.push(s);

    int round = 0;
    while (!queue_.empty()) {
        int v = queue_.front();
        queue_.pop();
    
        Relax(g, v);
        
        round++;
        if (round > g->V()) {
            FindNegativeCycle(g, v);    
            break;
        }
    }
}

void BellmanFordSp::Relax(WeightedDigraph *g, int v) {

    const auto &adjs = g->Adjacent(v);

    for (const auto &e : adjs) {
        int to = e.To();

        if (dist_[v] + e.Weight() < dist_[to]) {
            dist_[to] = dist_[v] + e.Weight();
            predecessor_[to] = v;

            queue_.push(to);
        }
    }
}

void BellmanFordSp::FindNegativeCycle(WeightedDigraph *g, int v) {

    std::stack<int> cycle_stack;

    std::vector<bool> on_path(g->V(), false);

    // find the start vertex on negative cycle 
    while (!on_path[v]) {
        on_path[v] = true;
        v = predecessor_[v];
    }

    int start = v;
    cycle_stack.push(v);

    v = predecessor_[v];
    while (v != start) {
        cycle_stack.push(v);
        v = predecessor_[v];
    }

    cycle_stack.push(v);

    while (!cycle_stack.empty()) {
        negative_cycle_.push_back(cycle_stack.top());
        cycle_stack.pop();
    }
}

bool BellmanFordSp::HasNegativeCycle() {
    return !negative_cycle_.empty();
}

std::vector<int> BellmanFordSp::GetNegativeCycle() {
    return negative_cycle_;
}

float BellmanFordSp::DistTo(int v) {
    return dist_[v];
}

std::vector<int> BellmanFordSp::GetPath(int v) {

    std::stack<int> reverse_path;

    reverse_path.push(v);
    while (v != s_) {
        reverse_path.push(predecessor_[v]);
        v = predecessor_[v];
    }

    std::vector<int> path;

    while (!reverse_path.empty()) {
        path.push_back(reverse_path.top());
        reverse_path.pop();
    }
    return path;
}
}//namespace
