#include "cc.h"

namespace graph {

CC::CC(Graph *g) : count_(0) {
    mark_.resize(g->V());
    id_.resize(g->V());

    for (int i = 0; i < g->V(); i++) {
        if (!mark_[i]) {
            mark_[i] = true; 
            id_[i] = count_;
            Dfs(g, i);
            count_++;
        }
    }
}

void CC::Dfs(Graph *g, int s) {

    const auto &adj_v = g->Adjacent(s);

    for (int i : adj_v) {
        if (!mark_[i]) {
            mark_[i] = true;
            id_[i] = count_;
            Dfs(g, i);
        }
    }
}

bool CC::Connected(int v, int w) {
    return id_[v] == id_[w];
}

// return component count
int CC::Count() {
    return count_;
}

// return component id
int CC::Id(int v) {
    return id_[v];
}

}// namespace
