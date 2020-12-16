#ifndef ACYCLIC_SHORTEST_PATH_H_
#define ACYCLIC_SHORTEST_PATH_H_
#include "weighted_di_topological.h"
#include "weighted_digraph.h"

namespace graph {

class AcyclicShortestPath {
public:
    AcyclicShortestPath(WeightedDigraph *g, int s, bool reverse = false);

    bool HasPathTo(int v);
    float DistTo(int v);
    int Predecessor(int v);
    std::vector<int> GetPath(int v);

private:

    void Relax(WeightedDigraph *g, int v);
    bool Less(float lhs, float rhs);
   
    std::vector<float> dist_;
    std::vector<int> path_;
    int s_;

    float init_dist_;
    bool reverse_;
};

} //namespace graph

#endif  // ACYCLIC_SHORTEST_PATH_H_
