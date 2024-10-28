/*******************************************************/
/*                     Cminus Parser                   */
/*                                                     */
/*******************************************************/

/*********************DEFINITIONS***********************/
%{
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <util/general.h>
#include <util/symtab.h>
#include <util/symtab_stack.h>
#include <util/dlink.h>
#include <util/string_utils.h>

#define SYMTABLE_SIZE 100
#define SYMTAB_VALUE_FIELD     "value"

/*********************EXTERNAL DECLARATIONS***********************/

EXTERN(void, Cminus_error, (const char*));

EXTERN(int, Cminus_lex, (void));

char *fileName;

SymTable symtab;

extern int Cminus_lineno;

extern FILE *Cminus_in;
%}

%name-prefix = "Cminus_"
%defines

%start Program

%token AND
%token ELSE
%token EXIT
%token FOR
%token IF 		
%token INTEGER 
%token NOT 		
%token OR 		
%token READ
%token WHILE
%token WRITE
%token LBRACE
%token RBRACE
%token LE
%token LT
%token GE
%token GT
%token EQ
%token NE
%token ASSIGN
%token COMMA
%token SEMICOLON
%token LBRACKET
%token RBRACKET
%token LPAREN
%token RPAREN
%token PLUS
%token TIMES
%token IDENTIFIER
%token DIVIDE
%token RETURN
%token STRING	
%token INTCON
%token MINUS

%left OR
%left AND
%left NOT
%left LT LE GT GE NE EQ
%left PLUS MINUS
%left TIMES DIVDE

/***********************PRODUCTIONS****************************/
%%
Program			: Procedures 
					{
						
					}
				| DeclList Procedures
					{
						
					}
				;

Procedures 		: ProcedureDecl Procedures
					{
						
					}
				| 
					{
						
					}
				;

ProcedureDecl 	: ProcedureHead ProcedureBody
					{
						genEnd();
					}
				;

ProcedureHead 	: FunctionDecl DeclList 
					{
						genMain();
					}
	      		| FunctionDecl
					{
						genMain();
					}
              	;	

FunctionDecl 	:  Type IDENTIFIER LPAREN RPAREN LBRACE 
					{
						
					}
				;

ProcedureBody 	: StatementList RBRACE
					{
						
					}
				;


DeclList 		: Type IdentifierList SEMICOLON 
					{
						genSpace(( 4 * ($2 + 1) ));
					}		
				| DeclList Type IdentifierList SEMICOLON
					{
						
					}
				;


IdentifierList 	: VarDecl  
					{
						$$ = $1;
					}
									
				| IdentifierList COMMA VarDecl
					{
						$$ = $3;
					}
                ;

VarDecl 		: IDENTIFIER
					{ 
						$$ = $1;
					}
				| IDENTIFIER LBRACKET INTCON RBRACKET
					{
					
					}
				;

Type     		: INTEGER 
					{ 
						
					}
                ;

Statement 		: Assignment
					{ 
						
					}
				| IfStatement
					{ 
						
					}
				| WhileStatement
					{ 
						
					}
				| IOStatement 
					{ 
						
					}
				| ReturnStatement
					{ 
						
					}
				| ExitStatement	
					{ 
						
					}
				| CompoundStatement
					{ 
						
					}
                ;

Assignment      : Variable ASSIGN Expr SEMICOLON
					{
						setValue($1, $3);
					}
                ;
				
IfStatement		: IF TestAndThen ELSE CompoundStatement
					{
						
					}
				| IF TestAndThen
					{
						
					}
				;
		
				
TestAndThen		: Test CompoundStatement
					{
						
					}
				;
				
Test			: LPAREN Expr RPAREN
					{
						
					}
				;
	

WhileStatement  : WhileToken WhileExpr Statement
					{
						
					}
                ;
                
WhileExpr		: LPAREN Expr RPAREN
					{
						
					}
				;
				
WhileToken		: WHILE
					{
						
					}
				;


IOStatement     : READ LPAREN Variable RPAREN SEMICOLON
					{
						int t;
						scanf("%d", &t);
						setValue($3, t); 
					}
				| WRITE LPAREN Expr RPAREN SEMICOLON
					{
						//printf("%d\n", $3);
					}
				| WRITE LPAREN StringConstant RPAREN SEMICOLON         
					{
						//printf("%s\n", (char *) SymGetFieldByIndex(symtab, $3, SYM_NAME_FIELD));
					}
                ;

ReturnStatement : RETURN Expr SEMICOLON
					{
						
					}
                ;

ExitStatement 	: EXIT SEMICOLON
					{
						
					}
				;

CompoundStatement: LBRACE StatementList RBRACE
					{
						
					}
                ;

StatementList   : Statement
					{		

					}
				| StatementList Statement
					{		

					}
                ;

Expr            : SimpleExpr
					{
						$$ = $1;
					}
				| Expr OR SimpleExpr 
					{
						$$ = $1 | $3;
					}
				| Expr AND SimpleExpr 
					{
						$$ = $1 & $3;
					}
				| NOT SimpleExpr 
					{
						$$ = $2 ^ 1;
					}
                ;

SimpleExpr		: AddExpr
					{
						$$ = $1;
					}
				| SimpleExpr EQ AddExpr
					{
						$$ = ($1 == $3);
					}
				| SimpleExpr NE AddExpr
					{
						$$ = ($1 != $3);
					}
				| SimpleExpr LE AddExpr
					{
						$$ = ($1 <= $3);
					}
				| SimpleExpr LT AddExpr
					{
						$$ = ($1 < $3);
					}
				| SimpleExpr GE AddExpr
					{
						$$ = ($1 >= $3);
					}
				| SimpleExpr GT AddExpr
					{
						$$ = ($1 > $3);
					}
                ;

AddExpr			:  MulExpr            
					{
						$$ = $1;
					}
				|  AddExpr PLUS MulExpr
					{
						$$ = $1 + $3;
					}
				|  AddExpr MINUS MulExpr
					{
						$$ = $1 - $3;
					}
                ;

MulExpr			:  Factor
					{
						$$ = $1;
					}
				|  MulExpr TIMES Factor
					{
						$$ = $1 * $3;
					}
				|  MulExpr DIVIDE Factor
					{
						$$ = $1 / $3;
					}		
                ;
				
Factor          : Variable
					{ 
						$$ = getValue($1);
					}
				| Constant
					{ 
						$$ = $1;
					}
				| IDENTIFIER LPAREN RPAREN
					{

					}
				| LPAREN Expr RPAREN
					{
						$$ = $2;
					}
                ;  

Variable        : IDENTIFIER
					{
						$$ = $1;
					}
                | IDENTIFIER LBRACKET Expr RBRACKET    
					{

					}
                ;			       

StringConstant 	: STRING
					{ 
						genString((char *) SymGetFieldByIndex(symtab, $1, SYM_NAME_FIELD));
						$$ = $1;
					} 
                ;

Constant        : INTCON
					{ 
						$$ = $1;
					}
                ;
%%


/********************C ROUTINES *********************************/

void Cminus_error(const char *s) {
  fprintf(stderr, "%s: line %d: %s\n", fileName, Cminus_lineno, s);
}

int Cminus_wrap() {
	return 1;
}

static void initialize(char* inputFileName) {
	Cminus_in = fopen(inputFileName, "r");
	if (Cminus_in == NULL) {
		fprintf(stderr, "Error: Could not open file %s\n", inputFileName);
		exit(-1);
	}

	char* dotChar = rindex(inputFileName, '.');
	int endIndex = strlen(inputFileName) - strlen(dotChar);
	char *outputFileName = nssave(2, substr(inputFileName, 0, endIndex), ".s");
	stdout = freopen(outputFileName, "w", stdout);
	if (stdout == NULL) {
		fprintf(stderr, "Error: Could not open file %s\n", outputFileName);
		exit(-1);
	}

	symtab = SymInit(SYMTABLE_SIZE);
	SymInitField(symtab, SYMTAB_VALUE_FIELD, (Generic) -1, NULL);
}

static void finalize() {
    SymKillField(symtab, SYMTAB_VALUE_FIELD);
    SymKill(symtab);
    fclose(Cminus_in);
    fclose(stdout);
}

int main(int argc, char** argv) {	
	fileName = argv[1];
	initialize(fileName);
	Cminus_parse();
  	finalize();
  	return 0;
}

int getValue(int index) {
	return (int) SymGetFieldByIndex(symtab, index, SYMTAB_VALUE_FIELD); 
}

int setValue(int index, int value) {
	SymPutFieldByIndex(symtab, index, SYMTAB_VALUE_FIELD, (Generic) value); 
}
/******************END OF C ROUTINES**********************/
