#include "two_color.h"

namespace graph {

TwoColor::TwoColor(Graph *g) : is_two_color_(true) {
    mark_.resize(g->V());
    color_.resize(g->V());

    for (int i = 0; i < g->V(); i++) {
        if (!mark_[i]) {
            mark_[i] = true;
            color_[i] = true;
            Dfs(g, i);
        }
    }
}

void TwoColor::Dfs(Graph *g, int v) {

    const auto &adj_v = g->Adjacent(v);

    for (int i : adj_v) {
        if (!mark_[i]) {
            mark_[i] = true;
            color_[i] = !color_[v];
            Dfs(g, i);
        } else {
            if (color_[i] == color_[v]) {
                is_two_color_ = false;
                break;
            }
        }
    }
}

bool TwoColor::IsTwoColor() {
    return is_two_color_;
}

} //namespace
