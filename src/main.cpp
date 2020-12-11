/**
 * @file main.cpp
 * Entry point to scalarflow binary
 *
 * @author Ajay Uppili Arasanipalai
 *
 */

#include "scalarflow/sfg.h"
#include "fileinterface.h"
#include "lexer.h"

#include <iostream>

int main(int argc, char** argv) {

    if (argc != 2)
    {
        std::cerr << "ERROR: please pass one and only one input file" << std::endl;
        exit(1);
    }

    std::ifstream file(argv[1]);
    yyFlexLexer scanner(&file);

    cout << "Parsing..." << endl;

    scanner.yylex();
    FileInterface fi;
    ScalarFlowGraph * g = fi.getGraph();

    cout << "Registered " << g->getVertices().size() <<  " nodes." << endl;

    // g->print();
    g->compile();
    map<Vertex, float> vals = g->evalAll();
    g->savePNG("simple");

    Vertex source = {"a", "const"};
    vector<Edge> path = g->traverse(source, "BFS");

    for (Edge e : path)
        cout << e.source.first << "->" << e.dest.first << endl;

}