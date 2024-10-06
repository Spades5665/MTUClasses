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

SymTable symtab;

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

%union {
	char *text;
	int    num;
}

%type <text> STRING IDENTIFIER StringConstant VarDecl Variable IdentifierList DeclList
%type <num>  INTCON Constant Factor MulExpr AddExpr SimpleExpr Expr

/***********************PRODUCTIONS****************************/
%%
Program			: Procedures 
					{
						//printf("<Program>           -> <Procedures>\n");
					}
				| DeclList Procedures
					{
						//printf("<Program>           -> <DeclList> <Procedures>\n");
					}
				;

Procedures 		: ProcedureDecl Procedures
					{
						//printf("<Procedures>        -> <ProcedureDecl> <Procedures>\n");
					}
				|
					{
						//printf("<Procedures>        -> epsilon\n");
					}
				;

ProcedureDecl 	: ProcedureHead ProcedureBody
					{
						//printf("<ProcedureDecl>     -> <ProcedureHead> <ProcedureBody>\n");
					}
				;

ProcedureHead 	: FunctionDecl DeclList 
					{
						//printf("<ProcedureHead>     -> <FunctionDecl> <DeclList>\n");
					}
				| FunctionDecl
					{
						//printf("<ProcedureHead>     -> <FunctionDecl>\n");
					}
				;

FunctionDecl 	:  Type IDENTIFIER LPAREN RPAREN LBRACE 
					{
						//printf("<FunctionDecl>      -> <Type> <IDENTIFIER> <LP> <RP> <LBR>\n"); 
						free($2);
					}
				;

ProcedureBody 	: StatementList RBRACE
					{
						//printf("<ProcedureBody>     -> <StatementList> <RBR>\n");
					}
				;

DeclList    	: Type IdentifierList SEMICOLON 
					{
						//printf("<DeclList>          -> <Type> <IdentifierList> <SC>\n");
						char* id = strtok($2, ",");
					
						while (id != NULL) {
							SymIndex(symtab, id);
							id = strtok(NULL, ",");
						}
						free(id);
						free($2);
					}		
				| DeclList Type IdentifierList SEMICOLON
					{
						//printf("<DeclList>          -> <DeclList> <Type> <IdentifierList> <SC>\n");
						char* id = strtok($3, ",");
					
						while (id != NULL) {
							SymIndex(symtab, id);
							id = strtok(NULL, ",");
						}
						free(id);
						free($3);
					}
				;

IdentifierList  : VarDecl  
		            {
			            //printf("<IdentifierList>    -> <VarDecl>\n");
						$$ = $1;
		            }		
            	| IdentifierList COMMA VarDecl
		        	{
			        	//printf("<IdentifierList>    -> <IdentifierList> <CM> <VarDecl>\n");    
						char *copy = (char *)malloc((strlen($1) + strlen($3) + 2) * sizeof(char));
						strcpy(copy, $1);
						strcat(copy, ",");
						strcat(copy, $3); 
						free($1);
						free($3);
						$$ = copy;
		    		}
        		;

VarDecl 		: IDENTIFIER
					{ 
						//printf("<VarDecl>           -> <IDENTIFIER\n");
						$$ = $1;
					}
				| IDENTIFIER LBRACKET INTCON RBRACKET
					{
						printf("<VarDecl>           -> <IDENTIFIER> <LBK> <INTCON> <RBK>\n");
					}
				;

Type     		: INTEGER 
					{ 
						//printf("<Type>              -> <INTEGER>\n");
					}
                ;

Statement 		: Assignment
					{ 
						//printf("<Statement>         -> <Assignment>\n");
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
						//printf("<Statement>         -> <IOStatement>\n");
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
						//printf("<Assignment>        -> <Variable> <ASSIGN> <Expr> <SC>\n");
						if (SymQueryIndex(symtab, $1) == -1) {
							fprintf(stderr, "ERROR --- Variable: %s not declared\n", $1);
							exit(1);
						}
						SymPutField(symtab, $1, $1, $3);
						free($1);
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
						//printf("<IOStatement>       -> <READ> <LP> <Variable> <RP> <SC>\n");
						int val;
						scanf("%d", &val);
						SymPutField(symtab, $3, $3, val);
						free($3);
					}
                | WRITE LPAREN Expr RPAREN SEMICOLON
					{
						//printf("<IOStatement>       -> <WRITE> <LP> <Expr> <RP> <SC>\n");
						printf("%d\n", $3);
					}
                | WRITE LPAREN StringConstant RPAREN SEMICOLON         
					{
						//printf("<IOStatement>       -> <WRITE> <LP> <StringConstant> <RP> <SC>\n");
						printf("%s\n", $3);
						free($3);
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
						//printf("<StatementList>     -> <Statement>\n");
					}
                | StatementList Statement
					{		
						//printf("<StatementList>     -> <StatementList> <Statement>\n");
					}
                ;

Expr            : SimpleExpr
					{
						//printf("<Expr>              -> <SimpleExpr>\n");
						$$ = $1;
					}
                | Expr OR SimpleExpr 
					{
						//printf("<Expr>              -> <Expr> <OR> <SimpleExpr>\n");
						$$ = $1 || $3;
					}
                | Expr AND SimpleExpr 
					{
						//printf("<Expr>              -> <Expr> <AND> <SimpleExpr>\n");
						$$ = $1 && $3;
					}
                | NOT SimpleExpr 
					{
						//printf("<Expr>              -> <NOT> <SimpleExpr>\n");
						$$ = !$2;
					}
                ;

SimpleExpr		: AddExpr
					{
						//printf("<SimpleExpr>        -> <AddExpr>\n");
						$$ = $1;
					}
                | SimpleExpr EQ AddExpr
					{
						//printf("<SimpleExpr>        -> <SimpleExpr> <EQ> <AddExpr>\n");
						$$ = $1 == $3;
					}
                | SimpleExpr NE AddExpr
					{
						//printf("<SimpleExpr>        -> <SimpleExpr> <NE> <AddExpr>\n");
						$$ = $1 != $3;
					}
                | SimpleExpr LE AddExpr
					{
						//printf("<SimpleExpr>        -> <SimpleExpr> <LE> <AddExpr>\n");
						$$ = $1 <= $3;
					}
                | SimpleExpr LT AddExpr
					{
						//printf("<SimpleExpr>        -> <SimpleExpr> <LT> <AddExpr>\n");
						$$ = $1 < $3;
					}
                | SimpleExpr GE AddExpr
					{
						//printf("<SimpleExpr>        -> <SimpleExpr> <GE> <AddExpr>\n");
						$$ = $1 >= $3;
					}
                | SimpleExpr GT AddExpr
					{
						//printf("<SimpleExpr>        -> <SimpleExpr> <GT> <AddExpr>\n");
						$$ = $1 > $3;
					}
                ;

AddExpr			:  MulExpr            
					{
						//printf("<AddExpr>           -> <MulExpr>\n");
						$$ = $1;
					}
                |  AddExpr PLUS MulExpr
					{
						//printf("<AddExpr>           -> <AddExpr> <PLUS> <MulExpr>\n");
						$$ = $1 + $3;
					}
                |  AddExpr MINUS MulExpr
					{
						//printf("<AddExpr>           -> <AddExpr> <MINUS> <MulExpr>\n");
						$$ = $1 - $3;
					}
                ;

MulExpr			:  Factor
					{
						//printf("<MulExpr>           -> <Factor>\n");
						$$ = $1;
					}
                |  MulExpr TIMES Factor
					{
						//printf("<MulExpr>           -> <MulExpr> <TIMES> <Factor>\n");
						$$ = $1 * $3;
					}
                |  MulExpr DIVIDE Factor
					{
						//printf("<MulExpr>           -> <MulExpr> <DIVIDE> <Factor>\n");
						if ($3 == 0) {
							fprintf(stderr, "ERROR --- Hey DUMBASS no divide by 0\n");
							exit(1);
						}
						$$ = $1 / $3;
					}		
                ;
				
Factor          : Variable
					{ 
						//printf("<Factor>            -> <Variable>\n");
						if (SymGetField(symtab, $1, $1) == 0) {
							fprintf(stderr, "ERROR --- Variable: %s not initialized\n", $1);
							exit(1);
						}
						$$ = (int) SymGetField(symtab, $1, $1);
						free($1);
					}
                | Constant
					{ 
						//printf("<Factor>            -> <Constant>\n");
						$$ = $1;
					}
                | IDENTIFIER LPAREN RPAREN
					{	
						printf("<Factor>            -> <IDENTIFIER> <LP> <RP>\n");
					}
         		| LPAREN Expr RPAREN
					{
						//printf("<Factor>            -> <LP> <Expr> <RP>\n");
						$$ = $2;
					}
                ;  

Variable        : IDENTIFIER
					{
						//printf("<Variable>          -> <IDENTIFIER>\n");
						$$ = $1;
					}
                | IDENTIFIER LBRACKET Expr RBRACKET    
					{
						printf("<Variable>          -> <IDENTIFIER> <LBK> <Expr> <RBK>\n");
					}
                ;			       

StringConstant 	: STRING
					{
						//printf("<StringConstant>    -> <STRING>\n");
						$$ = $1;
					}
                ;

Constant        : INTCON
					{
						//printf("<Constant>          -> <INTCON>\n");
						$$ = $1;
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

static void finalize() {
    fclose(Cminus_in);
    fclose(stdout);
	SymKill(symtab);
	Cminus_lex_destroy();
}

int main(int argc, char** argv) {	
	fileName = argv[1];
	initialize(fileName);
	symtab = SymInit(SYMTABLE_SIZE);
    Cminus_parse();
  	finalize();
  	return 0;
}

/******************END OF C ROUTINES**********************/
