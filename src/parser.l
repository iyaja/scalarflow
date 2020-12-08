/* @file parser.l
 * Reads in raw text from stdin and parses into tokens.
 */

%{

#include "scalarflow/graph.h"

std::vector<string> lines;

%}

%%

[a-zA-Z]+\n  { lines.push_back(yytext) }
.          { ; }

%%

main(int argc, char **argv)
{
  yylex();
  printf("%8d%8d%8d\n", lines);
}