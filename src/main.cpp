/**
 * @file graph.h
 * ScalarFlow Graph Class Declarations
 *
 * @author Ajay Uppili Arasanipalai
 *
 */

#include "scalarflow/sfg.h"
#include "file.h"
#include "lexer.h"

#include <iostream>

int main(int argc, char** argv) {

    yyFlexLexer scanner(std::cin, std::cout);

    // cout << "Parsing..." << endl;

    scanner.yylex();
    File file;
    ScalarFlowGraph * g = file.getGraph();

    // cout << "Registered " << g->getVertices().size() <<  " nodes." << endl;

    // g->print();
    g->compile();
    // map<Vertex, float> vals = g->evalAll();
    g->savePNG("simple");
    // for (std::pair<const Vertex,float> val : vals)
    // {
    //     cout << val.first.first << "\t" << val.second << endl;
    // }

}