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

#include <chrono>
#include <ctime>
#include <iostream>

using namespace std::chrono;

#define TIME(STMT)                        \
    start = high_resolution_clock::now(); \
    STMT;                                 \
    stop = high_resolution_clock::now();  \
    duration = duration_cast<milliseconds>(stop - start);

typedef map<Vertex, float> Values;

int main(int argc, char **argv)
{

    if (argc != 2)
    {
        std::cerr << "ERROR: please pass one and only one input file" << std::endl;
        exit(1);
    }

    // Initialize timing variables
    auto start = high_resolution_clock::now();
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    std::ifstream file(argv[1]);
    yyFlexLexer scanner(&file);

    cout << "Parsing..." << endl;

    scanner.yylex();
    FileInterface fi;
    ScalarFlowGraph *g = fi.getGraph();

    cout << "INFO: Registered " << g->getVertices().size() << " nodes." << endl;

    // Save parsed graph
    // g->savePNG("out");

    // "Compile" and optimze graph
    g->compile();

    // Call and time forward prop
    TIME(Values forwardVals = g->forwardAll())
    cout << "INFO: completed forward prop in " << duration.count() << "ms" << endl;

    // Call and time lazy eval
    TIME(Values evalVals = g->evalAll())
    cout << "INFO: completed lazy eval in " << duration.count() << "ms" << endl;

    // Choose node for starting point of traversal
    Vertex source = g->getVertices().back();

    // Call and time DFS
    TIME(vector<Edge> DFSPath = g->traverse(source, "DFS"))
    cout << "INFO: DFS visited " << DFSPath.size() << " edges" << endl;
    cout << "INFO: completed depth-first search in " << duration.count() << "ms" << endl;

    // Call and time BFS
    TIME(vector<Edge> BFSPath = g->traverse(source, "BFS"))
    cout << "INFO: BFS visited " << BFSPath.size() << " edges" << endl;
    cout << "INFO: completed breadth-first search in " << duration.count() << "ms" << endl;

    TIME(
        int a = 0;
        for (int i = 0; i < 99999; i++)
            a += i / 3.4;
    )
    cout << "INFO: completed print-first search in " << duration.count() << "ms" << endl;
}