#ifndef DI_TOPOLOGICAL_H
#define DI_TOPOLOGICAL_H
#include "di_graph.h"
#include <vector>

namespace graph {

class DiTopological {
public:
    DiTopological(DiGraph *g);

    bool IsDAG();
    
    // This is a another way to check acyclic
    bool IsDAG2();

    std::vector<int> Order();

private:
    void InitUseDfs(DiGraph *g);
    void InitWithIndegreeTable(DiGraph *g);

    std::vector<int> order_;
    bool is_dag_;
    DiGraph *g_;

};

}//namespace

#endif//DI_TOPOLOGICAL_H
