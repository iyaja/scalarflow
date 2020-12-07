#include "scalarflow/graph.h"

#include <iostream>

int main(int, char**) {
    Graph* g = new Graph();
    Vertex v1 = {"1", "+"};
    Vertex v2 = {"2", "+"};
    g->insertEdge(v1, v2);
    g->insertVertex(v1);
    g->insertVertex(v2);
    std::cout << g->edgeExists(v1, v2) << std::endl;
    std::cout << "Hello, world!\n";
}