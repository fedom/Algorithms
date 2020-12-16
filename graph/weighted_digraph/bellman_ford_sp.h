#ifndef BELLMAN_FORD_SP_H_
#define BELLMAN_FORD_SP_H_
#include "weighted_digraph.h"
#include <queue>
#include <vector>
#include <stack>

namespace graph {
class BellmanFordSp {
public:
    BellmanFordSp(WeightedDigraph *g, int s);

    float DistTo(int v);
    std::vector<int> GetPath(int v);

    bool HasNegativeCycle();
    std::vector<int> GetNegativeCycle();

private:
    void Relax(WeightedDigraph *g, int v);
    void FindNegativeCycle(WeightedDigraph *g, int v);

    std::vector<float> dist_;
    std::vector<int> predecessor_;

    std::queue<int> queue_;
    std::vector<int> negative_cycle_;

    int s_;
};

} // namespace
#endif  // BELLMAN_FORD_SP_H_
