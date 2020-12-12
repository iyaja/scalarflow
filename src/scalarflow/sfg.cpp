#include "graph.h"
#include "edge.hpp"
#include "sfg.h"
#include "ops.hpp"

using namespace std;

void ScalarFlowGraph::compile()
{

    vector<Vertex> nodes = this->getVertices();

    for (Vertex node : nodes)
    {
        if (node.second == "const")
            inodes.push_back(node);
        if (node.second == "input")
            inodes.push_back(node);
        if (node.second == "output")
            onodes.push_back(node);
    }
    registerBackward();
    compiled = true;
}

void ScalarFlowGraph::registerBackward()
{

    for (Vertex v : this->getVertices())
        backGraph.insertVertex(v);

    for (Edge e : this->getEdges())
        backGraph.insertEdge(e.dest, e.source);
}

map<Vertex, float> ScalarFlowGraph::forwardAll()
{

    if (!compiled)
    {
        cerr << "Graph not initialized. Please call compile() before running a forward pass." << endl;
        exit(1);
    }

    for (Vertex v : inodes)
        forward_(v);

    return values;
}

map<Vertex, float> ScalarFlowGraph::forward(Vertex v)
{

    if (!compiled)
    {
        cerr << "Graph not initialized. Please call compile() before running a forward pass." << endl;
        exit(1);
    }

    forward_(v);
    return values;
}

void ScalarFlowGraph::forward_(Vertex curr)
{
    // cout << curr.first << "\t" << curr.second << endl;

    vector<float> params = {};
    for (Vertex v : backGraph.getAdjacent(curr))
    {
        if (values.count(v))
            params.push_back(values.at(v));
        else
            return;
    }

    while (params.size() < 2)
        params.push_back(0.0);

    function<float(float, float)> f = ops.at(curr.second);
    float val = f(params[0], params[1]);
    values.insert({curr, val});

    for (Vertex v : getAdjacent(curr))
        forward(v);
}

map<Vertex, float> ScalarFlowGraph::evalAll()
{
    if (!compiled)
    {
        cerr << "Graph not initialized. Please call compile() before running a forward pass." << endl;
        exit(1);
    }

    for (Vertex v : onodes)
        eval_(v);
    return values;
}

map<Vertex, float> ScalarFlowGraph::eval(Vertex v)
{
    eval_(v);
    return values;
}

float ScalarFlowGraph::eval_(Vertex curr)
{
    if (backGraph.getAdjacent(curr).empty() && values.count(curr))
        return values.at(curr);

    vector<float> params = {};
    for (Vertex v : backGraph.getAdjacent(curr))
        params.push_back(eval_(v));
    
    while (params.size() < 2)
        params.push_back(0.0);

    function<float(float, float)> f = ops.at(curr.second);
    float val = f(params[0], params[1]);
    values.insert({curr, val});

    return val;
}

vector<Edge> ScalarFlowGraph::traverse(Vertex source, string method)
{

    if (method == "DFS")
        DFS_(source);
    else if (method == "BFS")
        BFS_(source);
    else
    {
        cerr << "ERROR: invalid traversal maethod specified - " << method << endl;
        exit(1);
    }

    return trav;
}

vector<Edge> ScalarFlowGraph::traverseAll(string method)
{
    this->trav = {};

    for (Vertex inode: inodes)
        traverse(inode, method);

    return trav;
}

void ScalarFlowGraph::DFS_(Vertex curr)
{
    for (Vertex v: getAdjacent(curr))
    {
        trav.push_back(getEdge(curr, v));
        DFS_(v);
    }

}

void ScalarFlowGraph::BFS_(Vertex curr)
{
    for (Vertex v: getAdjacent(curr))
        trav.push_back(getEdge(curr, v));
    
    for (Vertex v: getAdjacent(curr))
        BFS_(v);

}