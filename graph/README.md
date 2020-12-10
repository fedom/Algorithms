# Description

As there are too many graph operations and usually each operation may bound to a given start vertex. So
the design pattern for graph is different from trees. Operations can't be simply implemented as graph's
member function. So we separate the graph operation and the graph data. In the graph class we tracking the
basic data structure and the base operations only. Other complicated operations are implemented as standalone
class for each which will keep a reference to the actual graph instance. Common operations:

1. Path

Specify a start vertex s, the path operation is all operation that use it as start vertex. Eg.
path to v means path from s to v.

- constructor: Path(Graph *g, int s);
- operations: bool HasPathTo(int v);        // if exist a path from s to v
- operations: Vector<int> PathTo(int v);    // return the path from s to v

2. CC (Connect Component)

Specify a graph (no start vertex needed) and you can check the connection state of the graph or between two vertex.
Compare with the union-find algorithm the performance and application scenario.

- constructor: CC(Graph *g);
- operations: bool Connected(int v, int w); // if v and w connected
- operations: int count();        // return the number of the connected component
- operations: int id(int v);      // return the component id of the vertex v

3. Cycle

Check if a cycle exist in the graph. Algorithm use dfs to traverse the graph. During the process of looping v's adjacent
vertex w, if we meet a w's adjacent vertex x, and x is not v(not the same edge we just marked), that means there must exist
some other path to the vertex x. So there is a cycle in the graph.

- constructor: CC(Graph *g);
- operatoins: bool HasCycle();

4. TwoColor

[bipartite graph](https://zh.wikipedia.org/wiki/%E4%BA%8C%E5%88%86%E5%9B%BE)

- constructor: TwoColor(Graph *g);
- operatoins: bool IsTwoColor();

