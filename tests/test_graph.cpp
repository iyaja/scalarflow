#include "catch.hpp"

#include <iostream>
#include <scalarflow/graph.h>
#include <scalarflow/sfg.h>

template <typename T>
bool ifSourceInList(vector<T> list, T source) {
    bool found = false;
    for(T elem:list) {
        if(elem == source) {
            found = true;
        }
    }
    return found;
}

template <typename T>
set<T> convertVectorToSet(vector<T> list) {
    set<T> res;
    for(T element: list) {
        res.insert(element);
    }
    return res;
}

TEST_CASE("test graph insertVertex") {
    Graph g(false, true);
    Vertex testVertex("test_label", "+");
    g.insertVertex(testVertex);
    REQUIRE( g.vertexExists(testVertex) );
}

TEST_CASE("test graph removeVertex") {
    Graph g(false, true);
    Vertex testVertex("test_label", "+");
    g.insertVertex(testVertex);
    g.removeVertex(testVertex);
    REQUIRE( !g.vertexExists(testVertex) );
}

TEST_CASE("test graph insertEdge") {
    Graph g(false, true);
    Vertex source("test_source", "+");
    Vertex dest("test_dest", "*");

    g.insertEdge(source, dest);
    REQUIRE( g.edgeExists(source, dest) );
}

TEST_CASE("test graph removeEdge") {
    Graph g(false, true);
    Vertex source("test_source", "+");
    Vertex dest("test_dest", "*");

    g.insertEdge(source, dest);
    g.removeEdge(source, dest);
    REQUIRE( !g.edgeExists(source, dest) );
}

TEST_CASE("test graph getEdges") {
    Graph g(false, true);
    Vertex source1("test_source1", "+");
    Vertex dest1("test_dest1", "*");

    Vertex source2("test_source2", "+");
    Vertex dest2("test_dest2", "*");

    Vertex source3("test_source3", "+");
    Vertex dest3("test_dest3", "*");

    g.insertEdge(source1, dest1);
    g.insertEdge(source2, dest2);
    g.insertEdge(source3, dest3);

    // put all edges into the set
    // find these three edges in the set
    vector<Edge> edges = g.getEdges();
    set<Edge> edgeSet;

    for(Edge edge: edges) {
        edgeSet.insert(edge);
    }

    REQUIRE( edgeSet.find(g.getEdge(source1, dest1)) != edgeSet.end() );
    REQUIRE( edgeSet.find(g.getEdge(source2, dest2)) != edgeSet.end() );
    REQUIRE( edgeSet.find(g.getEdge(source3, dest3)) != edgeSet.end() );
}

TEST_CASE("test graph getAdjacentVertices") {
    Graph g(false, true);
    Vertex source1("test_source1", "+");
    Vertex dest1("test_dest1", "*");

    Vertex source2("test_source2", "+");
    Vertex dest2("test_dest2", "*");

    Vertex source3("test_source3", "+");
    Vertex dest3("test_dest3", "*");

    g.insertEdge(source1, source2);
    g.insertEdge(source1, source3);
    g.insertEdge(source1, dest1);
    g.insertEdge(source1, dest2);
    g.insertEdge(source1, dest3);

    vector<Vertex> adjacent_vertices = g.getAdjacent(source1);
    // convert vector to set
    set<Vertex> vertices_set;
    for(Vertex vertex : adjacent_vertices) {
        vertices_set.insert(vertex);
    }

    REQUIRE( vertices_set.find(source2) != vertices_set.end() );
    REQUIRE( vertices_set.find(source3) != vertices_set.end() );
    REQUIRE( vertices_set.find(dest1) != vertices_set.end() );
    REQUIRE( vertices_set.find(dest2) != vertices_set.end() );
    REQUIRE( vertices_set.find(dest3) != vertices_set.end() );
}