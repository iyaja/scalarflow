#include "graph.h"

// const Vertex Graph::InvalidVertex = "_CS225INVALIDVERTEX";
const Vertex Graph::InvalidVertex = pair<string,string>("_CS225INVALIDVERTEX", "");
const int Graph::InvalidWeight = INT_MIN;
const double Graph::InvalidOperand = INT_MIN;
const string Graph:: InvalidLabel = "_CS225INVALIDLABEL";
const Edge Graph::InvalidEdge = Edge(Graph::InvalidVertex, Graph::InvalidVertex, Graph::InvalidWeight, Graph::InvalidLabel, Graph::InvalidOperand);

Graph::Graph() : weighted(false), directed(false), random(Random(0))
{
}

Graph::Graph(bool weighted) : weighted(weighted), directed(false), random(Random(0))
{
}

Graph::Graph(bool weighted, bool directed) : weighted(weighted),directed(directed),random(Random(0))
{
}


// Graph::Graph(bool weighted, int numVertices, unsigned long seed)
//     :weighted(weighted),
//       directed(false),
//      random(Random(seed)) 
// {
//     if(numVertices < 2) {
//         error("numVertices too low");
//         exit(1);
//     }

//     vector<Vertex> vertices;
//     for(int i = 0; i < numVertices; i++) {
//         insertVertex(to_string(i));
//         vertices.
//     }
// }

Edge Graph::getEdge(Vertex source, Vertex destination) const 
{
    if(assertEdgeExists(source, destination, __func__) == false)
        return Edge();
    
    Edge ret = adjacency_list[source][destination];
    return ret;
}

vector<Edge> Graph::getEdges() const
{
    if(adjacency_list.empty()) {
        return vector<Edge>();
    }

    vector<Edge> ret;
    set<pair<Vertex,Vertex>> seen;

    for(auto it = adjacency_list.begin(); it != adjacency_list.end(); it++) {
        Vertex source = it->first;
        for(auto its = adjacency_list[source].begin(); its != adjacency_list[source].end(); ++its) {
            Vertex destination = its->first;
            if(seen.find(make_pair(source, destination)) == seen.end()) {
                // this pair is never added to seen
                ret.push_back(its->second);
                seen.insert(make_pair(source, destination));
                if(!directed) {
                    seen.insert(make_pair(source, destination));
                }
            }
        }
    }

    return ret;
}

bool Graph::vertexExists(Vertex v) const
{
    return assertVertexExists(v, "");
}

void Graph::insertVertex(Vertex v) 
{
    // will overwrite if old stuff was there
    removeVertex(v);
    // make it empty again
    adjacency_list[v] = unordered_map<Vertex, Edge, pair_hash>();
}

Vertex Graph::removeVertex(Vertex v) 
{
    if(adjacency_list.find(v) != adjacency_list.end()) {
        if(!directed){
            for (auto it = adjacency_list[v].begin(); it != adjacency_list[v].end(); it++)
            {
                Vertex u = it->first;
                adjacency_list[u].erase(v); 
            }
            adjacency_list.erase(v);
            return v;
        }
        
        adjacency_list.erase(v);
        for(auto it2 = adjacency_list.begin(); it2 != adjacency_list.end(); it2++) {
            Vertex u = it2->first;
            if(it2->second.find(v) != it2->second.end()) {
                it2->second.erase(v);
            }
        }
        return v;
    }

    return InvalidVertex;
}

double Graph::getEdgeOperand(Vertex source, Vertex destination) const 
{
    if(assertEdgeExists(source, destination, __func__) == false)
        return InvalidOperand;
    return adjacency_list[source][destination].getOperand();
}

string Graph::getEdgeLabel(Vertex source, Vertex destination) const
{
    if(assertEdgeExists(source, destination, __func__) == false)
        return InvalidLabel;
    return adjacency_list[source][destination].getLabel();
}

int Graph::getEdgeWeight(Vertex source, Vertex destination) const
{
    if (!weighted)
        error("can't get edge weights on non-weighted graphs!");

    if(assertEdgeExists(source, destination, __func__) == false)
        return InvalidWeight;
    return adjacency_list[source][destination].getWeight();
}

bool Graph::edgeExists(Vertex source, Vertex destination) const
{
    return assertEdgeExists(source, destination, "");
}

bool Graph::insertEdge(Vertex source, Vertex destination) 
{
    if(adjacency_list.find(source)!= adjacency_list.end() 
    && adjacency_list[source].find(destination)!= adjacency_list[source].end())
    {
        //edge already exit
        return false;
    }

    if(adjacency_list.find(source)==adjacency_list.end())
    {
        adjacency_list[source] = unordered_map<Vertex, Edge, pair_hash>();
    }

     //source vertex exists
    adjacency_list[source][destination] = Edge(source, destination);
    if(!directed)
    {
        if(adjacency_list.find(destination)== adjacency_list.end())
        {
            adjacency_list[destination] = unordered_map<Vertex, Edge, pair_hash>();
        }
        adjacency_list[destination][source] = Edge(source, destination);
    }

    return true;
}

Edge Graph::removeEdge(Vertex source, Vertex destination)
{
    if(assertEdgeExists(source, destination, __func__) == false)
        return InvalidEdge;
    Edge e = adjacency_list[source][destination];
    adjacency_list[source].erase(destination);
    // if undirected, remove the corresponding edge
    if(!directed)
    {
        adjacency_list[destination].erase(source);
    }
    return e;
}

Edge Graph::setEdgeOperand(Vertex source, Vertex destination, double operand) 
{
   if(assertEdgeExists(source, destination, __func__) == false)
        return InvalidEdge;
    Edge e = adjacency_list[source][destination];
    Edge new_edge(source, destination, e.getLabel(), operand);
    adjacency_list[source][destination] = new_edge;

    if(!directed) {
        Edge new_edge_reverse(destination, source, e.getLabel(), operand);
        adjacency_list[destination][source] = new_edge_reverse;
    }
    return new_edge;
}

bool Graph::assertVertexExists(Vertex v, string functionName) const
{
    if (adjacency_list.find(v) == adjacency_list.end())
    {
        if (functionName != "")
            error(functionName + " called on nonexistent vertices");
        return false;
    }
    return true;
}

bool Graph::assertEdgeExists(Vertex source, Vertex destination, string functionName) const
{
    if(assertVertexExists(source,functionName) == false)
        return false;
    if(adjacency_list[source].find(destination)== adjacency_list[source].end())
    {
        if (functionName != "")
            error(functionName + " called on nonexistent edge " + source.first + " -> " + destination.first);
        return false;
    }

    if(!directed)
    {
        if (assertVertexExists(destination,functionName) == false)
            return false;
        if(adjacency_list[destination].find(source)== adjacency_list[destination].end())
        {
            if (functionName != "")
                error(functionName + " called on nonexistent edge " + destination.first + " -> " + source.first);
            return false;
        }
    }
    return true;
}

/**
 * Prints a graph error and quits the program.
 * The program is exited with a segfault to provide a stack trace.
 * @param message - the error message that is printed
 */
void Graph::error(string message) const
{
    cerr << "\033[1;31m[Graph Error]\033[0m " + message << endl;
}