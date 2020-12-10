#include "di_topological.h"
#include "di_cycle.h"
#include "di_depth_first_order.h"
#include <queue>

namespace graph {

DiTopological::DiTopological(DiGraph *g) : is_dag_(false) {
   //InitUseDfs(g);
   InitWithIndegreeTable(g);
}

bool DiTopological::IsDAG() {
    return is_dag_;
}

std::vector<int> DiTopological::Order() {
    return order_;
}

void DiTopological::InitUseDfs(DiGraph *g) {

    DiCycle dicycle(g);
    if (dicycle.HasCycle()) {
        is_dag_ = false;
        return;
    }

    is_dag_ = true;
    DiDepthFirstOrder dfo(g);
    order_ = dfo.PostReverseOrder();
}

void DiTopological::InitWithIndegreeTable(DiGraph *g) {

    std::vector<int> in_degree(g->V());

    for (int i = 0; i < g->V(); i++) {
        for (int j : g->Adjacent(i)) {
            in_degree[j]++;
        }
    }

    std::queue<int> q;

    for (int i = 0; i < in_degree.size(); i++) {
        if (!in_degree[i])
            q.push(i);
    }

    while(!q.empty()) {
    
        int v = q.front();
        q.pop();

        order_.push_back(v);

        for (int i : g->Adjacent(v)) {
            in_degree[i]--;
            if (!in_degree[i]) {
                q.push(i);
            }
        }
    }

    is_dag_ = true;
    for (int i : in_degree) {
        if (i != 0) {
            is_dag_ = false;
            break;
        }
    }
}

}
