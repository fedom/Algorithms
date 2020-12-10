#ifndef DI_CYCLE_H
#define DI_CYCLE_H
#include "di_graph.h"
#include <vector>
#include <stack>


namespace graph {

// traverse the whole graph
class DiCycle {
public:
    DiCycle(DiGraph *g);
    bool HasCycle();
    std::vector<int> GetDfsCycle();

private:
    void Dfs(DiGraph *g, int v);

    std::vector<bool> mark_;
    std::vector<bool> on_stack_;
    std::vector<int> path_to_;

    std::vector<int> dfs_cycle_;

    bool has_cycle_;
    DiGraph *g_;
};

}// namespace


#endif//DI_CYCLE_H
