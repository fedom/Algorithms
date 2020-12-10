#include "weighted_graph.h"
#include "common/utils.h"
#include <set>
#include <iostream>
#include <fstream>
#include <utility> // for make_pair

namespace graph {

WeightedGraph::WeightedGraph() : edge_count_(0) {
}

bool WeightedGraph::Load(const std::string &file_name) {

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
        AddEdge(WeightedEdge(i, j, weight));
    }

    ifs.close();
    return true;
}

std::vector<WeightedEdge> WeightedGraph::Adjacent(int v) {
    return graph_[v];
}

std::vector<WeightedEdge> WeightedGraph::GetEdges() {
    std::vector<WeightedEdge> edges;

    for (auto &i : graph_) {
        edges.insert(edges.end(), i.begin(), i.end());
    }

    return edges;
}

void WeightedGraph::AddEdge(WeightedEdge edge) {
    int v = edge.Either();
    int w = edge.Other(v);

    graph_[v].push_back(edge);
    graph_[w].push_back(edge);

    edge_count_++;
}


void WeightedGraph::Print(const std::string &file_name) {

    std::ofstream ofs(file_name, std::ios_base::out);
    if (!ofs) {
        std::cout << file_name << " write failed" << std::endl;
        return;
    }

    ofs << "graph {" << std::endl;
    ofs << "node [shape=circle fixsize=TRUE]" << std::endl;

    std::set<std::pair<int,int>> edges;

    for (int i = 0; i < graph_.size(); i++) {
        for (WeightedEdge &e : graph_[i]) {

            // edge already processed
            if (edges.find(std::make_pair(i, e.Other(i))) != edges.end()) 
                continue;

            edges.insert(std::make_pair(e.Other(i), i));
            ofs << i << "--" << e.Other(i) << " [label=" << e.Weight() << "]" << std::endl;
        }
    }

    ofs << "}" << std::endl;
    ofs.close();
}

void WeightedGraph::PrintMst(const std::string &file_name, const std::set<std::pair<int, int>> &bold_edges) {

    std::ofstream ofs(file_name, std::ios_base::out);
    if (!ofs) {
        std::cout << file_name << " write failed" << std::endl;
        return;
    }

    ofs << "graph {" << std::endl;
    ofs << "node [shape=circle fixsize=TRUE]" << std::endl;

    std::set<std::pair<int,int>> edges;

    for (int i = 0; i < graph_.size(); i++) {
        for (WeightedEdge &e : graph_[i]) {

            // edge already processed
            int j = e.Other(i);
            if (edges.find(std::make_pair(i, j)) != edges.end()) 
                continue;

            bool is_bold = false;
            if (bold_edges.find(std::make_pair(i,j)) != bold_edges.end() 
                || bold_edges.find(std::make_pair(j,i)) != bold_edges.end()) {
                is_bold = true;
            }

            edges.insert(std::make_pair(j, i));
            if (is_bold) {
                ofs << i << "--" << e.Other(i) << " [label=" << e.Weight() << "color=red]" << std::endl;
            } else {
                ofs << i << "--" << e.Other(i) << " [label=" << e.Weight() << "]" << std::endl;
            }
        }
    }

    ofs << "}" << std::endl;
    ofs.close();
}
}// end of namespace
