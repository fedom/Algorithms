#include "di_paths.h"
#include <stack>
#include <queue>
#include <string>

namespace graph {

DiPaths::DiPaths(DiGraph *g, int s) : s_(s), count_(0) {
    mark_.resize(g->V());

    path_to_.resize(g->V());
    std::fill(path_to_.begin(), path_to_.end(), -1);

    path_to_[s] = s;

    //Dfs(g, s);
    Bfs(g, s);
}

bool DiPaths::HasPathTo(int v) {
    return path_to_[v] != -1;
}

void DiPaths::Bfs(DiGraph *g, int s) {
    std::queue<int> q;

    q.push(s);
    mark_[s] = true;
    count_++;

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        const auto &adj_v = g->Adjacent(v);

        for (int i : adj_v) {
            if (!mark_[i]) {
                mark_[i] = true;
                count_++;
                path_to_[i] = v;
                q.push(i);
            }
        }
    }
}

void DiPaths::Dfs(DiGraph *g, int s) {

    mark_[s] = true;
    count_++;

    const auto &adj_v = g->Adjacent(s);

    for (int i : adj_v) {
        if (!mark_[i]) {
            path_to_[i] = s;
            Dfs(g, i);
        }
    }
}

std::vector<int> DiPaths::PathTo(int v) {
    std::stack<int> path_to_v;
    std::vector<int> r;

    if (!HasPathTo(v)) {
        return r;
    }

    while (v != s_) {
        path_to_v.push(v);
        v = path_to_[v];
    }

    path_to_v.push(s_);
    while (!path_to_v.empty()) {
        r.push_back(path_to_v.top());
        path_to_v.pop();
    }

    return r;
}

int DiPaths::Count() {
    return count_;
}

} //namespace
