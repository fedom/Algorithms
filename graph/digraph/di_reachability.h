#ifndef DI_REACHABILITY_H 
#define DI_REACHABILITY_H 
#include "di_graph.h"
#include <vector>

namespace graph {

class DiReachability {

public:
    DiReachability(DiGraph *g, int start_v); 
    DiReachability(DiGraph *g, std::vector<int> start_v); 

    ~DiReachability() {}

    void Dfs(DiGraph *g, int v);
    std::vector<int> GetUnreachableV();

private:

    DiGraph *g_; 

    int start_v_;
    std::vector<bool> mark_;
};

}// namespace graph

#endif//DI_REACHABILITY_H 
