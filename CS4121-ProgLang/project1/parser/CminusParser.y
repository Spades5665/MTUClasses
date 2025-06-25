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

extern int Cminus_lineno;

extern FILE *Cminus_in;

extern int Cminus_lex_destroy(void);

SymTable symtab; // Symbol table for holding variables and their values

%}

%define api.prefix {Cminus_}
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
%left TIMES DIVIDE

// Defines the types of values tokens and expressions can return
%union {
	char *text;
	int    num;
}

%type <text> STRING IDENTIFIER StringConstant VarDecl Variable IdentifierList DeclList  // All of these return a char *
%type <num>  INTCON Constant Factor MulExpr AddExpr SimpleExpr Expr                     // All of these return an int

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
						
					}
				;

ProcedureHead 	: FunctionDecl DeclList 
					{
						
					}
				| FunctionDecl
					{
						
					}
				;

FunctionDecl 	:  Type IDENTIFIER LPAREN RPAREN LBRACE 
					{
						free($2); // Saves memory leak
					}
				;

ProcedureBody 	: StatementList RBRACE
					{
						
					}
				;

DeclList    	: Type IdentifierList SEMICOLON 
					{
						char* id = strtok($2, ","); // Separates each id from a list separated by commas
						while (id != NULL) {        // Loops until no ids are left
							SymIndex(symtab, id);   // Creates a variable for id in the table
							id = strtok(NULL, ","); // Gets the next id
						}
						free(id);
						free($2);
					}		
				| DeclList Type IdentifierList SEMICOLON
					{
						char* id = strtok($3, ","); // Separates each id from a list separated by commas
						while (id != NULL) {        // Loops until no ids are left
							SymIndex(symtab, id);   // Creates a variable for id in the table
							id = strtok(NULL, ","); // Gets the next id
						}
						free(id);
						free($3);
					}
				;

IdentifierList  : VarDecl  
		            {
						$$ = $1;
		            }		
            	| IdentifierList COMMA VarDecl
		        	{    
						char *copy = (char *) malloc((strlen($1) + strlen($3) + 2) * sizeof(char)); // Allocates enough space to append strings
						strcpy(copy, $1);   // Copies the first string
						strcat(copy, ",");  // Adds a comma
						strcat(copy, $3);   // Adds the other string
						free($1);
						free($3);
						$$ = copy;
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

						SymPutField(symtab, $1, $1, $3); // Adds the value to the variable in the table
						free($1);
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
						int val;
						scanf("%d", &val);
						SymPutField(symtab, $3, $3, val); // Adds the value to the variable in the table
						free($3);
					}
                | WRITE LPAREN Expr RPAREN SEMICOLON
					{
						printf("%d\n", $3);
					}
                | WRITE LPAREN StringConstant RPAREN SEMICOLON         
					{
						printf("%s\n", $3);
						free($3);
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
						$$ = $1 || $3;
					}
                | Expr AND SimpleExpr 
					{
						$$ = $1 && $3;
					}
                | NOT SimpleExpr 
					{
						$$ = !$2;
					}
                ;

SimpleExpr		: AddExpr
					{
						$$ = $1;
					}
                | SimpleExpr EQ AddExpr
					{
						$$ = $1 == $3;
					}
                | SimpleExpr NE AddExpr
					{
						$$ = $1 != $3;
					}
                | SimpleExpr LE AddExpr
					{
						$$ = $1 <= $3;
					}
                | SimpleExpr LT AddExpr
					{
						$$ = $1 < $3;
					}
                | SimpleExpr GE AddExpr
					{
						$$ = $1 >= $3;
					}
                | SimpleExpr GT AddExpr
					{
						$$ = $1 > $3;
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
						if ($3 == 0) {                                           // Checks if zero is attempted 
							fprintf(stderr, "ERROR --- Can't divide by 0\n");
							exit(1);
						}
						$$ = $1 / $3;
					}		
                ;
				
Factor          : Variable
					{ 
						$$ = (int) SymGetField(symtab, $1, $1); // Gets the value from the table
						free($1);
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
						char *copy = (char *) malloc((strlen($1) - 1) * sizeof(char)); // Creates a string for removing the quotes
						for (int i = 1; i < strlen($1) - 1; i++) {                     // Removes the first and last character in $1 and stores it in copy
							copy[i - 1] = $1[i];             
						}
						copy[strlen($1) - 2] = '\0';                                   // Adds the null terminator
						free($1);
						$$ = copy;
					}
                ;

Constant        : INTCON
					{
						$$ = $1;
					}
				;

%%

/********************C ROUTINES *********************************/

void Cminus_error(const char *s) {fprintf(stderr, "%s: line %d: %s\n", fileName, Cminus_lineno, s);}

int Cminus_wrap() {return 1;}

// Initializes file
static void initialize(char* inputFileName) {
	Cminus_in = fopen(inputFileName, "r");
	if (Cminus_in == NULL) {
		fprintf(stderr, "Error: Could not open file %s\n", inputFileName);
		exit(-1);
	}

	char* dotChar = rindex(inputFileName, '.');
	int endIndex = strlen(inputFileName) - strlen(dotChar);
	char *sub = substr(inputFileName, 0, endIndex);
	char *outputFileName = nssave(2, sub, ".s");
	stdout = freopen(outputFileName, "w", stdout);
	free(sub);
	if (stdout == NULL) {
		fprintf(stderr, "Error: Could not open file %s\n", outputFileName);
		free(outputFileName);
		exit(-1);
	}
	free(outputFileName);
}

// Cleans up malloced variables
static void finalize() {
    fclose(Cminus_in);
    fclose(stdout);
	SymKill(symtab);
	Cminus_lex_destroy();
}

// Runs the program, initializes and cleans up
int main(int argc, char** argv) {	
	fileName = argv[1];
	initialize(fileName);
	symtab = SymInit(SYMTABLE_SIZE);
    Cminus_parse();
  	finalize();
  	return 0;
}

/******************END OF C ROUTINES**********************/
