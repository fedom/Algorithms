#include "di_reachability.h"
#include <iostream>

namespace graph {

DiReachability::DiReachability(DiGraph *g, int start_v) : g_(g) {
    mark_.resize(g->V());
    mark_[start_v] = true;
    Dfs(g, start_v);
}

DiReachability::DiReachability(DiGraph *g, std::vector<int> start_v) : g_(g) {
    mark_.resize(g->V());

    for (auto i : start_v) {
        if (!mark_[i]) {
            mark_[i] = true;
            Dfs(g, i);
        }
    }
}

void DiReachability::Dfs(DiGraph *g, int v) {
    for (int i : g->Adjacent(v)) {
        if (mark_[i])
            continue;

        mark_[i] = true;
        Dfs(g, i);
    }
}

std::vector<int> DiReachability::GetUnreachableV() {
    std::vector<int> vec;
    std::cout << "vertex count " << g_->V();

    for (int i = 0; i < g_->V(); i++) {
        if (!mark_[i]) {
            vec.push_back(i);
        }
    }

    return vec;
}


}//namespace
