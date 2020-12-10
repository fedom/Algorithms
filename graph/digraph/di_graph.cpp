#include "di_graph.h"
#include "common/utils.h"
#include <iostream>
#include <fstream>
#include <cassert>
#include <set>

namespace graph {

bool DiGraph::Load(const std::string &file_name) {

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
        auto vec = string_vec_to_int_vec(string_split(line, " ,"));
        std::cout << "add edge " << vec[0] << " " << vec[1] << std::endl;
        AddEdge(vec[0], vec[1]);
    }

    ifs.close();
    return true;
}

int DiGraph::V() {
    return graph_.size();
}

int DiGraph::E() {
    int edge_count = 0;
    for (int i = 0; i < graph_.size(); i++) {
        edge_count += graph_[i].size();
    }
    return edge_count;
}

void DiGraph::AddEdge(int v1, int v2) {
    graph_[v1].push_back(v2);
}

std::vector<int> DiGraph::Adjacent(int v) {
    assert(v < graph_.size());
    return graph_[v];
}

DiGraph DiGraph::Reverse() {
    DiGraph g(V());
    for (int i = 0; i < graph_.size(); i++) {
        for (int j : graph_[i]) {
            g.AddEdge(j, i);
        }
    }
    return g;
}

void DiGraph::Print(const std::string &file_name) {

    std::ofstream ofs(file_name, std::ios_base::out);
    if (!ofs) {
        std::cout << file_name << " write failed" << std::endl;
        return;
    }

    ofs << "digraph {" << std::endl;
    ofs << "node [shape=circle fixsize=TRUE]" << std::endl;

    for (int i = 0; i < graph_.size(); i++) {
        for (int j : graph_[i]) {
            ofs << i << "->" << j << std::endl;
        }
    }

    ofs << "}" << std::endl;
    ofs.close();
}

} //namespace
