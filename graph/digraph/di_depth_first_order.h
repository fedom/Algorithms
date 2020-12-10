#ifndef DI_DEPTH_FIRST_ORDER_H
#define DI_DEPTH_FIRST_ORDER_H
#include "di_graph.h"
#include <vector>
#include <stack>


namespace graph {

class DiDepthFirstOrder {
public:
    DiDepthFirstOrder(DiGraph *g);

    void Dfs(DiGraph *g, int v);

    std::vector<int> PreOrder();
    std::vector<int> PostOrder();
    std::vector<int> PostReverseOrder();

private:
    
    std::vector<int> mark_;
    std::vector<int> pre_order_;
    std::vector<int> post_order_;
    std::vector<int> post_reverse_order_;

    std::stack<int> post_reverse_order_stack_;

    DiGraph *g_;

};

}

#endif//DI_DEPTH_FIRST_ORDER_H
