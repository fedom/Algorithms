#include "weighted_digraph.h"
//#include "lazy_prim_mst.h"
//#include "prim_mst.h"
//#include "kruskal_mst.h"
#include <iostream>
#include <set>
#include <utility>

using namespace graph;

static void TestDigraph(WeightedDigraph &graph) {
    std::cout << "graph edge count :" << graph.E() << std::endl;
    graph.Print("tinyEWG.txt.dot");
}

//static void TestPrimMst(WeightedGraph &graph) {
//    LazyPrimMst mst(&graph);
//
//    std::cout << "mst weight is " << mst.Weight() << std::endl;
//
//    const auto &edges = mst.GetEdges();
//
//    std::set<std::pair<int,int>> bold_edges;
//
//    for (auto &e : edges) {
//        int i = e.Either();
//        int j = e.Other(i);
//        bold_edges.insert(std::make_pair(i, j));
//    }
//
//    graph.PrintMst("mst.dot", bold_edges);
//
//    std::cout << "mst is:" << std::endl;
//    for (auto &i : edges) {
//        std::cout << i.ToString() << std::endl;;
//    }
//    std::cout << "=====" << std::endl;
//}
//
//static void TestPrimMstImproved(WeightedGraph &graph) {
//    PrimMst mst(&graph);
//
//    std::cout << "mst weight is " << mst.Weight() << std::endl;
//
//    const auto &edges = mst.GetEdges();
//
//    std::set<std::pair<int,int>> bold_edges;
//
//    for (auto &e : edges) {
//        int i = e.Either();
//        int j = e.Other(i);
//        bold_edges.insert(std::make_pair(i, j));
//    }
//
//    graph.PrintMst("mst_improved.dot", bold_edges);
//
//    std::cout << "mst improved is:" << std::endl;
//    for (auto &i : edges) {
//        std::cout << i.ToString() << std::endl;;
//    }
//    std::cout << "=====" << std::endl;
//}
//
//static void TestKruskalMst(WeightedGraph &graph) {
//    KruskalMst mst(&graph);
//
//    std::cout << "kruskal mst weight is " << mst.Weight() << std::endl;
//
//    const auto &edges = mst.GetEdges();
//
//    std::set<std::pair<int,int>> bold_edges;
//
//    for (auto &e : edges) {
//        int i = e.Either();
//        int j = e.Other(i);
//        bold_edges.insert(std::make_pair(i, j));
//    }
//
//    graph.PrintMst("mst_kruskal.dot", bold_edges);
//
//    std::cout << "mst kruskal is:" << std::endl;
//
//    for (auto &i : edges) {
//        std::cout << i.ToString() << std::endl;;
//    }
//
//    std::cout << "=====" << std::endl;
//}

int main(int argc, char* argv[]) {
    WeightedDigraph graph;

    graph.Load("tinyEWG.txt");

    TestDigraph(graph);

    return 0;
}
