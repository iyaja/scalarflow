/* @file parser.y
 * A simple bison parser for scalarflow
 */

%{
#include "scalarflow/graph.h"
#include "file.h"
#include <string>

int yyerror(char *s);
int yylex(void);
%}

%union {
  int		int_val;
  string*	op_val;
}

%start	input 

%token  FUNCTION
%token  INPUT
%token  OUTPUT
%type	<int_val>	exp

%token <str_val>

%%

input:		/* empty */
		| exp	{ cout << "Result: " << $1 << endl; }
		;

exp:		INTEGER_LITERAL	{ $$ = $1; }
		| exp PLUS exp	{ $$ = $1 + $3; }
		| exp MULT exp	{ $$ = $1 * $3; }
		;

%%

int yyerror(string s)
{
  cerr << "ERROR: " << s << " at symbol \"" << yytext;
  cerr << "\" on line " << yylineno << endl;
  exit(1);
}

int yyerror(char *s)
{
  return yyerror(string(s));
}


