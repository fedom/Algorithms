#ifndef PATH_H
#define PATH_H
#include "symbol_graph.h"
#include <vector>
#include <map>

namespace graph {

class Paths {
public:
    Paths(SymbolGraph *g, const std::string &s);
    int Count();
    bool HasPathTo(const std::string &v);
    std::vector<std::string> PathTo(const std::string &v);
    std::string StartVertex() {return str_s_;}

private:

    void Dfs(SymbolGraph *g, int s);
    void Bfs(SymbolGraph *g, int s);
    bool HasPathTo(int v);
    std::vector<int> PathTo(int v);

    SymbolGraph *g_;

    // Start vertex name of this path operation
    std::string str_s_;

    // Start vertex of this path operation
    int s_;

    // Helper array while traverse the graph
    std::vector<bool> mark_;

    // index is the edge end vertex, value is the edge start vertex, 
    // We construct the relation while travel the graph start from s_.
    // Edge is : path_to_[index] -> index
    std::vector<int> path_to_;

    int count_;

};

}//namespace


#endif//PATH_H
