#ifndef EDGE_WEIGHTED_DIGRAPH_H
#define EDGE_WEIGHTED_DIGRAPH_H
#include <vector>
#include <stdexcept>
#include <string>
#include <set>
#include <utility>

namespace graph {

class WeightedDiEdge {
public:
    WeightedDiEdge(int from, int to, float weight) : from_(from), to_(to), weight_(weight) {}

    int From() const {return from_;}

    int To() const {
        return to_;
    }

    float Weight() {return weight_;}

    bool operator<(const WeightedDiEdge &rhs) const { return weight_ < rhs.weight_; }
    bool operator>(const WeightedDiEdge &rhs) const { return weight_ > rhs.weight_; }

    std::string ToString() const {
        return std::to_string(from_) + "->" + std::to_string(to_) + " " + std::to_string(weight_);
    }

private:
    int from_;
    int to_;
    float weight_;
};

class WeightedDigraph {
public:
    WeightedDigraph();

    bool Load(const std::string &file_name);

    int V() { return graph_.size(); }
    int E() {return edge_count_;}

    std::vector<WeightedDiEdge> Adjacent(int v);
    std::vector<WeightedDiEdge> GetEdges();

    void Print(const std::string &file_name);
    void PrintMst(const std::string &file_name, const std::set<std::pair<int, int>> &bold_edges);

private:

    void AddEdge(WeightedDiEdge edge);

    std::vector<std::vector<WeightedDiEdge>> graph_;
    int edge_count_;
};

} // end of namespace

#endif //EDGE_WEIGHTED_DIGRAPH_H
