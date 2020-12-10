#ifndef GRAPH_H
#define GRAPH_H
#include <vector>

namespace graph {

class Graph {
public:
    Graph() {}

    bool Load(const char *file_name);
    int V();
    int E();
    std::vector<int> Adjacent(int v);
    void Print(const char* file_name);

private:
    void AddEdge(int v1, int v2);

    std::vector<std::vector<int> > graph_;
};

} //namespace graph
#endif//GRAPH_H
