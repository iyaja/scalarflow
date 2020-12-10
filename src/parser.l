/* @file parser.l
 * Reads in raw text from stdin and parses into tokens.
 */

%{

#include "scalarflow/graph.h"

std::vector<string> lines;

%}

%option c++


%%

[a-zA-Z]+\n  { lines.push_back(yytext); }
.          { ; }

%%

int yyFlexLexer::yywrap() {
  return 1;
}