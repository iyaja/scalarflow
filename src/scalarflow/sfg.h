#include "graph.h"
#include "edge.hpp"
#include "pair_hash.h"

class ScalarFlowGraph : Graph
{
public:
    float compute();
    float eval(Vertex v);
    void DFS();
};