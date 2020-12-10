#ifndef CYCLE_H
#define CYCLE_H
#include "graph.h"
#include <vector>

namespace graph {

// traverse the whole graph
class Cycle {
public:
    Cycle(Graph *g);
    bool HasCycle();
    std::vector<int> GetSimpleCycle();
    std::vector<int> GetDfsCycle();

private:
    void Dfs(Graph *g, int v, int s_v);

    std::vector<bool> mark_;
    bool has_cycle_;

    int cycle_v_a_;
    int cycle_v_b_;

    std::vector<int> dfs_cycle_;
    int dfs_cycle_key_vertex_;

    Graph *g_;
};

}// namespace


#endif//CYCLE_H
