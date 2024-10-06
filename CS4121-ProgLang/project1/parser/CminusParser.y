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
%token FLTCON
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
						printf("<Program>           -> <Procedures>\n");
					}
				| DeclList Procedures
					{
						printf("<Program>           -> <DeclList> <Procedures>\n");
					}
				;

Procedures 		: ProcedureDecl Procedures
					{
						printf("<Procedures>        -> <ProcedureDecl> <Procedures>\n");
					}
				|
					{
						printf("<Procedures>        -> epsilon\n");
					}
				;

ProcedureDecl 	: ProcedureHead ProcedureBody
					{
						printf("<ProcedureDecl>     -> <ProcedureHead> <ProcedureBody>\n");
					}
				;

ProcedureHead 	: FunctionDecl DeclList 
					{
						printf("<ProcedureHead>     -> <FunctionDecl> <DeclList>\n");
					}
				| FunctionDecl
					{
						printf("<ProcedureHead>     -> <FunctionDecl>\n");
					}
				;

FunctionDecl 	:  Type IDENTIFIER LPAREN RPAREN LBRACE 
					{
						printf("<FunctionDecl>      -> <Type> <IDENTIFIER> <LP> <RP> <LBR>\n"); 
					}
				;

ProcedureBody 	: StatementList RBRACE
					{
						printf("<ProcedureBody>     -> <StatementList> <RBR>\n");
					}
				;

DeclList    	: Type IdentifierList  SEMICOLON 
					{
						printf("<DeclList>          -> <Type> <IdentifierList> <SC>\n");
					}		
				| DeclList Type IdentifierList SEMICOLON
					{
						printf("<DeclList>          -> <DeclList> <Type> <IdentifierList> <SC>\n");
					}
				;

IdentifierList  : VarDecl  
		            {
			            printf("<IdentifierList>    -> <VarDecl>\n");
		            }		
            	| IdentifierList COMMA VarDecl
		        	{
			        	printf("<IdentifierList>    -> <IdentifierList> <CM> <VarDecl>\n");
		    		}
        		;

VarDecl 		: IDENTIFIER
					{ 				
						//printf("ID: %s\n", $1);
						printf("<VarDecl>           -> <IDENTIFIER>\n");
					}
				| IDENTIFIER LBRACKET INTCON RBRACKET
					{
						printf("<VarDecl>           -> <IDENTIFIER> <LBK> <INTCON> <RBK>\n");
					}
				;

Type     		: INTEGER 
					{ 
						printf("<Type>              -> <INTEGER>\n");
					}
                ;

Statement 		: Assignment
					{ 
						printf("<Statement>         -> <Assignment>\n");
					}
				| IfStatement
					{ 
						printf("<Statement>         -> <IfStatement>\n");
					}
				| WhileStatement
					{ 
						printf("<Statement>         -> <WhileStatement>\n");
					}
				| IOStatement 
					{ 
						printf("<Statement>         -> <IOStatement>\n");
					}
				| ReturnStatement
					{ 
						printf("<Statement>         -> <ReturnStatement>\n");
					}
				| ExitStatement	
					{ 
						printf("<Statement>         -> <ExitStatement>\n");
					}
				| CompoundStatement
					{ 
						printf("<Statement>         -> <CompoundStatement>\n");
					}
                ;

Assignment      : Variable ASSIGN Expr SEMICOLON
					{
						printf("<Assignment>        -> <Variable> <ASSIGN> <Expr> <SC>\n");
					}
                ;
				
IfStatement		: IF TestAndThen ELSE CompoundStatement
					{
						printf("<IfStatement>       -> <IF> <TestAndThen> <ELSE> <CompoundStatement>\n");
					}
				| IF TestAndThen
					{
						printf("<IfStatement>       -> <IF> <TestAndThen>\n");
					}
				;
		
				
TestAndThen		: Test CompoundStatement
					{
						printf("<TestAndThen>       -> <Test> <CompoundStatement>\n");
					}
				;
				
Test			: LPAREN Expr RPAREN
					{
						printf("<Test>              -> <LP> <Expr> <RP>\n");
					}
				;
	

WhileStatement  : WhileToken WhileExpr Statement
					{
						printf("<WhileStatement>    -> <WhileToken> <WhileExpr> <Statement>\n");
					}
                ;
                
WhileExpr		: LPAREN Expr RPAREN
					{
						printf("<WhileExpr>         -> <LP> <Expr> <RP>\n");
					}
				;
				
WhileToken		: WHILE
					{
						printf("<WhileToken>        -> <WHILE>\n");
					}
				;


IOStatement     : READ LPAREN Variable RPAREN SEMICOLON
					{
						printf("<IOStatement>       -> <READ> <LP> <Variable> <RP> <SC>\n");
					}
                | WRITE LPAREN Expr RPAREN SEMICOLON
					{
						printf("<IOStatement>       -> <WRITE> <LP> <Expr> <RP> <SC>\n");
					}
                | WRITE LPAREN StringConstant RPAREN SEMICOLON         
					{
						printf("<IOStatement>       -> <WRITE> <LP> <StringConstant> <RP> <SC>\n");
					}
                ;

ReturnStatement : RETURN Expr SEMICOLON
					{
						printf("<ReturnStatement>   -> <RETURN> <Expr> <SC>\n");
					}
                ;

ExitStatement 	: EXIT SEMICOLON
					{
						printf("<ExitStatement>     -> <EXIT> <SC>\n");
					}
				;

CompoundStatement: LBRACE StatementList RBRACE
					{
						printf("<CompoundStatement> -> <LBR> <StatementList> <RBR>\n");
					}
                ;

StatementList   : Statement
					{		
						printf("<StatementList>     -> <Statement>\n");
					}
                | StatementList Statement
					{		
						printf("<StatementList>     -> <StatementList> <Statement>\n");
					}
                ;

Expr            : SimpleExpr
					{
						printf("<Expr>              -> <SimpleExpr>\n");
					}
                | Expr OR SimpleExpr 
					{
						printf("<Expr>              -> <Expr> <OR> <SimpleExpr>\n");
					}
                | Expr AND SimpleExpr 
					{
						printf("<Expr>              -> <Expr> <AND> <SimpleExpr>\n");
					}
                | NOT SimpleExpr 
					{
						printf("<Expr>              -> <NOT> <SimpleExpr>\n");
					}
                ;

SimpleExpr		: AddExpr
					{
						printf("<SimpleExpr>        -> <AddExpr>\n");
					}
                | SimpleExpr EQ AddExpr
					{
						printf("<SimpleExpr>        -> <SimpleExpr> <EQ> <AddExpr>\n");
					}
                | SimpleExpr NE AddExpr
					{
						printf("<SimpleExpr>        -> <SimpleExpr> <NE> <AddExpr>\n");
					}
                | SimpleExpr LE AddExpr
					{
						printf("<SimpleExpr>        -> <SimpleExpr> <LE> <AddExpr>\n");
					}
                | SimpleExpr LT AddExpr
					{
						printf("<SimpleExpr>        -> <SimpleExpr> <LT> <AddExpr>\n");
					}
                | SimpleExpr GE AddExpr
					{
						printf("<SimpleExpr>        -> <SimpleExpr> <GE> <AddExpr>\n");
					}
                | SimpleExpr GT AddExpr
					{
						printf("<SimpleExpr>        -> <SimpleExpr> <GT> <AddExpr>\n");
					}
                ;

AddExpr			:  MulExpr            
					{
						printf("<AddExpr>           -> <MulExpr>\n");
					}
                |  AddExpr PLUS MulExpr
					{
						printf("<AddExpr>           -> <AddExpr> <PLUS> <MulExpr>\n");
					}
                |  AddExpr MINUS MulExpr
					{
						printf("<AddExpr>           -> <AddExpr> <MINUS> <MulExpr>\n");
					}
                ;

MulExpr			:  Factor
					{
						printf("<MulExpr>           -> <Factor>\n");
					}
                |  MulExpr TIMES Factor
					{
						printf("<MulExpr>           -> <MulExpr> <TIMES> <Factor>\n");
					}
                |  MulExpr DIVIDE Factor
					{
						printf("<MulExpr>           -> <MulExpr> <DIVIDE> <Factor>\n");
					}		
                ;
				
Factor          : Variable
					{ 
						printf("<Factor>            -> <Variable>\n");
					}
                | Constant
					{ 
						printf("<Factor>            -> <Constant>\n");
					}
                | IDENTIFIER LPAREN RPAREN
					{	
						printf("<Factor>            -> <IDENTIFIER> <LP> <RP>\n");
					}
         		| LPAREN Expr RPAREN
					{
						printf("<Factor>            -> <LP> <Expr> <RP>\n");
					}
                ;  

Variable        : IDENTIFIER
					{
						printf("<Variable>          -> <IDENTIFIER>\n");
					}
                | IDENTIFIER LBRACKET Expr RBRACKET    
					{
						printf("<Variable>          -> <IDENTIFIER> <LBK> <Expr> <RBK>\n");
					}
                ;			       

StringConstant 	: STRING
					{ 
						//printf("String in: %s\n", $1);
						printf("<StringConstant>    -> <STRING>\n");
					}
                ;

Constant        : INTCON
					{ 
						//printf("Int: %s\n", $1);
						printf("<Constant>          -> <INTCON>\n");
					}
                | FLTCON
					{ 
						//printf("Float: %s\n", $1);
						printf("<Constant>          -> <INTCON>\n");
					}
				;

%%

/********************C ROUTINES *********************************/

void Cminus_error(const char *s) {fprintf(stderr, "%s: line %d: %s\n", fileName, Cminus_lineno, s);}

int Cminus_wrap() {return 1;}

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
}

static void finalize() {
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

/******************END OF C ROUTINES**********************/
