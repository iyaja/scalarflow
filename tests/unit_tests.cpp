#include "../cs225/catch/catch.hpp"

#include "../graph.h"

#include "../edge.h"

#include <iostream>

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



TEST_CASE("test_edge_constructor") {
    SECTION("test_default_constructor") {
        Edge edge;

        REQUIRE(edge.source == std::pair<string, string>("", ""));
        REQUIRE(edge.dest == std::pair<string, string>("", ""));
        REQUIRE(edge.getLabel() == "");
        REQUIRE(edge.getOperand() == 0.0);
    }

    SECTION("test_2_param_constructor") {
        Vertex source = std::pair<string, string>("sourceL", "+");
        Vertex desti = std::pair<string, string>("destiL", "-");

        Edge edge(source, desti);

        REQUIRE(edge.source == source);
        REQUIRE(edge.dest == desti);
        REQUIRE(edge.getLabel() == "");
        REQUIRE(edge.getOperand() == 0.0);
    }

    SECTION("test_4_param_constructor") {
        Vertex source = std::pair<string, string>("sourceL", "+");
        Vertex desti = std::pair<string, string>("destiL", "-");
        string label = "label";
        double operand = 5.0;

        Edge edge(source, desti, label, operand);

        REQUIRE(edge.source == source);
        REQUIRE(edge.dest == desti);
        REQUIRE(edge.getLabel() == label);
        REQUIRE(edge.getOperand() == operand);
    }

}