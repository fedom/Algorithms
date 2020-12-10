#include "paths.h"
#include <stack>
#include <queue>



namespace graph {

Paths::Paths(SymbolGraph *g, const std::string &s) : g_(g), str_s_(s), count_(0) {
    mark_.resize(g->V());
    path_to_.resize(g->V());
    std::fill(path_to_.begin(), path_to_.end(), -1);

    s_ = g->Name2Id(s);
    //Dfs(g, s);
    Bfs(g, s_);
}

bool Paths::HasPathTo(const std::string &v) {
    return HasPathTo(g_->Name2Id(v));
}

bool Paths::HasPathTo(int v) {
    return path_to_[v] != -1;
}

void Paths::Bfs(SymbolGraph *g, int s) {
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

void Paths::Dfs(SymbolGraph *g, int s) {

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

std::vector<std::string> Paths::PathTo(const std::string &v) {

    std::vector<int> id_path = PathTo(g_->Name2Id(v));
    std::vector<std::string> name_path;

    for (int i = 0; i < id_path.size(); i++) {
        name_path.push_back(g_->Id2Name(id_path[i])); 
    }

    return name_path;
}

std::vector<int> Paths::PathTo(int v) {

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

    // convert the reversed int path to normal string path
    while (!path_to_v.empty()) {
        r.push_back(path_to_v.top());
        path_to_v.pop();
    }

    return r;
}


int Paths::Count() {
    return count_;
}

} //namespace
