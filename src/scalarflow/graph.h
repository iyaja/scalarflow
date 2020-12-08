
#pragma once

#include <list>
#include <unordered_map>
#include <utility>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <climits>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <set>
#include <sstream>
#include <vector>
#include <stack>
#include <queue>

#include "edge.h"
#include "random.h"

using std::cerr;
using std::cout;
using std::endl;
using std::vector;
using std::set;
using std::string;
using std::to_string;
using std::vector;
using std::pair;
using std::make_pair;
using std::unordered_map;
using std::stack;
using std::queue;


class Graph {
public:
    /**
     * Constructor to create an empty graph.
     */
     Graph();

    /**
     * Constructor to create an empty graph.
     * @param weighted - specifies whether the graph is a weighted graph or
     *  not
     */
     Graph(bool weighted);

     /**
     * Constructor to create an empty graph.
     * @param weighted - specifies whether the graph is a weighted graph or
     *  not
     * @param directed - specifies whether the graph is directed
     */
    Graph(bool weighted, bool directed);

    /**
     * Constructor to create an empty graph.
     * @param weighted - specifies whether the graph is a weighted graph or
     *  not
     * @param directed - specifies whether the graph is directed
     * @param seed - a random seed to create the graph with
     */
    Graph(bool weighted, bool directed, unsigned long seed);

    /**
     * Constructor to create a random, connected graph.
     * @param weighted - specifies whether the graph is a weighted graph or
     *  not
     * @param numVertices - the number of vertices the graph will have
     * @param seed - a random seed to create the graph with
     */
    Graph(bool weighted, int numVertices, unsigned long seed);

    /**
     * Gets all vertices in the graph.
     * @return a vector of all vertices in the graph
     */
    vector<Vertex> getVertices() const;

    // /**
    // * set vertex operator when the vertex is the vertex without out edges (end vertex)
    // * @param vertex - the vertex without out edges
    // * @param operand - the operator is going to be assigned to vertex
    // */
    // void setVertexOperator(Vertex vertex, string operand); 

    /**
     * Returns one vertex in the graph. This function can be used
     *  to find a random vertex with which to start a traversal.
     * @return a vertex from the graph
     */
    Vertex getStartingVertex() const;

    /**
     * Returns one random vertex in the graph. This function can be used
     *  to find a random vertex 
     * @return a random vertex from the graph
     */
    Vertex getRandomVertex();

    /**
     * Gets all adjacent vertices to the parameter vertex.
     * @param source - vertex to get neighbors from
     * @return a vector of vertices
     */
    vector<Vertex> getAdjacentVertices(Vertex source) const; 

    /**
     * Gets all adjacent edges which points to the parameter vertex.
     * @param source - vertex to get edges from
     * @return a vector of edges
     */
    vector<Edge> getAdjacentInEdges(Vertex source) const;

    /**
    * Gets all adjacent edges which comes from the parameter vertex.
    * @param source - vertex to get edges from
    * @return a vector of edges
    */
    vector<Edge> getAdjacentOutEdges(Vertex source) const;

    /**
    * Gets all adjacent vertices which the direction of edge between source and vertex is from source to vertex
    * @param source - vertex to get vertices from
    * @return a vector of vertices
    */
    vector<Vertex> getAdjacentOutVertices(Vertex source) const;

    /**
    * Gets all adjacent vertices which the direction of edge between source and vertex is from vertex to source
    * @param source - vertex to get vertices from
    * @return a vector of vertices
    */
    vector<Vertex> getAdjacentInVertices(Vertex source) const;

    /**
     * Gets an edge between two vertices.
     * @param source - one vertex the edge is connected to
     * @param destination - the other vertex the edge is connected to
     * @return - if exist, return the corresponding edge
     *         - if edge doesn't exist, return Edge()
     */
    Edge getEdge(Vertex source, Vertex destination) const;

    /**
     * Gets all the edges in the graph.
     * @return a vector of all the edges in the graph
     */
    vector<Edge> getEdges() const;

    /**
     * Checks if the given vertex exists.
     * @return - if Vertex exists, true
     *         - if Vertex doesn't exist, return false
     */
    bool vertexExists (Vertex v) const;

    /**
     * Inserts a new vertex into the graph and initializes its label as "".
     * @param v - the name for the vertex
     */
    void insertVertex(Vertex v);

    /**
     * Removes a given vertex from the graph.
     * @param v - the vertex to remove
     * @return - if v exists, return v
     *         - if not, return InvalidVertex;
     */
    Vertex removeVertex(Vertex v);

     /**
     * Gets the edge operand of the edge between vertices u and v.
     * @param source - one vertex the edge is connected to
     * @param destination - the other vertex the edge is connected to
     * @return - if edge exists, return edge operand
     *         - if edge doesn't exist, return InvalidOperand
     */
    double getEdgeOperand(Vertex source, Vertex destination) const;

    /**
     * Gets the edge label of the edge between vertices u and v.
     * @param source - one vertex the edge is connected to
     * @param destination - the other vertex the edge is connected to
     * @return - if edge exists, return edge label
     *         - if edge doesn't exist, return InvalidLabel
     */
    string getEdgeLabel(Vertex source, Vertex destination) const;

    /**
     * Gets the weight of the edge between two vertices.
     * @param source - one vertex the edge is connected to
     * @param destination - the other vertex the edge is connected to
     * @return - if edge exists, return edge wright
     *         - if doesn't, return InvalidWeight
     */
    int getEdgeWeight(Vertex source, Vertex destination) const;

     /**
     * Checks if edge exists between two vertices exists.
     * @return - if Edge exists, true
     *         - if Edge doesn't exist, return false
     */
    bool edgeExists(Vertex source, Vertex destination) const;

     /**
     * Inserts an edge between two vertices.
     * A boolean is returned for use with the random graph generation.
     * Hence, an error is not thrown when it fails to insert an edge.
     * @param source - one vertex the edge is connected to
     * @param destination - the other vertex the edge is connected to
     * @return whether inserting the edge was successful
     */
    bool insertEdge(Vertex source, Vertex destination);

    /**
     * Removes the edge between two vertices.
     * @param source - one vertex the edge is connected to
     * @param destination - the other vertex the edge is connected to
     * @return - if edge exists, remove it and return removed edge
     *         - if not, return InvalidEdge
     */
    Edge removeEdge(Vertex source, Vertex destination);

    /**
     * Sets the operand of the edge between two vertices.
     * @param source - one vertex the edge is connected to
     * @param destination - the other vertex the edge is connected to
     * @param weight - the operand to set to the edge
     * @return - if edge exists, set edge weight and return  edge with new operand
     *         - if not, return InvalidEdge
     */
    Edge setEdgeOperand(Vertex source, Vertex destination, double operand);

    /**
     * Sets the weight of the edge between two vertices.
     * @param source - one vertex the edge is connected to
     * @param destination - the other vertex the edge is connected to
     * @param weight - the weight to set to the edge
     * @return - if edge exists, set edge weight and return  edge with new weight
     *         - if not, return InvalidEdge
     */
    Edge setEdgeWeight(Vertex source, Vertex destination, int weight);

     /**
     * Sets the edge label of the edge between vertices u and v.
     * @param source - one vertex the edge is connected to
     * @param destination - the other vertex the edge is connected to
     * @return - if edge exists, set the label to the corresponding edge(if not directed, set the reverse one too), return edge with new label
     *         - if edge doesn't exist, return InvalidEdge
     */
    Edge setEdgeLabel(Vertex source, Vertex destination, string label);


    /**
    * compute the result of computation graph 
    * @param startingVertex - one vertex which computation starts from
    */
    void compute(Vertex startingVertex);


    /**
    * compute the out edges result according to in edges and operator of vertex
    * @param vertex - one vertex where computation happens
    */
    double computeOutEdges(Vertex vertex);

    /**
    * Breadth first search
    * @param visitedVertices - the vector stores the order of vertices which are visited
    * @param discoveredEdges - the vector stores the order of edges which are visited
    * @param crossEdges - the vector stores the order of edges which are cross edges
    */
    void dfs(vector<Vertex> &visitedVertices, vector<Edge> &discoveredEdges, vector<Edge> &crossEdges);


    const static Vertex InvalidVertex;
    const static Edge InvalidEdge;
    const static int InvalidWeight;
    const static string InvalidLabel;
    const static double InvalidOperand;

private:

    mutable unordered_map<Vertex, unordered_map<Vertex, Edge, pair_hash>, pair_hash> adjacency_list;


    bool weighted;
    bool directed;
    Random random;

    /**
     * Returns whether a given vertex exists in the graph.
     * @param v - the vertex to check
     * @param functionName - the name of the calling function to return
     *  in the event of an error
     */
    bool assertVertexExists(Vertex v, string functionName) const;

    /**
     * Returns whether thee edge exists in the graph.
     * @param source - one vertex
     * @param destination - another vertex
     * @param functionName - the name of the calling function to return
     *  in the event of an error
     */
    bool assertEdgeExists(Vertex source, Vertex destination, string functionName) const;


    /**
     * Prints a graph error and quits the program.
     * The program is exited with a segfault to provide a stack trace.
     * @param message - the error message that is printed
     */
    void error(string message) const;

    void computeInternal(stack<Vertex> &s);

     /**
    * Breadth first search
    * @param v - the vertex which is the starting vertex
    * @param visitedVertices - the vector stores the order of vertices which are visited
    * @param discoveredEdges - the vector stores the order of edges which are visited
    * @param crossEdges - the vector stores the order of edges which are cross edges
    * @param unexploredVertices - the set which stores unexploredVertices
    */
    void dfsInternal(Vertex vertex, vector<Vertex> &visitedVertices, vector<Edge> &discoveredEdges, vector<Edge> &crossEdges, set<Vertex> &unexploredVertices, set<Edge> &unexploredEdges);
  
};
