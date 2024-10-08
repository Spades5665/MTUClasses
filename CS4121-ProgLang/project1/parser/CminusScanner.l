%{
#include <stdio.h>
#include <util/symtab.h>
#include <util/symtab_stack.h>
#include <util/string_utils.h>
#include <util/dlink.h>
#include "CminusParser.h"
%}

%option prefix="Cminus_"

%%
while						{ return WHILE; }
int							{ return INTEGER; }
else						{ return ELSE; }
exit						{ return EXIT; }
if							{ return IF; }
read						{ return READ; }
write						{ return WRITE; }
return						{ return RETURN; }
\!							{ return NOT; }
"||"		    			{ return OR; }
\&&							{ return AND; }
\<=							{ return LE; }
\<							{ return LT; }
\>=							{ return GE; }
\>							{ return GT; }
\==							{ return EQ; }
\!=							{ return NE; }
\=							{ return ASSIGN; }
\;							{ return SEMICOLON; }
\{			    			{ return LBRACE; }
"}"			    			{ return RBRACE; }
\[							{ return LBRACKET; }
\]							{ return RBRACKET; }
\(							{ return LPAREN; }
\)							{ return RPAREN; }
\+							{ return PLUS; }
\-          				{ return MINUS; }
\*							{ return TIMES; }
\/							{ return DIVIDE; }
","							{ return COMMA; }
\"[^\"]*\"					{ Cminus_lval.text = strdup(Cminus_text); return STRING; }     // Creates a copy of the token text and returns it to parser
[a-zA-Z]([a-zA-Z]|[0-9])*	{ Cminus_lval.text = strdup(Cminus_text); return IDENTIFIER; } // Creates a copy of the token text and returns it to parser
[0-9]+						{ Cminus_lval.num = atoi(Cminus_text); return INTCON; }        // Creates an int from the token text and returns it to parser
[ \r\t]						{ ; }
"\n"						{ Cminus_lineno++; }
.							{ fprintf(stderr, "Scanner lexical error: unrecognized token %s at line %d.\n", Cminus_text, Cminus_lineno); }
%%
