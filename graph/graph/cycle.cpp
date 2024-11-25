#include "cycle.h"
#include <queue>

namespace graph {

Cycle::Cycle(Graph *g) : g_(g) 
                       , has_cycle_(false)
                       , dfs_cycle_key_vertex_(-1)
                       , cycle_v_a_(-1) 
                       , cycle_v_b_(-1) {
    mark_.resize(g->V());

    for (int i = 0; i < g->V() && !has_cycle_; i++) {
        if (!mark_[i]) {
            Dfs(g, i, i);
        }
    }
}
         
void Cycle::Dfs(Graph *g, int v, int s_v) {

    if (has_cycle_)
        return;

    mark_[v] = true;
    const auto &adj_v = g->Adjacent(v);

    for (int i : adj_v) {
        if (!mark_[i]) {
            Dfs(g, i, v); 
            // this code is executed while stack backtrace 
            if (HasCycle()) {
                // all the cycle vertics have been record. Current node already pass the stop vertex.
                if (dfs_cycle_key_vertex_ == -1) 
                    return;

                dfs_cycle_.push_back(v);
                if (v == dfs_cycle_key_vertex_) {
                    dfs_cycle_key_vertex_ = -1;
                }

                return;
            }
        } else {
            if (i != s_v) {
                cycle_v_a_ = i;
                cycle_v_b_ = v;
                has_cycle_ = true;
                dfs_cycle_key_vertex_ = i;

                dfs_cycle_.push_back(i);
                dfs_cycle_.push_back(v);

                break;
            }
        }
    } 
}

std::vector<int> Cycle::GetDfsCycle() {
    return dfs_cycle_;
}

bool Cycle::HasCycle() {
    return has_cycle_;
}

std::vector<int> Cycle::GetSimpleCycle() {
    std::vector<int> r;

    if (!has_cycle_)
        return r;

    std::fill(mark_.begin(), mark_.end(), false);

    std::queue<int> q;
    q.push(cycle_v_a_);
    mark_[cycle_v_a_] = true;

    std::vector<int> path;
    path.resize(g_->V());
    
    bool done = false;
    while (!q.empty()) {

        int v = q.front();
        q.pop();

        const auto &adjs = g_->Adjacent(v);

        for (int i : adjs) {

            if (mark_[i]) {
                continue;
            }

            // cut the direct edge to let it travel the long path so we can get it
            if (v == cycle_v_a_ && i == cycle_v_b_) {
                continue;
            }

            path[i] = v;
            mark_[i] = true;
            q.push(i);

            if (i == cycle_v_b_) {
                done = true;
                break;
            }
        }
        
        if (done) {
            break;
        }
    }

    r.push_back(cycle_v_b_);
    int v = path[cycle_v_b_];
    while (v != cycle_v_a_) {
        r.push_back(v); 
        v = path[v];
    }
    r.push_back(cycle_v_a_);

    return r;
}

}//namespace
