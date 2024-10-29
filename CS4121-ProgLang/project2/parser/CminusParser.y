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

/*********************EXTERNAL DECLARATIONS***********************/

EXTERN(void, Cminus_error, (const char*));

EXTERN(int, Cminus_lex, (void));

char *fileName;

SymTable symtab;
SymTable regSymTab;

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
						//genEnd();
					}
				;

ProcedureHead 	: FunctionDecl DeclList 
					{
						//genMain();
					}
	      		| FunctionDecl
					{
						//genMain();
					}
              	;	

FunctionDecl 	:  Type IDENTIFIER LPAREN RPAREN LBRACE 
					{
						//printf("Index for %s = %d\n", (char *) SymGetFieldByIndex(symtab, $2, SYM_NAME_FIELD), $2);
					}
				;

ProcedureBody 	: StatementList RBRACE
					{
						
					}
				;

DeclList 		: Type IdentifierList SEMICOLON 
					{
						//genSpace(( 4 * ($2 + 1) ));
					}		
				| DeclList Type IdentifierList SEMICOLON
					{
						
					}
				;

IdentifierList 	: VarDecl  
					{
						//printf("Index for %s = %d\n", (char *) SymGetFieldByIndex(symtab, $1, SYM_NAME_FIELD), $1);
						$$ = $1;
					}
									
				| IdentifierList COMMA VarDecl
					{
						//printf("Index for %s = %d\n", (char *) SymGetFieldByIndex(symtab, $3, SYM_NAME_FIELD), $3);
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
						genWriteStr($3);
						genNewLine();
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
						$$ = genArith(regSymTab, $1, $3, "add");
					}
				|  AddExpr MINUS MulExpr
					{
						$$ = genArith(regSymTab, $1, $3, "sub");
					}
                ;

MulExpr			:  Factor
					{
						$$ = $1;
					}
				|  MulExpr TIMES Factor
					{
						$$ = genArith(regSymTab, $1, $3, "mul");
					}
				|  MulExpr DIVIDE Factor
					{
						$$ = genArith(regSymTab, $1, $3, "div");
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
						$$ = genString(symtab, $1);
					} 
                ;

Constant        : INTCON
					{ 
						$$ = genInt(regSymTab, $1);
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
	char * sub = substr(inputFileName, 0, endIndex);
	char *outputFileName = nssave(2, sub, ".s");
	free(sub);
	stdout = freopen(outputFileName, "w", stdout);
	if (stdout == NULL) {
		fprintf(stderr, "Error: Could not open file %s\n", outputFileName);
		free(outputFileName);
		exit(-1);
	}

	free(outputFileName);
	symtab = SymInit(SYMTABLE_SIZE);
	regSymTab = SymInit(SYMTABLE_SIZE);
	SymInitField(symtab, SYM_VALUE_FIELD, (Generic) -1, NULL);
	SymInitField(symtab, SYM_VARNAME_FIELD, (Generic) -1, NULL);

	initRegisters();
}

static void finalize() {
    cleanupRegisters();
	SymKillField(symtab, SYM_VALUE_FIELD);
	SymKillField(symtab, SYM_VARNAME_FIELD);
    SymKill(symtab);
	SymKill(regSymTab);
    fclose(Cminus_in);
    fclose(stdout);
	Cminus_lex_destroy();
}

int main(int argc, char** argv) {	
	fileName = argv[1];
	initialize(fileName);
	Cminus_parse();
  	finalize();
  	return 0;
}

int getValue(int index) {
	return (int) SymGetFieldByIndex(symtab, index, SYM_VALUE_FIELD); 
}

int setValue(int index, int value) {
	SymPutFieldByIndex(symtab, index, SYM_VALUE_FIELD, (Generic) value); 
}
/******************END OF C ROUTINES**********************/
