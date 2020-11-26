/**
* @file edge.h
* Definition and implementation of an edge class
*/

#pragma once

#include <string>
#include <utility> // import pair

using std::string;
using std::pair;

typedef std::pair<string, string> Vertex; // first means label of vertex, second means operator stored in the vertex

/**
* provide hash function for pair<string, string>,
* in this way, pair<string, string> or Vertex could be 
* used as key of unordered_map
*/
struct pair_hash {
    template <class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2> &pair) const
    {
        return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
    }
};

/**
* Represents an edge in a graph; used by graph class. 
* originally created by Sean Massung. But it's altered now.
* 
* @author Shellyn, Adam
*/
class Edge {
    public:
       Vertex source; /**< The source of the edge **/
       Vertex dest; /**< The destination of the edge **/

    /**
    * Parameter constructor for graphs.
    * @param u - one vertex the edge is connected to
    * @param v - the other vertex it is connected to
    */
    Edge(Vertex u, Vertex v)
        : source(u), dest(v), label(""), operand(0.0), weight(-1)
    { /* nothing */
    }
    
    /**
    * Parameter constructor for graphs.
    * @param u - one vertex the edge is connected to
    * @param v - the other vertex it is connected to
    * @param lbl - the edge label
    * @param oper - the operand stored in edge
    */
    Edge(Vertex u, Vertex v, string lbl, double oper)
        : source(u), dest(v), label(lbl), operand(oper), weight(-1)
    { /* nothing */
    }

    /**
    * Parameter constructor for graphs.
    * @param u - one vertex the edge is connected to
    * @param v - the other vertex it is connected to
    * @param lbl - the edge label
    * @param oper - the operand stored in edge
    * @param wei - the weight of the edge
    */
    Edge(Vertex u, Vertex v, int wei, string lbl, double oper)
        : source(u), dest(v), label(lbl), operand(oper), weight(wei)
    { /* nothing */
    }

    /**
    * Default constructor.
    */
    Edge(): source(pair<string,string>("","")), dest(pair<string,string>("","")), label(""), operand(0.0), weight(-1)
    { /* nothing */
    }

    /**
    * Gets edge label.
    */
    string getLabel() const 
    {
        return this->label;
    }

    /**
    * Gets operands stored in edge
    */
    double getOperand() const 
    {
        return operand;
    }

    /** 
    * Sets operands 
    */
    void setOperand(double oper)
    {
        operand = oper;
    }


    /**
     * Gets edge weight.
     */
    int getWeight() const
    {
        return this->weight;
    }


    /**
    * Compares two edges' source and dest.
    * @param other - the edge to compare with
    */
    bool operator==(Edge& other) const
    {
        if (this->source != other.source) {
            return false;
        }
        if (this->dest != other.dest) {
            return false;
        }
        return true;
    }

    /**
     * Compares two Edges.
     * operator< is defined so Edges can be sorted with std::sort.
     * @param other - the edge to compare with
     * @return whether the current edge is less than the parameter
     */
    bool operator<(const Edge& other) const
    {
        return weight < other.weight;
    }


    private:
        string label; /**< The edge label **/
        double operand; /** operands stored **/
        int weight; /**< The edge weight (if in a weighed graph) **/

};




