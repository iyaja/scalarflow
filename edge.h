/**
* @file edge.h
* Definition and implementation of an edge class
*/

#pragma once

#include <string>
#include <utility> // import pair

using std::string

typedef pair<string, string> Vertex; // first means label of vertex, second means operator stored in the vertex


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
        : source(u), dest(v), label(""), operand(0.0)
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
        : source(u), dest(v), label(lbl), operand(oper)
    { /* nothing */
    }

    /**
    * Default constructor.
    */
    Edge(): source(""), dest(""), label(""), operand(0.0)
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
    string getOperand() const 
    {
        return this->operand;
    }

    /** 
    * Sets operands 
    */
    string setOperand(double oper)
    {
        this->operand = oper;
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

    private:
        string label; /**< The edge label **/
        double operand; /** operands stored **/

};




