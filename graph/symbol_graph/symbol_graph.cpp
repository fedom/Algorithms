#include "symbol_graph.h"
#include "common/utils.h"
#include <iostream>
#include <fstream>
#include <cassert>
#include <set>

namespace graph {
  

bool SymbolGraph::Load(const char *file_name) {

    const char *delims = " ";

    std::ifstream ifs(file_name, std::ios_base::in);
    if (!ifs) {
        std::cout << file_name << " open failed\n";
        return false;
    }

    int name_count = 0;

    std::string line;
    std::getline(ifs, line);

    while (std::getline(ifs, line)) {
        if (line.empty())
            continue;
        auto vec = string_split(line, delims);

        if (name_id_.find(vec[0]) == name_id_.end()) {
            name_id_[vec[0]] = name_count++;
            names_.push_back(vec[0]);
        }

        if (name_id_.find(vec[1]) == name_id_.end()) {
            name_id_[vec[1]] = name_count++;
            names_.push_back(vec[1]);
        }
    }

    graph_.resize(names_.size());

    std::cout << "vertex count : " << graph_.size() << std::endl;

    ifs.clear();
    ifs.seekg(0);

    while (std::getline(ifs, line)) {

        if (line.empty())
            continue;
        auto vec = string_split(line, delims);

        //std::cout << "add edge " << vec[0] << " " << vec[1] << std::endl;
        //std::cout << "add edge2 " << name_id_[vec[0]] << " " << name_id_[vec[1]] << std::endl;
        AddEdge(name_id_[vec[0]], name_id_[vec[1]]);
    }

    ifs.close();
    return true;
}


// for movie.txt
bool SymbolGraph::Load2(const char *file_name) {

    const char *delims = "/";

    std::ifstream ifs(file_name, std::ios_base::in);
    if (!ifs) {
        std::cout << file_name << " open failed\n";
        return false;
    }

    int name_count = 0;

    std::string line;
    std::getline(ifs, line);

    while (std::getline(ifs, line)) {
        if (line.empty())
            continue;
        auto vec = string_split(line, delims);

        for (int i = 0; i < vec.size(); i++) {
            if (name_id_.find(vec[i]) == name_id_.end()) {
                name_id_[vec[i]] = name_count++;
                names_.push_back(vec[i]);
            }
        }
    }

    graph_.resize(names_.size());

    std::cout << "vertex count : " << graph_.size() << std::endl;

    ifs.clear();
    ifs.seekg(0);

    while (std::getline(ifs, line)) {

        if (line.empty())
            continue;
        auto vec = string_split(line, delims);

        for (int i = 1; i < vec.size(); i++) {
            AddEdge(name_id_[vec[0]], name_id_[vec[i]]);
        }

        //std::cout << "add edge " << vec[0] << " " << vec[1] << std::endl;
        //std::cout << "add edge2 " << name_id_[vec[0]] << " " << name_id_[vec[1]] << std::endl;
    }

    ifs.close();
    return true;
}

int SymbolGraph::V() {
    return graph_.size();
}

int SymbolGraph::E() {
    int edge_count = 0;
    for (int i = 0; i < graph_.size(); i++) {
        edge_count += graph_[i].size();
    }
    return edge_count / 2;
}

void SymbolGraph::AddEdge(int v1, int v2) {
    graph_[v1].push_back(v2);
    graph_[v2].push_back(v1);
}

std::vector<int> SymbolGraph::Adjacent(int v) {
    return graph_[v];
}

std::vector<std::string> SymbolGraph::Adjacent(const std::string &v) {

    int id = Name2Id(v);
    assert(id < graph_.size());

    const auto &vec = graph_[id];
    std::vector<std::string> str_vec;

    for (auto i : vec) {
        str_vec.push_back(Id2Name(i)); 
    }

    return str_vec;
}

int SymbolGraph::Name2Id(const std::string &name) {
    if (name_id_.find(name) == name_id_.end()) {
        std::cout << name << std::endl;
        assert(false);
    }

    assert(name_id_.find(name) != name_id_.end());
    return name_id_[name];
}

std::string SymbolGraph::Id2Name(int id) {
    assert(id < names_.size());
    return names_[id];
}

void SymbolGraph::Print(const char *file_name) {

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
            ofs << names_[i] << "--" << names_[j] << std::endl;
        }
    }

    ofs << "}" << std::endl;
    ofs.close();
}

} //namespace
