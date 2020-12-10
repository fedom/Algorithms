#ifndef PATH_H
#define PATH_H
#include "graph.h"
#include <vector>
#include <map>

namespace graph {

class Paths {
public:
    Paths(Graph *g, int s);
    int Count();
    bool HasPathTo(int v);
    std::vector<int> PathTo(int v);
    std::string PathToString(int v);

private:

    void Dfs(Graph *g, int s);
    void Bfs(Graph *g, int s);

    int s_;
    std::vector<bool> mark_;
    std::vector<int> path_to_;

    int count_;
};

}//namespace


#endif//PATH_H
