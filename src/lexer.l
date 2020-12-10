/* @file parser.l
 * Reads in raw text from stdin and parses into tokens.
 */

%{

#include "scalarflow/graph.h"

std::vector<string> lines;
Graph* g = new Graph();

%}

%option noyywrap

%%

@[a-zA-Z_]+   { g->insertNode }
$[a-zA-Z_]+   { std::cout << yytext << std::endl; }
\n            {  }
.             {  }

%%

int main() {
  yylex();
  return 0;
}