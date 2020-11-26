#include "../cs225/catch/catch.hpp"

#include "../graph.h"

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