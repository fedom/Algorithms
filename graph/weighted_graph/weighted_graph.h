#ifndef EDGE_WEIGHTED_GRAPH_H
#define EDGE_WEIGHTED_GRAPH_H
#include <vector>
#include <stdexcept>
#include <string>
#include <set>
#include <utility>

namespace graph {

class WeightedEdge {
public:
    WeightedEdge(int v, int w, float weight) : v_(v), w_(w), weight_(weight) {}

    int Either() const {return v_;}

    int Other(int v) const {
        if (v == v_) return w_;
        if (v == w_) return v_;

        throw std::runtime_error("v is not either vertex of the edge.");
    }

    float Weight() {return weight_;}

    bool operator<(const WeightedEdge &rhs) const { return weight_ < rhs.weight_; }
    bool operator>(const WeightedEdge &rhs) const { return weight_ > rhs.weight_; }

    std::string ToString() const {
        return std::to_string(v_) + "->" + std::to_string(w_) + " " + std::to_string(weight_);
    }

private:
    int v_;
    int w_;
    float weight_;
};

class WeightedGraph {
public:
    WeightedGraph();

    bool Load(const std::string &file_name);

    int V() { return graph_.size(); }
    int E() {return edge_count_;}

    std::vector<WeightedEdge> Adjacent(int v);
    std::vector<WeightedEdge> GetEdges();

    void Print(const std::string &file_name);
    void PrintMst(const std::string &file_name, const std::set<std::pair<int, int>> &bold_edges);

private:

    void AddEdge(WeightedEdge edge);

    std::vector<std::vector<WeightedEdge>> graph_;
    int edge_count_;
};

} // end of namespace

#endif //EDGE_WEIGHTED_GRAPH_H
