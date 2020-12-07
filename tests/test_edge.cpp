#include <iostream>
#include <catch2/catch.hpp>
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

TEST_CASE("test graph computeOutEdges") {
    Graph g(false, true, 100000);
    Vertex vertex1("1", "start");
    Vertex vertex2("2", "+");
    Vertex vertex3("3", "start");
    Vertex vertex4("4", "+");
    Vertex vertex5("5", "*");
    Vertex vertex6("6", "start");
    Vertex vertex7("7", "+");
    Vertex vertex8("8", "end");

    g.insertEdge(vertex1, vertex5);
    g.insertEdge(vertex1, vertex2);
    g.insertEdge(vertex3, vertex2);
    g.insertEdge(vertex2, vertex4);
    g.insertEdge(vertex5, vertex4);
    g.insertEdge(vertex6, vertex5);
    g.insertEdge(vertex5, vertex7);
    g.insertEdge(vertex4, vertex7);

    g.setEdgeOperand(vertex1, vertex5, 3);
    g.setEdgeOperand(vertex1, vertex2, 1);
    g.setEdgeOperand(vertex3, vertex2, 2);
    g.setEdgeOperand(vertex6, vertex5, 4);

    REQUIRE( g.computeOutEdges(vertex5) == 12 );
    REQUIRE( g.computeOutEdges(vertex2) == 3 );
}

TEST_CASE("test graph compute") {
    Graph g(false, true, 100000);
    Vertex vertex1("1", "start");
    Vertex vertex2("2", "+");
    Vertex vertex3("3", "start");
    Vertex vertex4("4", "+");
    Vertex vertex5("5", "*");
    Vertex vertex6("6", "start");
    Vertex vertex7("7", "+");
    Vertex vertex8("8", "end");

    g.insertEdge(vertex1, vertex5);
    g.insertEdge(vertex1, vertex2);
    g.insertEdge(vertex3, vertex2);
    g.insertEdge(vertex2, vertex4);
    g.insertEdge(vertex5, vertex4);
    g.insertEdge(vertex6, vertex5);
    g.insertEdge(vertex5, vertex7);
    g.insertEdge(vertex4, vertex7);
    g.insertEdge(vertex7, vertex8);


    g.setEdgeOperand(vertex1, vertex5, 3);
    g.setEdgeOperand(vertex1, vertex2, 1);
    g.setEdgeOperand(vertex3, vertex2, 2);
    g.setEdgeOperand(vertex6, vertex5, 4);

    Vertex randomVertex = g.getRandomVertex();
    g.compute(randomVertex);

    REQUIRE( g.getEdge(vertex7, vertex8).getOperand() == 27 );
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