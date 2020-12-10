#include "scalarflow/graph.h"
#include "file.h"
#include "lexer.h"

#include <iostream>

using namespace std;

int main(int argc, char** argv) {

    yyFlexLexer scanner(std::cin, std::cout);

    cout << "Parsing..." << endl;

    scanner.yylex();
    File file;
    Graph * g = file.getGraph();

    cout << "Registered " << g->getVertices().size() <<  " nodes." << endl;

    g->print();

}