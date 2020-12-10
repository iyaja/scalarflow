/* @file parser.l
 * Reads in raw text from stdin and parses into tokens.
 */

%{

#include "scalarflow/graph.h"
#include "file.h"
#include <string>
#include <map>

using namespace std;

Graph * g = new Graph(true, true);

std::map<std::string, Vertex> nodes;

char* id;
char* in;
char* fname;
string out;

void addNode(string id, string fname) {
  out = id;
  Vertex v = { id, fname };
  nodes.insert({id, v});
  g->insertVertex(v);
}

void addEdge(string in, string id) {
  if (nodes.at(in).second == "input")
    return;
  g->insertEdge(nodes.at(in), nodes.at(id));
}


%}

%option c++

%%

@[a-zA-Z]+          { fname = &yytext[1]; }
%[a-zA-Z]+          { id = &yytext[1]; addNode(id, fname); }
$[a-zA-Z]+          { in = &yytext[1]; addEdge(in, out); }
.                   {  }

%%

int yyFlexLexer::yywrap() {
  return 1;
}

Graph * File::getGraph() {
  return g;
}