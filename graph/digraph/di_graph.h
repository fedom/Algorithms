#ifndef DI_GRAPH_H
#define DI_GRAPH_H
#include <vector>
#include <string>

namespace graph {

class DiGraph {
public:
    DiGraph() {}
    DiGraph(int v_count) {graph_.resize(v_count);}

    bool Load(const std::string &file_name);
    int V();
    int E();
    std::vector<int> Adjacent(int v);
    DiGraph Reverse();
    
    void Print(const std::string &file_name);

private:
    void AddEdge(int v1, int v2);

    std::vector<std::vector<int> > graph_;
};

} //namespace graph
#endif//DI_GRAPH_H
