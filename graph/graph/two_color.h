#ifndef OPERATION_H
#define OPERATION_H

#include "graph.h"
#include <vector>


namespace graph {

class TwoColor {
public:
    TwoColor(Graph *g);
    bool IsTwoColor();
        
private:

    void Dfs(Graph *g, int v);

    bool is_two_color_;
    std::vector<bool> mark_;
    std::vector<bool> color_;
};

}// namespace

#endif //TWO_COLOR_H
