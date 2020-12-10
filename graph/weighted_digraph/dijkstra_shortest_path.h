#ifndef DIJKSTRA_SHORTEST_PATH_H_
#define DIJKSTRA_SHORTEST_PATH_H_
#include "heap/indexed_priority_queue.h"
#include "weighted_digraph.h"
#include <memory>
#include <vector>

namespace graph {

class DijkstraShortestPath {
public:
    DijkstraShortestPath(WeightedDigraph *g, int s);

    bool HasPathTo(int v);
    float DistTo(int v);
    std::vector<int> GetPath(int v);

private:
    void Visit(WeightedDigraph *g, int v);

    std::vector<float> dist_;
    std::vector<float> path_;

    int s_;
    std::unique_ptr<IndexedPriorityQueue> pri_queue_;
};

} //namespace graph

#endif  // DIJKSTRA_SHORTEST_PATH_H_

