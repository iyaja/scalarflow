#include "catch.hpp"

#include <iostream>
#include <scalarflow/graph.h>


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

TEST_CASE("test graph setEdgeOperand") {
    Graph g(false, true);
    Vertex source("test_source", "+");
    Vertex dest("test_dest", "*");

    g.insertEdge(source, dest);
    g.setEdgeOperand(source, dest, 123.123);
    REQUIRE( g.edgeExists(source, dest) );
    REQUIRE( g.getEdgeOperand(source, dest) == 123.123 );
    REQUIRE( g.getEdge(source, dest).getOperand() == 123.123 );
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

    vector<Vertex> adjacent_vertices = g.getAdjacentVertices(source1);
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

TEST_CASE("test graph getAdjacentInEdges") {
    Graph g(false, true);
    Vertex in1("test_in1", "*");
    Vertex in2("test_in2", "*");
    Vertex center("test_center", "+");
    Vertex out1("test_out1", "*");
    Vertex out2("test_out2", "*");

    g.insertEdge(in1, center);
    g.insertEdge(in2, center);
    g.insertEdge(center, out1);
    g.insertEdge(center, out2);

    vector<Edge> adjacent_in_edges = g.getAdjacentInEdges(center);
    Edge inEdge1 = g.getEdge(in1, center);
    Edge inEdge2 = g.getEdge(in2, center);
    Edge outEdge1 = g.getEdge(center, out1);
    Edge outEdge2 = g.getEdge(center, out2);

    REQUIRE( adjacent_in_edges.size() == 2 );
    REQUIRE( ifSourceInList<Edge>(adjacent_in_edges, inEdge1) );
    REQUIRE( ifSourceInList<Edge>(adjacent_in_edges, inEdge2) );
    REQUIRE( !ifSourceInList<Edge>(adjacent_in_edges, outEdge1) );
    REQUIRE( !ifSourceInList<Edge>(adjacent_in_edges, outEdge2) );
}

TEST_CASE("test graph getAdjacentOutEdges") {
    Graph g(false, true);
    Vertex in1("test_in1", "*");
    Vertex in2("test_in2", "*");
    Vertex center("test_center", "+");
    Vertex out1("test_out1", "*");
    Vertex out2("test_out2", "*");

    g.insertEdge(in1, center);
    g.insertEdge(in2, center);
    g.insertEdge(center, out1);
    g.insertEdge(center, out2);

    vector<Edge> adjacent_out_edges = g.getAdjacentOutEdges(center);
    Edge inEdge1 = g.getEdge(in1, center);
    Edge inEdge2 = g.getEdge(in2, center);
    Edge outEdge1 = g.getEdge(center, out1);
    Edge outEdge2 = g.getEdge(center, out2);

    REQUIRE( adjacent_out_edges.size() == 2 );
    REQUIRE( !ifSourceInList<Edge>(adjacent_out_edges, inEdge1) );
    REQUIRE( !ifSourceInList<Edge>(adjacent_out_edges, inEdge2) );
    REQUIRE( ifSourceInList<Edge>(adjacent_out_edges, outEdge1) );
    REQUIRE( ifSourceInList<Edge>(adjacent_out_edges, outEdge2) );
}

TEST_CASE("test graph getAdjacentOutVertices") {
    Graph g(false, true);
    Vertex in1("test_in1", "*");
    Vertex in2("test_in2", "*");
    Vertex center("test_center", "+");
    Vertex out1("test_out1", "*");
    Vertex out2("test_out2", "*");

    g.insertEdge(in1, center);
    g.insertEdge(in2, center);
    g.insertEdge(center, out1);
    g.insertEdge(center, out2);

    vector<Vertex> adjacent_out_vertices = g.getAdjacentOutVertices(center);

    REQUIRE( adjacent_out_vertices.size() == 2 );
    REQUIRE( !ifSourceInList<Vertex>(adjacent_out_vertices, in1) );
    REQUIRE( !ifSourceInList<Vertex>(adjacent_out_vertices, in2) );
    REQUIRE( ifSourceInList<Vertex>(adjacent_out_vertices, out1) );
    REQUIRE( ifSourceInList<Vertex>(adjacent_out_vertices, out2) );
}

TEST_CASE("test graph getAdjacentInVertices") {
    Graph g(false, true);
    Vertex in1("test_in1", "*");
    Vertex in2("test_in2", "*");
    Vertex center("test_center", "+");
    Vertex out1("test_out1", "*");
    Vertex out2("test_out2", "*");

    g.insertEdge(in1, center);
    g.insertEdge(in2, center);
    g.insertEdge(center, out1);
    g.insertEdge(center, out2);

    vector<Vertex> adjacent_out_vertices = g.getAdjacentInVertices(center);

    REQUIRE( adjacent_out_vertices.size() == 2 );
    REQUIRE( ifSourceInList<Vertex>(adjacent_out_vertices, in1) );
    REQUIRE( ifSourceInList<Vertex>(adjacent_out_vertices, in2) );
    REQUIRE( !ifSourceInList<Vertex>(adjacent_out_vertices, out1) );
    REQUIRE( !ifSourceInList<Vertex>(adjacent_out_vertices, out2) );
}

TEST_CASE("test graph getRandomVertex") {
    Graph g(false, true, 100000);
    Vertex in1("test_in1", "*");
    Vertex in2("test_in2", "*");
    Vertex center("test_center", "+");
    Vertex out1("test_out1", "*");
    Vertex out2("test_out2", "*");

    g.insertEdge(in1, center);
    g.insertEdge(in2, center);
    g.insertEdge(center, out1);
    g.insertEdge(center, out2);

    Vertex randomVertex1 = g.getRandomVertex();
    Vertex randomVertex2 = g.getRandomVertex();

    REQUIRE( randomVertex1 != randomVertex2 );
}