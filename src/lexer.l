/* @file parser.l
 * Reads in raw text from stdin and parses into tokens.
 */

%{

#include "scalarflow/graph.h"
#include "fileinterface.h"
#include <string>
#include <map>

using namespace std;

ScalarFlowGraph * g = new ScalarFlowGraph(true, true);

std::map<std::string, Vertex> nodes;

char* id;
char* in;
string fname;
string out;

void addNode(string id, string fname) {
  out = id;
  Vertex v = { id, fname };
  nodes.insert({id, v});
  g->insertVertex(v);
}

void addEdge(string in, string id) {
  g->insertEdge(nodes.at(in), nodes.at(id));
}

void setFunction(string f) {
  fname = f;
}

void storeConst(string val) {
  Vertex v = { out, fname };
  g->setValue(v, stof(val));
}

%}

%option c++

%%

@[a-zA-Z0-9]+          { setFunction(&yytext[1]); }
%[a-zA-Z]+          { id = &yytext[1]; addNode(id, fname); }
$[a-zA-Z]+          { in = &yytext[1]; addEdge(in, out); }
[0-9]+[\.]*[0-9]*   { storeConst(yytext); }
.                   {  }

%%

int yyFlexLexer::yywrap() {
  return 1;
}

ScalarFlowGraph * FileInterface::getGraph() {
  return g;
}