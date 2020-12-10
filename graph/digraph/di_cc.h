#ifndef DI_CC_H
#define DI_CC_H
#include "di_graph.h"
#include <vector>
#include <set>

namespace graph {

/**
 * This is a Dicc alternative class for easily understand Kosaraju algorithm.
 * This class use a easy to understand way to implement the directed connected
 * components algorithm which is the core principle of the Kosaraju algorithm.
 *
 * */
class DiCC_1 {
public:
    DiCC_1(DiGraph *g);
    int Count();
    bool IsStronglyConnected(int v, int w);
    std::vector<std::vector<int>> GetConnectedComponents();

private:

    void Dfs1(DiGraph *g, int v, std::set<int> &group);
    void Dfs2(DiGraph *g, int v, const std::set<int> &group);

    DiGraph *g_;
    std::vector<int> mark_;
    std::vector<int> ids_;

    int id_;

    std::vector<std::set<int>> reverse_connected_;
};

class DiCC_2 {
public:
    DiCC_2(DiGraph *g);

    // return count of connected components
    int Count();
    bool IsStronglyConnected(int v, int w);
    std::vector<std::vector<int>> GetConnectedComponents();

private:
    void Dfs1(DiGraph *g, int v, std::vector<int> &group);
    void Dfs2(DiGraph *g, int v, const std::vector<int> &group);

    DiGraph *g_;

    std::vector<int> mark_;
    std::vector<int> ids_;

    std::vector<int> first_traverse_order_;
    int id_;
};

class DiCC_3 {
public:
    DiCC_3(DiGraph *g);

    // return count of connected components
    int Count();
    bool IsStronglyConnected(int v, int w);
    std::vector<std::vector<int>> GetConnectedComponents();

private:
    void Dfs(DiGraph *g, int v);

    DiGraph *g_;

    std::vector<int> mark_;
    std::vector<int> ids_;

    int id_;
};

}//namespace

#endif//DI_CC_H
