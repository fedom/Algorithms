#ifndef DI_PATH_H
#define DI_PATH_H
#include "di_graph.h"
#include <vector>
#include <map>

namespace graph {

class DiPaths {
public:
    DiPaths(DiGraph *g, int s);

    int Count();
    bool HasPathTo(int v);
    std::vector<int> PathTo(int v);

    int S() {return s_;}

private:

    void Dfs(DiGraph *g, int s);
    void Bfs(DiGraph *g, int s);

    int s_;
    std::vector<bool> mark_;
    std::vector<int> path_to_;

    // connected vertics count from s_
    int count_;
};

}//namespace


#endif//DI_PATH_H
