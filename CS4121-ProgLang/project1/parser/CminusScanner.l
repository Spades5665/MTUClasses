WS	[ \t]

typedef char* YYSTYPE;

%{

/* This scanner approximates the Void specification.
 *
 * Major differences:
 *
 *  (1) the printed spec is wrong in about sixteen ways in its definition
 *	of numeric constants.  The scanner recognizes a fairly broad class
 * 	of things as constants - it allows both 0 and 1.0 as constants, where
 *	the document would not.
 *
 *      Feel free to accept the things that the scanner accepts as constants.
 *	The bug is in the original spec document.
 *
 *	Note: the scanner classifies all kinds of constants as "constant".
 *	It does not make a distinction between character, integer, and floating
 *	point constants.  I think of that distinction as something to look for
 *	in the type checker lab, not something that the grammar should enforce.
 *
 *
 * To hook this thing up to your parser, you will need to take the include
 * file of grammar terminals and relate them to the constants defined below.
 * You can either edit the flex spec or edit the constant defintions.  (Of
 * course, you should do that on your own copy!)  
 *
 */

#include <stdio.h>
#include <util/symtab.h>
#include <util/symtab_stack.h>
#include <util/string_utils.h>
#include <util/dlink.h>
#include "CminusParser.h"

%}

%option bison-bridge
%option prefix="Cminus_"

%%

int							{ Cminus_lval = strdup(Cminus_text); return INTEGER; }
while						{ Cminus_lval = strdup(Cminus_text); return WHILE; }
else						{ Cminus_lval = strdup(Cminus_text); return ELSE; }
exit						{ Cminus_lval = strdup(Cminus_text); return EXIT; }
if							{ Cminus_lval = strdup(Cminus_text); return IF; }
read						{ Cminus_lval = strdup(Cminus_text); return READ; }
write						{ Cminus_lval = strdup(Cminus_text); return WRITE; }
return						{ Cminus_lval = strdup(Cminus_text); return RETURN; }
\!							{ Cminus_lval = strdup(Cminus_text); return NOT; }
"||"		    			{ Cminus_lval = strdup(Cminus_text); return OR; }
\&&							{ Cminus_lval = strdup(Cminus_text); return AND; }
\<=							{ Cminus_lval = strdup(Cminus_text); return LE; }
\<							{ Cminus_lval = strdup(Cminus_text); return LT; }
\>=							{ Cminus_lval = strdup(Cminus_text); return GE; }
\>							{ Cminus_lval = strdup(Cminus_text); return GT; }
\==							{ Cminus_lval = strdup(Cminus_text); return EQ; }
\!=							{ Cminus_lval = strdup(Cminus_text); return NE; }
\=							{ Cminus_lval = strdup(Cminus_text); return ASSIGN; }
\;							{ Cminus_lval = strdup(Cminus_text); return SEMICOLON; }
\{			    			{ Cminus_lval = strdup(Cminus_text); return LBRACE; }
"}"			    			{ Cminus_lval = strdup(Cminus_text); return RBRACE; }
\[							{ Cminus_lval = strdup(Cminus_text); return LBRACKET; }
\]							{ Cminus_lval = strdup(Cminus_text); return RBRACKET; }
\(							{ Cminus_lval = strdup(Cminus_text); return LPAREN; }
\)							{ Cminus_lval = strdup(Cminus_text); return RPAREN; }
\+							{ Cminus_lval = strdup(Cminus_text); return PLUS; }
\-          				{ Cminus_lval = strdup(Cminus_text); return MINUS; }
\*							{ Cminus_lval = strdup(Cminus_text); return TIMES; }
\/							{ Cminus_lval = strdup(Cminus_text); return DIVIDE; }
","							{ Cminus_lval = strdup(Cminus_text); return COMMA; }
\"[^\"]*\"					{ Cminus_lval = strdup(Cminus_text); return STRING; }
[a-zA-Z]([a-zA-Z]|[0-9])*	{ Cminus_lval = strdup(Cminus_text); return IDENTIFIER; }
[0-9]*\.[0-9]+ 				{ Cminus_lval = strdup(Cminus_text); return FLTCON; }
[0-9]+						{ Cminus_lval = strdup(Cminus_text); return INTCON; }
{WS}						{ ; }
"\n"						{ Cminus_lineno++; }
.							{ fprintf(stderr, "Scanner: lexical error '%s'.\n", Cminus_text); }

%%
