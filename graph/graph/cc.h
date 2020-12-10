#ifndef CC_H
#define CC_H
#include "graph.h"
#include <vector>

namespace graph {

class CC {
public:
    CC(Graph *g);

    bool Connected(int v, int w);

    // return component count
    int Count();

    // return component id
    int Id(int v);

private:

    void Dfs(Graph *g, int s);

    std::vector<int> mark_;
    std::vector<int> id_;
    int count_;
};

}// namespace

#endif//CC_H
