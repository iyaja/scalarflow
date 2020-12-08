#include "graph.h"
#include "edge.h"

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

Graph::Graph(bool weighted, bool directed, unsigned long seed) : weighted(weighted),directed(directed),random(Random(seed))
{
}

vector<Vertex> Graph::getVertices() const
{
    vector<Vertex> ret;

    for(auto it = adjacency_list.begin(); it != adjacency_list.end(); it++)
    {
        ret.push_back(it->first);
    }

    return ret;
}

Vertex Graph::getStartingVertex() const
{
    return adjacency_list.begin()->first;
}

Vertex Graph::getRandomVertex()
{
    static int times;
    int randomInteger;
    for(int i = 0; i < times; i++) {
        randomInteger = random.nextInt();
    }
    times++;
    int size = adjacency_list.size();
    int index = randomInteger % size;

    int i = 0;
    auto it = adjacency_list.begin();
    for(; it != adjacency_list.end(); it++) {
        if(i == index) {
            break;
        }
        i++;
    }

    return it->first;
}

vector<Vertex> Graph::getAdjacentVertices(Vertex source) const
{
    auto lookup = adjacency_list.find(source);

    if(lookup == adjacency_list.end()) {
        return vector<Vertex>();
    }
    else {
        vector<Vertex> vertex_list;
        unordered_map<Vertex, Edge, pair_hash> & map = adjacency_list[source];
        for(auto it = map.begin(); it != map.end(); it++) {
            vertex_list.push_back(it->first);
        }
        return vertex_list;
    }
}

vector<Edge> Graph::getAdjacentInEdges(Vertex source) const
{

    vector<Edge> edge_list;

    // get adjacent vertices
    // 1. if adjacent vertices don't exist, return empty vector
    // 2. if adjacent vertices exists
    // 2.1 get unordered_map adjacent_list[adjacent_vertex]
    // 2.2 iterate through the entry,
    // 2.2.1 if find the source Vertex, add corresponding edge to edge_list
    
    vector<Vertex> adjacent_vertices = getAdjacentVertices(source);
    if(adjacent_vertices.empty()) {
        return vector<Edge>();
    } 
    else {
        for(Vertex vertex : adjacent_vertices) {
            Edge edge = adjacency_list[vertex][source];
            if(edge.getExisted() && edge.source == vertex && edge.dest == source) {
                edge_list.push_back(edge);
            }
        }
        return edge_list;
    }
}

vector<Edge> Graph::getAdjacentOutEdges(Vertex source) const
{
    vector<Edge> edge_list;

    vector<Vertex> adjacent_vertices = getAdjacentVertices(source);
    if(adjacent_vertices.empty()) {
       return vector<Edge>();
    }
    else {
         for(Vertex vertex : adjacent_vertices) {
            Edge edge = adjacency_list[source][vertex];
            if(edge.getExisted() && edge.source == source && edge.dest == vertex) {
                edge_list.push_back(edge);
            }
        }
        return edge_list;
    }
}

vector<Vertex> Graph::getAdjacentOutVertices(Vertex source) const
{
    vector<Vertex> vertices_list;
    vector<Edge> adjacent_out_edges = getAdjacentOutEdges(source);
    for(Edge edge : adjacent_out_edges) {
        vertices_list.push_back(edge.dest);
    }
    return vertices_list;
}

vector<Vertex> Graph::getAdjacentInVertices(Vertex source) const
{
    vector<Vertex> vertices_list;
    vector<Edge> adjacent_in_edges = getAdjacentInEdges(source);
    for(Edge edge : adjacent_in_edges) {
        vertices_list.push_back(edge.source);
    }
    return vertices_list;
}

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
    // if(!directed)
    // {
        if(adjacency_list.find(destination)== adjacency_list.end())
        {
            adjacency_list[destination] = unordered_map<Vertex, Edge, pair_hash>();
        }
        Edge edge(destination, source);
        edge.setExisted(false);
        adjacency_list[destination][source] = edge;
    // }

    return true;
}

Edge Graph::removeEdge(Vertex source, Vertex destination)
{
    if(assertEdgeExists(source, destination, __func__) == false)
        return InvalidEdge;
    Edge e = adjacency_list[source][destination];
    adjacency_list[source].erase(destination);
    // if undirected, remove the corresponding edge
    if(!directed || (directed && !adjacency_list[destination][source].getExisted()))
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
    new_edge.setAssigned(true);
    adjacency_list[source][destination] = new_edge;

    if(!directed) {
        Edge new_edge_reverse(destination, source, e.getLabel(), operand);
        adjacency_list[destination][source] = new_edge_reverse;
    }
    return new_edge;
}

Edge Graph::setEdgeLabel(Vertex source, Vertex destination, string label)
{
    if (assertEdgeExists(source, destination, __func__) == false)
        return InvalidEdge;
    Edge e = adjacency_list[source][destination];
    Edge new_edge(source, destination, e.getWeight(), label);
    adjacency_list[source][destination] = new_edge;

    if(!directed)
    {
        Edge new_edge_reverse(destination,source, e.getWeight(), label);
        adjacency_list[destination][source] = new_edge_reverse;
    }
    return new_edge;
}

void Graph::compute(Vertex startingVertex)
{
    stack<Vertex> s;
    s.push(startingVertex);
    while(!s.empty()) {
        computeInternal(s);
    }
}

void Graph::computeInternal(stack<Vertex> &s) {
    // top and pop the vertex
    Vertex top = s.top();
    s.pop();

    vector<Vertex> adjacent_out_vertices = getAdjacentOutVertices(top);
    
    // push all adjacent out vertices into stack
    for( Vertex vertex : adjacent_out_vertices) {
        s.push(vertex);
    }

    vector<Edge> adjacent_in_edges = getAdjacentInEdges(top);

    bool isAllInEdgesAssigned = true;
    vector<Vertex> unassigned_in_vertices;
    for( Edge edge : adjacent_in_edges) {
        if(!edge.getAssigned()) {
            Vertex vertex = edge.source;
            unassigned_in_vertices.push_back(vertex);
            if(isAllInEdgesAssigned) {
               isAllInEdgesAssigned = false; 
            }
        }
    }

    if(isAllInEdgesAssigned) {
        vector<Edge> adjacent_out_edges = getAdjacentOutEdges(top);
        if(top.second == "start") {
            for(Edge edge : adjacent_out_edges) {
                // assign out edges with result
                setEdgeOperand(edge.source, edge.dest, edge.getOperand());
            }
        }
        else {
            double result = computeOutEdges(top);

            for(Edge edge : adjacent_out_edges) {
                // assign out edges with result
                setEdgeOperand(edge.source, edge.dest, result);
            }
        }

    } else { // some in edges are not assigned operand before
        s.push(top);
        for(auto unassigned_in_vertex : unassigned_in_vertices) {
            s.push(unassigned_in_vertex);
        }
    }
}

double Graph::computeOutEdges(Vertex vertex) {
    string operat = vertex.second;
    vector<Edge> adjacent_in_edges = getAdjacentInEdges(vertex);

    if(operat == "+") {
        return adjacent_in_edges[0].getOperand() + adjacent_in_edges[1].getOperand();
    }
    if(operat == "*") {
        return adjacent_in_edges[0].getOperand() * adjacent_in_edges[1].getOperand();
    }
    return double();
}

void Graph::dfs(vector<Vertex> &visitedVertices, vector<Edge> &discoveredEdges, vector<Edge> &crossEdges) {
    vector<Vertex> vertices = this->getVertices();
    vector<Edge> edges = this->getEdges();
    set<Vertex> unexploredVertices; 
    set<Edge> unexploredEdges;
    for(auto v: vertices) {
        unexploredVertices.insert(v);
    }
    for(auto edge: edges) {
        unexploredEdges.insert(edge);
    }
    for(auto v: vertices) {
        dfsInternal(v, visitedVertices, discoveredEdges, crossEdges, unexploredVertices, unexploredEdges);
    }
}

void Graph::dfsInternal(Vertex vertex, vector<Vertex> &visitedVertices, vector<Edge> &discoveredEdges, vector<Edge> &crossEdges, set<Vertex> &unexploredVertices, set<Edge> &unexploredEdges) {
    set<Vertex> exploredVertices;
    set<Edge> exploredEdges;
    queue<Vertex> q;
    q.push(vertex);
    exploredVertices.insert(vertex);
    unexploredVertices.erase(vertex);
    while(!q.empty()) {
        Vertex frontVertex = q.front();
        vector<Vertex> adjacentVertices = this->getAdjacentVertices(frontVertex);
        for(auto adjacentVertex: adjacentVertices) {
            // get edge from graph and add to set exploredEdges
            Edge exploredEdge = this->getEdge(frontVertex, adjacentVertex);
            
            if(unexploredVertices.find(adjacentVertex) != unexploredVertices.end()) {
                // label edge as explored
                exploredEdges.insert(exploredEdge);
                unexploredEdges.erase(exploredEdge);

                // maintain the order of edges which are visited
                discoveredEdges.push_back(exploredEdge);

                // label vertex as explored
                exploredVertices.insert(adjacentVertex);
                unexploredVertices.erase(adjacentVertex);

                // maintain the order of vertices which are visited
                visitedVertices.push_back(adjacentVertex);

                q.push(adjacentVertex);
            }
            else if(unexploredEdges.find(exploredEdge) != unexploredEdges.end()) {
                unexploredEdges.erase(exploredEdge);
                crossEdges.push_back(exploredEdge);
            }
        }
    }
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
