#include "symbol_graph.h"
#include "paths.h"
#include "common/utils.h"
//#include "cc.h"
//#include "operations.h"
#include <iostream>

using namespace graph;

static void PrintPath(Paths &path, const std::string &v) {
    if (!path.HasPathTo(v)) {
        std::cout << path.StartVertex() << " -> " << v << " : " << "no path" << std::endl;
    } else {
        auto vec = path.PathTo(v);

        std::cout << path.StartVertex() << " -> " << v << " degree : " << (vec.size() - 1) / 2 << std::endl;
        std::cout << path.StartVertex() << " -> " << v << " : " << string_join(vec, " -> ") << std::endl;
    }
}

static void TestMoviePath(SymbolGraph *g) {
    Paths path(g, "Bassett, William");

    //std::cout << "connected vertex JFK is: " << path.Count() << std::endl;

    PrintPath(path, "McMillan, Ronnie");
    PrintPath(path, "Rambaruth, Sanjay");
    PrintPath(path, "Abesamis, Americus");
}

static void TestPath(SymbolGraph *g) {
    Paths path(g, "JFK");

    std::cout << "connected vertex JFK is: " << path.Count() << std::endl;

    PrintPath(path, "LAS");
    PrintPath(path, "MCO");
    PrintPath(path, "DEN");
}
//
//static void PrintCC(CC &cc, int i, int j) {
//    std::cout << i << " & " << j << " connected: " << cc.Connected(i, j) << std::endl;
//}
//
//static void TestCC(Graph *g) {
//    CC cc(g);
//
//    std::cout << "connected component count: " << cc.Count() << std::endl;
//
//    PrintCC(cc, 1, 7);
//    PrintCC(cc, 4, 7);
//    PrintCC(cc, 4, 6);
//    PrintCC(cc, 0, 9);
//
//}
//
//static void TestTwoColor(Graph *g) {
//
//    TwoColor two_color(g);
//
//    std::cout << "graph is two color: " << two_color.IsTwoColor() << std::endl;
//}

int main(int argc, char *argv[]) {

    SymbolGraph graph;
    if (!graph.Load2("movie.txt")) {
        std::cout << "movie.txt open failed\n";
        return 0;
    }
    
    graph.Print("symG.dot");

//    TestPath(&graph);
    TestMoviePath(&graph);
//    TestCC(&graph);
//    TestTwoColor(&graph);

    return 0;
}
