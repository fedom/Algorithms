#include "weighted_di_topological.h"
#include <queue>

namespace graph {

WeightedDiTopological::WeightedDiTopological(WeightedDigraph *g) : is_dag_(false) {
   //InitUseDfs(g);
   InitWithIndegreeTable(g);
}

bool WeightedDiTopological::IsDAG() {
    return is_dag_;
}

std::vector<int> WeightedDiTopological::Order() {
    return order_;
}

//void WeightedDiTopological::InitUseDfs(WeightedDigraph *g) {
//
//    DiCycle dicycle(g);
//    if (dicycle.HasCycle()) {
//        is_dag_ = false;
//        return;
//    }
//
//    is_dag_ = true;
//    DiDepthFirstOrder dfo(g);
//    order_ = dfo.PostReverseOrder();
//}

void WeightedDiTopological::InitWithIndegreeTable(WeightedDigraph *g) {

    std::vector<int> in_degree(g->V());

    for (int i = 0; i < g->V(); i++) {
        for (auto &e : g->Adjacent(i)) {
            in_degree[e.To()]++;
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

        for (auto &e : g->Adjacent(v)) {
            in_degree[e.To()]--;
            if (!in_degree[e.To()]) {
                q.push(e.To());
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
