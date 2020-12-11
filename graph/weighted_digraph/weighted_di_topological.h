#ifndef WEIGHTED_DI_TOPOLOGICAL_H_
#define WEIGHTED_DI_TOPOLOGICAL_H_
#include "weighted_digraph.h"
#include <vector>

namespace graph {

class WeightedDiTopological {
public:
    WeightedDiTopological(WeightedDigraph *g);

    bool IsDAG();
    std::vector<int> Order();

private:
    void InitUseDfs(WeightedDigraph *g);
    void InitWithIndegreeTable(WeightedDigraph *g);

    std::vector<int> order_;
    bool is_dag_;
};

}//namespace

#endif//WEIGHTED_DI_TOPOLOGICAL_H_
