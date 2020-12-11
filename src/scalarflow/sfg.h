#pragma once

#include "graph.h"
#include "edge.hpp"
#include "pair_hash.h"

#include <vector>
#include <map>

using namespace std;

class ScalarFlowGraph : public Graph
{
public:
    ScalarFlowGraph(bool weighted, bool directed) : Graph(weighted, directed) {};
    
    void setValue(Vertex v, float val) { values.insert({v, val}); }
    void registerBackward();

    void compile();
    map<Vertex, float> forward(Vertex);
    map<Vertex, float> forwardAll();
    map<Vertex, float> eval(Vertex);
    map<Vertex, float> evalAll();
    vector<Edge> DFS();

private:
    Graph backGraph = Graph(false, true);
    bool compiled = false;
    vector<Vertex> inodes;
    vector<Vertex> onodes;
    map<Vertex, float> values;

    void forward_(Vertex);
    float eval_(Vertex);
};