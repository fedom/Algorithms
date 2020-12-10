#include "di_cycle.h"
#include <queue>

namespace graph {

DiCycle::DiCycle(DiGraph *g) : g_(g) 
                       , has_cycle_(false) {
    mark_.resize(g->V());
    path_to_.resize(g->V());
    on_stack_.resize(g->V());
    
    for (int i = 0; i < g->V() && !has_cycle_; i++) {
        if (!mark_[i]) {
            // set the start vertex to itself, so we can get a valid path to start vertex
            path_to_[i] = i; 
            Dfs(g, i);
        }
    }
}
         
void DiCycle::Dfs(DiGraph *g, int v) {

    if (has_cycle_)
        return;

    mark_[v] = true;
    on_stack_[v] = true;
    const auto &adj_v = g->Adjacent(v);

    for (int i : adj_v) {
        if (HasCycle()) {
            break; 
        }

        if (!mark_[i]) {
            path_to_[i] = v;
            Dfs(g, i); 

        } else if (on_stack_[i]) {
            
            // found cycle
            std::stack<int> cycle_stack;

            cycle_stack.push(i);
            cycle_stack.push(v);

            int j = v;
            while (j != i) {
                cycle_stack.push(path_to_[j]); 
                j = path_to_[j];
            }

            while (!cycle_stack.empty()) {
                dfs_cycle_.push_back(cycle_stack.top());
                cycle_stack.pop();
            }

            has_cycle_ = true;
        }
    } 

    on_stack_[v] = false;
}

std::vector<int> DiCycle::GetDfsCycle() {
    return dfs_cycle_;
}

bool DiCycle::HasCycle() {
    return has_cycle_;
}

}//namespace
