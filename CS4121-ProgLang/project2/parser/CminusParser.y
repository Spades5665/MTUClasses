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
#include "../util/symtab.h"
#include <util/symtab_stack.h>
#include "../util/dlink.h"
#include <util/string_utils.h>

#define SYMTABLE_SIZE 100

/*********************EXTERNAL DECLARATIONS***********************/

EXTERN(void, Cminus_error, (const char*));

EXTERN(int, Cminus_lex, (void));

char *fileName;

SymTable symtab;              // Holds variables and their values
SymTable regSymTab;           // Holds registers and if they are in use
DLinkList * declarations;     // Contains the .data instructions
DLinkList * instructions;     // Contains the .text instructions
int mainSet = 0;              // Keeps offset consistent

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
// Program prints out the correct order of declarations and instructions
Program			: Procedures 
					{
						DLinkNode * current1 = dlinkHead(declarations);
						while (current1) {
							printf("%s\n", (char *) dlinkNodeAtom(current1));
							current1 = dlinkNext(current1);
						} 

						DLinkNode * current2 = dlinkHead(instructions);
						while (current2) {
							printf("%s\n", (char *) dlinkNodeAtom(current2));
							current2 = dlinkNext(current2);
						} 
					}
				| DeclList Procedures
					{
						DLinkNode * current1 = dlinkHead(declarations);
						while (current1) {
							printf("%s\n", (char *) dlinkNodeAtom(current1));
							current1 = dlinkNext(current1);
						} 

						DLinkNode * current2 = dlinkHead(instructions);
						while (current2) {
							printf("%s\n", (char *) dlinkNodeAtom(current2));
							current2 = dlinkNext(current2);
						}
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
						genEnd(instructions);
					}
				;

ProcedureHead 	: FunctionDecl DeclList 
					{
						genMain(instructions);
					}
	      		| FunctionDecl
					{
						genMain(instructions);
					}
              	;	

FunctionDecl 	:  Type IDENTIFIER LPAREN RPAREN LBRACE 
					{
						mainSet = 1;
					}
				;

ProcedureBody 	: StatementList RBRACE
					{
						
					}
				;

DeclList 		: Type IdentifierList SEMICOLON 
					{
						genSpace(instructions, $2 + 4);
					}		
				| DeclList Type IdentifierList SEMICOLON
					{
						
					}
				;

IdentifierList 	: VarDecl  
					{
						$$ = setOffset($1, 4 * ($1 - mainSet));
					}
									
				| IdentifierList COMMA VarDecl
					{
						$$ = setOffset($3, 4 * ($3 - mainSet));
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
						genAssign(instructions, regSymTab, $1, $3, getOffset($1));
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
						genRead(instructions, regSymTab, $3, getOffset($3));
					}
				| WRITE LPAREN Expr RPAREN SEMICOLON
					{
						genWriteNum(instructions, $3);
					}
				| WRITE LPAREN StringConstant RPAREN SEMICOLON         
					{
						genWriteStr(instructions, $3);
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
						$$ = genArith(instructions, regSymTab, $1, $3, "or");
					}
				| Expr AND SimpleExpr 
					{
						$$ = genArith(instructions, regSymTab, $1, $3, "and");
					}
				| NOT SimpleExpr 
					{
						$$ = genNot(instructions, regSymTab, $2);
					}
                ;

SimpleExpr		: AddExpr
					{
						$$ = $1;
					}
				| SimpleExpr EQ AddExpr
					{
						$$ = genEqual(instructions, regSymTab, $1, $3);
					}
				| SimpleExpr NE AddExpr
					{
						$$ = genNotEqual(instructions, regSymTab, $1, $3);
					}
				| SimpleExpr LE AddExpr
					{
						$$ = genLE(instructions, regSymTab, $1, $3);
					}
				| SimpleExpr LT AddExpr
					{
						$$ = genLT(instructions, regSymTab, $1, $3);
					}
				| SimpleExpr GE AddExpr
					{
						$$ = genGE(instructions, regSymTab, $1, $3);
					}
				| SimpleExpr GT AddExpr
					{
						$$ = genGT(instructions, regSymTab, $1, $3);
					}
                ;

AddExpr			:  MulExpr            
					{
						$$ = $1;
					}
				|  AddExpr PLUS MulExpr
					{
						$$ = genArith(instructions, regSymTab, $1, $3, "add");
					}
				|  AddExpr MINUS MulExpr
					{
						$$ = genArith(instructions, regSymTab, $1, $3, "sub");
					}
                ;

MulExpr			:  Factor
					{
						$$ = $1;
					}
				|  MulExpr TIMES Factor
					{
						$$ = genArith(instructions, regSymTab, $1, $3, "mul");
					}
				|  MulExpr DIVIDE Factor
					{
						$$ = genArith(instructions, regSymTab, $1, $3, "div");
					}		
                ;
				
Factor          : Variable
					{ 
						$$ = genVal(instructions, regSymTab, $1, getOffset($1));
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
						$$ = genString(declarations, symtab, $1);
					} 
                ;

Constant        : INTCON
					{ 
						$$ = genInt(instructions, regSymTab, $1);
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
	SymInitField(symtab, SYM_OFFSET_FIELD, (Generic) -1, NULL);
	instructions = dlinkListAlloc((Generic) "insts");
	declarations = dlinkListAlloc((Generic) "decls");
	char *inst = nssave(2,  ".data\n",
                            ".newLine: .asciiz \"\\n\""
                        );
	dlinkAppend(declarations, dlinkNodeAlloc((Generic) inst));
	initRegisters();
}

static void finalize() {
    cleanupRegisters();
	dlinkFreeNodesAndAtoms(instructions);
	dlinkFreeNodesAndAtoms(declarations);
	dlinkListFree(instructions);
	dlinkListFree(declarations);
	SymKillField(symtab, SYM_OFFSET_FIELD);
	SymKillField(symtab, SYM_VALUE_FIELD);
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

// Gets the offset of a variable using its index
int getOffset(int index) {
	return (int) SymGetFieldByIndex(symtab, index, SYM_OFFSET_FIELD); 
}

// Sets the offset of a variable using its index
int setOffset(int index, int value) {
	SymPutFieldByIndex(symtab, index, SYM_OFFSET_FIELD, (Generic) value); 
	return getOffset(index);
}
/******************END OF C ROUTINES**********************/
