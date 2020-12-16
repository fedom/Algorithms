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

    float Weight() const {return weight_;}

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

    // construct a graph from common format input
	/***
	---format desc:---
	vertex_count
	start_v1 end_v1	weight
	start_v2 end_v2	weight
	...
	---real content---
	8   
	4 5 0.35
	4 7 0.37
	5 7 0.28
	0 7 0.16
	1 5 0.32
	0 4 0.38
	2 3 0.17
	1 7 0.19
	0 2 0.26
	1 2 0.36
	1 3 0.29
	****/
    bool Load(const std::string &file_name);

    // construct a graph from cpm format input
	/***
	https://algs4.cs.princeton.edu/44sp/jobsPC.txt
	---format desc:---
	vertex_count
	task0_dur task0_must_complete_before_list...
	task1_dur task1_must_complete_before_list...
	...
	---real content---
	10
	41.0  3  1 7 9
	51.0  1  2
	50.0  0
	36.0  0
	38.0  0
	45.0  0
	21.0  2  3 8
	32.0  2  3 8
	32.0  1  2
	29.0  2  4 6
	****/
    bool LoadCpm(const std::string &file_name);

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
