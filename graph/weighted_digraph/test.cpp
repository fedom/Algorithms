#include "weighted_digraph.h"
//#include "lazy_prim_mst.h"
//#include "prim_mst.h"
//#include "kruskal_mst.h"
#include "common/utils.h"
#include <iostream>
#include <set>
#include <utility>
#include "dijkstra_shortest_path.h"
#include "weighted_di_topological.h"
#include "acyclic_shortest_path.h"

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
//
static void TestDijkstraPath(WeightedDigraph &graph) {
    DijkstraShortestPath dijkstra_path(&graph, 0);

    int target = 5;

    if (dijkstra_path.HasPathTo(target)) {
    
        auto path = dijkstra_path.GetPath(target);

        std::string s = string_join(int_vec_to_string_vec(path), "->"); 

        std::cout << "shortest path from 0 to 5 is: ";
        std::cout << s << " (" << dijkstra_path.DistTo(target) << ")" << std::endl;
    } else {
    
        std::cout << "no path from 0 to 5" << std::endl;
    }
}

static void TestDiTopological(WeightedDigraph &graph) {
    WeightedDiTopological topo(&graph);

    if (topo.IsDAG()) {
        std::string s = string_join(int_vec_to_string_vec(topo.Order()), "->"); 
        std::cout << "is Dag, topo order is :" << s << std::endl;
    } else {
        std::cout << "graph has cycle" << std::endl;
    }
}

static void TestAcyclicShortestPath(WeightedDigraph &graph) {
    WeightedDiTopological topo(&graph);
    if (topo.IsDAG()) {
        AcyclicShortestPath acyclic_sp(&graph, 0);

        int target_v = 5;

        std::string s = string_join(int_vec_to_string_vec(acyclic_sp.GetPath(target_v)), "->"); 
        std::cout << "DAG shortest path is:" << s << " (" << acyclic_sp.DistTo(target_v) << ")" << std::endl;

    } else {
        std::cout << "graph has cycle" << std::endl;
    }
}

int main(int argc, char* argv[]) {

    if (argc < 2) {
        std::cout << argv[0] << " <graph.txt>" << std::endl;
        return 0;
    }

    WeightedDigraph graph;

    if (!graph.Load(argv[1])) {
        return 0;
    }

    std::cout << "====TestDigraph====" << std::endl;
    TestDigraph(graph);

    std::cout << "====TestDijkstraPath====" << std::endl;
    TestDijkstraPath(graph);

    std::cout << "====TestDiTopological====" << std::endl;
    TestDiTopological(graph);

    std::cout << "====TestAcyclicShortestPath====" << std::endl;
    TestAcyclicShortestPath(graph);

    return 0;
}
