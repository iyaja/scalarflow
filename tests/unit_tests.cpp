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