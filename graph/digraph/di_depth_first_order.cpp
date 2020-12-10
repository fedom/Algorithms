#include "di_depth_first_order.h"

namespace graph {

DiDepthFirstOrder::DiDepthFirstOrder(DiGraph *g) : g_(g) {

    mark_.resize(g->V());

    for (int i = 0; i < g->V(); i++) {
        if (!mark_[i]) {
            Dfs(g, i); 
        }
    }

    while(!post_reverse_order_stack_.empty()) {
        post_reverse_order_.push_back(post_reverse_order_stack_.top());
        post_reverse_order_stack_.pop();
    }
}

void DiDepthFirstOrder::Dfs(DiGraph *g, int v) {

    mark_[v] = true;


    pre_order_.push_back(v);
    
    const auto &adj = g->Adjacent(v);

    for (int i : adj) {
        if (!mark_[i]) {
            Dfs(g, i);
        }
    }

    post_order_.push_back(v);
    post_reverse_order_stack_.push(v);
}

std::vector<int> DiDepthFirstOrder::PreOrder() {
    return pre_order_;
}

std::vector<int> DiDepthFirstOrder::PostOrder() {
    return post_order_;

}

std::vector<int> DiDepthFirstOrder::PostReverseOrder() {
    return post_reverse_order_;
}

}// namespace
