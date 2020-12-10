#include "di_cc.h"
#include "di_depth_first_order.h"
#include "common/utils.h"
#include <iostream>
#include <stack>

namespace graph {

DiCC_3::DiCC_3(DiGraph *g) : g_(g), id_(0) {
    mark_.resize(g->V());
    ids_.resize(g->V());

    DiDepthFirstOrder dfs_order(g);

    const std::vector<int> &vertics_post_reverse_order = dfs_order.PostReverseOrder();

    DiGraph r_g = g->Reverse();

    for (int i : vertics_post_reverse_order) {
        if (!mark_[i]) {
            Dfs(&r_g, i);
            id_++;
        }
    }
}


void DiCC_3::Dfs(DiGraph *g, int v) {

    mark_[v] = true;
    ids_[v] = id_;

    const auto &adj = g->Adjacent(v);

    for (int i : adj) {
        if (!mark_[i]) {
            Dfs(g, i);
        }
    }
}

int DiCC_3::Count() {
    return id_;
}

bool DiCC_3::IsStronglyConnected(int v, int w) {
    return ids_[v] == ids_[w];
}

std::vector<std::vector<int>> DiCC_3::GetConnectedComponents() {

    std::vector<std::vector<int>> r;
    r.resize(Count());

    for (int i = 0; i < g_->V(); i++) {
        r[ids_[i]].push_back(i);
    }

    return r;
}

DiCC_2::DiCC_2(DiGraph *g) : g_(g), id_(0) {

    mark_.resize(g->V());
    ids_.resize(g->V());

    std::stack<std::vector<int>> group_stack;

    for (int i = 0; i < g->V(); i++) {
        
        if (!mark_[i]) {
            std::vector<int> group;
            Dfs1(g, i, group);
            std::cout << string_join(int_vec_to_string_vec(group), ",") << std::endl;
            group_stack.push(group);
        }
    }

    DiGraph r_g = g->Reverse();
    std::fill(mark_.begin(), mark_.end(), false);

    while (!group_stack.empty()) {
        auto &group = group_stack.top();

        for (int i : group) {
            if (!mark_[i]) {
                Dfs2(&r_g, i, group);
                id_++;
            }
        }

        group_stack.pop();
    }
}

void DiCC_2::Dfs1(DiGraph *g, int v, std::vector<int> &group) {

    mark_[v] = true;
    group.push_back(v);

    const auto &adj = g->Adjacent(v);

    for (int i : adj) {
        if (!mark_[i]) {
            Dfs1(g, i, group);
        }
    }
}

void DiCC_2::Dfs2(DiGraph *g, int v, const std::vector<int> &group) {

    mark_[v] = true;
    ids_[v] = id_;

    const auto &adj = g->Adjacent(v);

    for (int i : adj) {
        if (!mark_[i]) {
            Dfs2(g, i, group);
        }
    }
}

int DiCC_2::Count() {
    return id_;
}

bool DiCC_2::IsStronglyConnected(int v, int w) {
    return ids_[v] == ids_[w];
}

std::vector<std::vector<int>> DiCC_2::GetConnectedComponents() {

    std::vector<std::vector<int>> r;
    r.resize(Count());

    for (int i = 0; i < g_->V(); i++) {
        r[ids_[i]].push_back(i);
    }

    return r;
}

DiCC_1::DiCC_1(DiGraph *g) : g_(g), id_(0) {

    mark_.resize(g->V());
    ids_.resize(g->V());

    DiGraph reverse_g = g->Reverse();

    // divide the 
    for (int i = 0; i < reverse_g.V(); i++) {
        if (!mark_[i]) {
            std::set<int> group;
            Dfs1(&reverse_g, i, group);
            reverse_connected_.push_back(group);
        }
    }

    fill(mark_.begin(), mark_.end(), 0);

    for (int i = 0; i < reverse_connected_.size(); i++) {
        const std::set<int> &group = reverse_connected_[i];

        for (auto j : group) {
            if (!mark_[j]) {
                Dfs2(g, j, group);
                id_++;
            }
        }
    }
}

int DiCC_1::Count() {
    return id_;
}

bool DiCC_1::IsStronglyConnected(int v, int w) {
    return ids_[v] == ids_[w];
}

void DiCC_1::Dfs1(DiGraph *g, int v, std::set<int> &group) {

    mark_[v] = true;
    group.insert(v);

    const auto &adj = g->Adjacent(v);

    for (auto i : adj) {
        if (!mark_[i]) {
            Dfs1(g, i, group); 
        }
    }
}

void DiCC_1::Dfs2(DiGraph *g, int v, const std::set<int> &group) {

    mark_[v] = true;
    ids_[v] = id_;

    const auto &adj = g->Adjacent(v);

    for (auto i : adj) {
        if (!mark_[i] && group.find(i) != group.end()) {
            Dfs2(g, i, group);
        }
    }
}

std::vector<std::vector<int>> DiCC_1::GetConnectedComponents() {

    std::vector<std::vector<int>> r;
    r.resize(Count());

    for (int i = 0; i < g_->V(); i++) {
        r[ids_[i]].push_back(i);
    }

    return r;
}
}//namespace
