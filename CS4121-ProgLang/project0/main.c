#include <stdio.h>
#include "expr.h"
#include <string.h>
#include <stdlib.h>

/* Clunky: Declare the parse function generated from parser.bison */
extern int yyparse();

/* Clunky: Declare the result of the parser from parser.bison */
extern struct expr * parser_result;

extern FILE *yyin;

// Define the symbol table 
struct SymbolTable symtab;

static void finalize() {
    fclose(yyin);
    fclose(stdout);
    destroyHashTable(&symtab);
}

static void initialize(char* inputFileName) {
	yyin = fopen(inputFileName, "r");

	if (yyin == NULL) {
		fprintf(stderr, "Error: Could not open file %s\n", inputFileName);
		exit(-1);
	}

	char *outputFileName = strcat(inputFileName, ".out");
	stdout = freopen(outputFileName, "w", stdout);
	
	if (stdout == NULL) {
		fprintf(stderr, "Error: Could not open file %s\n", outputFileName);
		exit(-1);
	}
}

int main(int argc, char *argv[]) {
	if (argc < 2) {printf("Usage: ./calc <filename>.out\n"); return 1;}

	char *fileName = argv[1];
	initialize(fileName);
	
	if (yyparse() != 0) {
		printf("parse failed!\n");
		finalize();
		return 1;
	}
	
	finalize();
	return 0;
}
