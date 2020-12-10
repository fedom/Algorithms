#ifndef SYMBOL_GRAPH_H
#define SYMBOL_GRAPH_H
#include <vector>
#include <string>
#include <map>

namespace graph {

class SymbolGraph {
public:
    SymbolGraph() {}

    // for symG.txt file format
    bool Load(const char *file_name);

    // for movie.txt file format
    bool Load2(const char *file_name);

    int V();
    int E();

    std::vector<std::string> Adjacent(const std::string &v);
    void Print(const char* file_name);

protected:
    std::vector<int> Adjacent(int v);
    int Name2Id(const std::string &name);
    std::string Id2Name(int id);
    void AddEdge(int v1, int v2);

    std::vector<std::vector<int> > graph_;
    std::map<std::string, int> name_id_;
    std::vector<std::string> names_;


    friend class Paths; 
};

} //namespace graph
#endif//SYMBOL_GRAPH_H
