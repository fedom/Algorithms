#include "di_graph.h"
#include "di_reachability.h"
#include "di_paths.h"
#include "di_depth_first_order.h"
#include "di_topological.h"
#include "di_cc.h"
#include "di_cycle.h"
//#include "two_color.h"
#include "common/utils.h"
#include <iostream>

using namespace graph;

static void PrintPath(DiPaths &path, int v) {
    if (!path.HasPathTo(v)) {
        std::cout << path.S() << "->" << v << ":" << "no path" << std::endl;
    } else {
        std::cout << path.S() << "->" << v << ":" << string_join(int_vec_to_string_vec(path.PathTo(v)), ",") << std::endl;
    }
}

static void TestPath(DiGraph *g) {
    DiPaths path(g, 1);

    std::cout << "connected vertex count with " << path.S() << " is " << path.Count() << std::endl;

    PrintPath(path, 6);
    PrintPath(path, 7);
    PrintPath(path, 1);
}

/*

static void PrintCC(CC &cc, int i, int j) {
    std::cout << i << " & " << j << " connected: " << cc.Connected(i, j) << std::endl;
}

static void TestCC(Graph *g) {
    CC cc(g);

    std::cout << "connected component count: " << cc.Count() << std::endl;

    PrintCC(cc, 1, 7);
    PrintCC(cc, 4, 7);
    PrintCC(cc, 4, 6);
    PrintCC(cc, 0, 9);

}

static void TestTwoColor(Graph *g) {

    TwoColor two_color(g);

    std::cout << "graph is two color: " << two_color.IsTwoColor() << std::endl;
}

*/
static void TestCycle(DiGraph *g) {

    DiCycle cycle(g);

    std::cout << "graph has cycle : " << cycle.HasCycle() << std::endl;

    if (cycle.HasCycle()) {
        auto vec2 = cycle.GetDfsCycle();
        std::cout << "graph dfs cycle : " << string_join(int_vec_to_string_vec(vec2), "->") << std::endl;
    }

}


static void TestReachability(DiGraph *g) {

    DiReachability reach(g, 2);

    std::vector<int> unreachable = reach.GetUnreachableV();

    std::cout << "unreachable vertics from 2 are:";
    for (auto i : unreachable) {
        std::cout << i << ","; 
    }
    std::cout << std::endl;


    DiReachability reach2(g, std::vector<int>({4, 3, 8}));

    std::vector<int> unreachable2 = reach2.GetUnreachableV();
    std::cout << "unreachable vertics from {4, 3, 8} are:";
    for (auto i : unreachable2) {
        std::cout << i << ","; 
    }
    std::cout << std::endl;


}

static void TestDiGraph(DiGraph *g) {
    g->Reverse().Print("reverse.dot");
}

static void TestDepthFirstOrder(DiGraph *g) {

    DiDepthFirstOrder dfo(g);

    std::cout << "PreOrder" << string_join(int_vec_to_string_vec(dfo.PreOrder()), ",") << std::endl;
    std::cout << "PostOrder" << string_join(int_vec_to_string_vec(dfo.PostOrder()), ",") << std::endl;
    std::cout << "PostReverseOrder" << string_join(int_vec_to_string_vec(dfo.PostReverseOrder()), ",") << std::endl;
}


static void TestTopological(DiGraph *g) {

    DiTopological topo(g);

    std::cout << "IsDAG:" << topo.IsDAG() << std::endl;
    std::cout << "IsDAG2:" << topo.IsDAG2() << std::endl;

    if (topo.IsDAG()) {
        std::cout << "topo order is:" << string_join(int_vec_to_string_vec(topo.Order()), ",") << std::endl;
    } else {
        std::cout << "graph is not dag" << std::endl;
    }
}

#define _PrintCC(cc, v, w) \
    if (cc.IsStronglyConnected(v, w)) {\
        std::cout << v << " and " << w << " are strongly connected" << std::endl;\
    } else {\
        std::cout << v << " and " << w << " are separated" << std::endl;\
    }

#define _PrintComponents(cc) \
    {\
        auto r = cc.GetConnectedComponents();\
        for (const auto &i : r) {\
            std::cout << string_join(int_vec_to_string_vec(i), ",") << std::endl; \
        }\
    }

static void TestCC_1(DiGraph *g) {
    DiCC_1 cc(g);

    std::cout << cc.Count() << std::endl;
    _PrintCC(cc, 0, 7);
    _PrintCC(cc, 6, 7);
    _PrintCC(cc, 3, 4);
    _PrintComponents(cc);
}

static void TestCC_2(DiGraph *g) {
    DiCC_2 cc(g);

    std::cout << cc.Count() << std::endl;
    _PrintCC(cc, 0, 7);
    _PrintCC(cc, 6, 7);
    _PrintCC(cc, 3, 4);

    _PrintComponents(cc);
}

static void TestCC_3(DiGraph *g) {
    DiCC_3 cc(g);

    std::cout << cc.Count() << std::endl;
    _PrintCC(cc, 0, 7);
    _PrintCC(cc, 6, 7);
    _PrintCC(cc, 3, 4);

    _PrintComponents(cc);
}

int main(int argc, char *argv[]) {

    DiGraph graph;

    std::string graph_txt = "diG.txt";

    if (!graph.Load(graph_txt)) {
        std::cout << "load " << graph_txt << " failed\n";
        return 0;
    };

    graph.Print(graph_txt + ".dot");

    std::cout << "======TestDiGraph==========\n";
    TestDiGraph(&graph);
    std::cout << "======TestReachability==========\n";
    TestReachability(&graph);

    std::cout << "======TestPath============\n";
    TestPath(&graph);
    std::cout << "======TestCycle========\n";
    TestCycle(&graph);
    std::cout << "=========TestDepthFirstOrder=========\n";
    TestDepthFirstOrder(&graph);
    std::cout << "=========TestTopological=========\n";
    TestTopological(&graph);
    std::cout << "======TestCC_1======\n";
    TestCC_1(&graph);
    std::cout << "======TestCC_2======\n";
    TestCC_2(&graph);
    std::cout << "======TestCC_3======\n";
    TestCC_3(&graph);

    //TestCC(&graph);
    //std::cout << "==================\n";
    //TestTwoColor(&graph);
    //std::cout << "==================\n";

    return 0;
}
