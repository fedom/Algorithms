#include "graph.h"
#include "common/utils.h"
#include <iostream>
#include <fstream>
#include <cassert>
#include <set>

namespace graph {

bool Graph::Load(const char *file_name) {

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

int Graph::V() {
    return graph_.size();
}

int Graph::E() {
    int edge_count = 0;
    for (int i = 0; i < graph_.size(); i++) {
        edge_count += graph_[i].size();
    }
    return edge_count / 2;
}

void Graph::AddEdge(int v1, int v2) {
    graph_[v1].push_back(v2);
    graph_[v2].push_back(v1);
}

std::vector<int> Graph::Adjacent(int v) {

    assert(v < graph_.size());
    return graph_[v];
}

void Graph::Print(const char *file_name) {

    std::ofstream ofs(file_name, std::ios_base::out);
    if (!ofs) {
        std::cout << file_name << " write failed" << std::endl;
        return;
    }

    ofs << "graph {" << std::endl;
    ofs << "node [shape=circle fixsize=TRUE]" << std::endl;


    std::set<std::pair<int, int> > edges;

    for (int i = 0; i < graph_.size(); i++) {
        for (int j : graph_[i]) {

            auto edge = std::make_pair(j, i);
            if (edges.find(edge) != edges.end()) 
                continue;

            edges.insert(std::make_pair(i, j));
            ofs << i << "--" << j << std::endl;
        }
    }

    ofs << "}" << std::endl;
    ofs.close();
}

} //namespace
