#include "graph.h"
#include "paths.h"
#include "cc.h"
#include "cycle.h"
#include "two_color.h"
#include "common/utils.h"
#include <iostream>

using namespace graph;

static void PrintPath(Paths &path, int v) {
    if (!path.HasPathTo(v)) {
        std::cout << "0->" << v << ":" << "no path" << std::endl;
    } else {
        std::cout << "0->" << v << ":" << path.PathToString(v) << std::endl;
    }
}

static void TestPath(Graph *g) {
    Paths path(g, 0);

    std::cout << "connected vertex count with 0 is " << path.Count() << std::endl;
    PrintPath(path, 0);
    PrintPath(path, 6);
    PrintPath(path, 7);
    PrintPath(path, 1);
}

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

static void TestCycle(Graph *g) {

    Cycle cycle(g);

    std::cout << "graph has cycle : " << cycle.HasCycle() << std::endl;

    if (cycle.HasCycle()) {
        auto vec = cycle.GetSimpleCycle();
        std::cout << "graph simple cycle : " << string_join(int_vec_to_string_vec(vec), "->") << std::endl;

        auto vec2 = cycle.GetDfsCycle();
        std::cout << "graph dfs cycle : " << string_join(int_vec_to_string_vec(vec2), "->") << std::endl;
    }

}

int main(int argc, char *argv[]) {

    Graph graph;

    if (!graph.Load("baseG.txt")) {
        std::cout << "load baseG.txt failed\n";
        return 0;
    };

    graph.Print("baseG.dot");

    std::cout << "==================\n";
    TestPath(&graph);
    std::cout << "==================\n";
    TestCC(&graph);
    std::cout << "==================\n";
    TestTwoColor(&graph);
    std::cout << "==================\n";
    TestCycle(&graph);

    return 0;
}
