#include "weighted_digraph.h"
#include "common/utils.h"
#include <set>
#include <iostream>
#include <fstream>
#include <utility> // for make_pair
#include <cassert>

namespace graph {

WeightedDigraph::WeightedDigraph() : edge_count_(0) {
}

bool WeightedDigraph::Load(const std::string &file_name) {

    std::ifstream ifs(file_name, std::ios_base::in);
    if (!ifs) {
        std::cout << file_name << " open failed\n";
        return false;
    }

    std::string line;

    std::getline(ifs, line);
    int v = std::stoi(line);
    graph_.resize(v);

    while (std::getline(ifs, line)) {
        if (line.empty())
            continue;

        auto str_vec = string_split(line, " ,");
        int i = std::stoi(str_vec[0]);
        int j = std::stoi(str_vec[1]);
        float weight = std::stof(str_vec[2]);

        std::cout << "add edge " << i << " " << j << " " << weight << std::endl;
        AddEdge(WeightedDiEdge(i, j, weight));
    }

    ifs.close();
    return true;
}

std::vector<WeightedDiEdge> WeightedDigraph::Adjacent(int v) {
    return graph_[v];
}

std::vector<WeightedDiEdge> WeightedDigraph::GetEdges() {
    std::vector<WeightedDiEdge> edges;

    for (auto &i : graph_) {
        edges.insert(edges.end(), i.begin(), i.end());
    }

    return edges;
}

void WeightedDigraph::AddEdge(WeightedDiEdge edge) {
    graph_[edge.From()].push_back(edge);
    edge_count_++;
}


void WeightedDigraph::Print(const std::string &file_name) {

    std::ofstream ofs(file_name, std::ios_base::out);
    if (!ofs) {
        std::cout << file_name << " write failed" << std::endl;
        return;
    }

    ofs << "digraph {" << std::endl;
    ofs << "node [shape=circle fixsize=TRUE]" << std::endl;

    for (int i = 0; i < graph_.size(); i++) {
        for (WeightedDiEdge &e : graph_[i]) {
            assert(i == e.From());
            ofs << i << "->" << e.To() << " [label=" << e.Weight() << "]" << std::endl;
        }
    }

    ofs << "}" << std::endl;
    ofs.close();
}

void WeightedDigraph::PrintMst(const std::string &file_name, const std::set<std::pair<int, int>> &bold_edges) {

    std::ofstream ofs(file_name, std::ios_base::out);
    if (!ofs) {
        std::cout << file_name << " write failed" << std::endl;
        return;
    }

    ofs << "digraph {" << std::endl;
    ofs << "node [shape=circle fixsize=TRUE]" << std::endl;


    for (int i = 0; i < graph_.size(); i++) {
        for (WeightedDiEdge &e : graph_[i]) {

            assert(i == e.From());
            // edge already processed
            bool is_bold = false;
            if (bold_edges.find(std::make_pair(e.From(),e.To())) != bold_edges.end()) {
                is_bold = true;
            }

            if (is_bold) {
                ofs << i << "->" << e.To() << " [label=" << e.Weight() << "color=red]" << std::endl;
            } else {
                ofs << i << "->" << e.To() << " [label=" << e.Weight() << "]" << std::endl;
            }
        }
    }

    ofs << "}" << std::endl;
    ofs.close();
}
}// end of namespace
