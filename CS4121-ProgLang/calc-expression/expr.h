/*
expr.h defines the structure of an expression node,
and the operations that can be performed upon it.
Note some things about this file that you should emulate:
- Every symbol in expr.[ch] begins with expr_.
- Use enumerations to define variant types.
- Build complex trees one node at a time.
- Define methods with recurse over those trees.
*/

#ifndef EXPR_H
#define EXPR_H

typedef enum {
	EXPR_ADD,
	EXPR_SUBTRACT,
	EXPR_DIVIDE,
	EXPR_MULTIPLY,
	EXPR_VALUE,
	EXPR_SIN,
	EXPR_COS
} expr_t;

struct expr {
       expr_t kind;
       int value;
       struct expr *left;
       struct expr *right;
};

struct expr * expr_create(expr_t kind, struct expr *left, struct expr *right);
struct expr * expr_create_value(int value);

void          expr_print(struct expr *e);
void          expr_delete(struct expr *e);
float         expr_evaluate(struct expr *e);

// Define the maximum number of buckets in the hash table
#define TABLE_SIZE 100

// Define the structure for a key-value pair
struct KeyValuePair {
    char* key;
    float value;
    struct KeyValuePair* next; // Pointer to the next item in the chain
};

struct SymbolTable {
    struct KeyValuePair* table[TABLE_SIZE]; // Array of pointers to key-value pairs
};

struct KeyValuePair * insert(struct SymbolTable* ht, const char* key, float value);
struct KeyValuePair * lookup(struct SymbolTable* ht, const char* key);
struct KeyValuePair * getAddr_symTab(struct SymbolTable* tab, char* text, int val);

void destroyHashTable(struct SymbolTable* ht);
#endif
