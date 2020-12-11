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

TEST_CASE("test_edge_constructor") {
    SECTION("test_default_constructor") {
        Edge edge;

        REQUIRE(edge.source == std::pair<string, string>("", ""));
        REQUIRE(edge.dest == std::pair<string, string>("", ""));
        REQUIRE(edge.getLabel() == "");
    }

    SECTION("test_2_param_constructor") {
        Vertex source = std::pair<string, string>("sourceL", "+");
        Vertex desti = std::pair<string, string>("destiL", "-");

        Edge edge(source, desti);

        REQUIRE(edge.source == source);
        REQUIRE(edge.dest == desti);
        REQUIRE(edge.getLabel() == "");
    }

    SECTION("test_4_param_constructor") {
        Vertex source = std::pair<string, string>("sourceL", "+");
        Vertex desti = std::pair<string, string>("destiL", "-");
        string label = "label";

        Edge edge(source, desti, label);

        REQUIRE(edge.source == source);
        REQUIRE(edge.dest == desti);
        REQUIRE(edge.getLabel() == label);
    }

}