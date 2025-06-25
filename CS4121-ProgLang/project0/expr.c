#include "expr.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// Create one node in an expression tree and return the structure.
struct expr * expr_create(expr_t kind, struct expr *left, struct expr *right, char *key, int value) {
	struct expr *e = malloc(sizeof(*e));

	e->kind = kind;
	e->left = left;
	e->right = right;
	e->value = value;
	e->key = key;

	return e;
}

// Recursively delete an expression tree.
void expr_delete(struct expr *e) {
	if (!e) return;
	expr_delete(e->left);
	expr_delete(e->right);
	free(e);
}

// Recursively print an expression tree by performing an in-order traversal of the tree, printing the current node between the left and right nodes.
void expr_print(struct expr *e) {
	if (!e) return;
	printf("(");
	expr_print(e->left);

	switch (e->kind) {
		case EXPR_ADD:
			printf("+");
			break;
		case EXPR_SUBTRACT:
			printf("-");
			break;
		case EXPR_MULTIPLY:
			printf("*");
			break;
		case EXPR_DIVIDE:
			printf("/");
			break;
		case EXPR_VALUE:
			printf("%d", e->value);
			break;
		case EXPR_SIN:
			printf("sin ");
			break;
		case EXPR_COS:
			printf("cos ");
			break;	
		case EXPR_EQU:
			printf("var %s = ", e->key);	
			break;
	}

	expr_print(e->right);
	printf(")");
}

// Recursively evaluate an expression by performing the desired operation and returning it up the tree.
float expr_evaluate(struct expr *e) {
	if (!e) return 0;

	float l = expr_evaluate(e->left);
	float r = expr_evaluate(e->right);

	switch (e->kind) {
		case EXPR_ADD:
			return l + r;
		case EXPR_SUBTRACT:
			return l - r;
		case EXPR_MULTIPLY:
			return l * r;
		case EXPR_DIVIDE:
			if (r == 0) {
				printf("runtime error: divide by zero\n");
				exit(1);
			}
			return l / r;	
		case EXPR_VALUE:
			return e->value;
		case EXPR_SIN:
		    printf("sin( %f )\n", r);
		    return sin(r);
		case EXPR_COS:
		    printf("cos( %f )\n", r);
			return cos(r);
		case EXPR_EQU:
			return e->value;
	}

	return 0;
}

extern struct SymbolTable symtab;

// Hash function to convert a string key into an index
unsigned int hash(const char* key) {
    unsigned int hash = 0;

    while (*key) {hash = (hash * 31) + (*key++);}

    return hash % TABLE_SIZE;
}

// Function to create a new key-value pair
struct KeyValuePair* createKeyValuePair(const char* key, int value) {
    struct KeyValuePair* pair = (struct KeyValuePair*) malloc(sizeof(struct KeyValuePair));
    
	if (pair) {
        pair->key = strdup(key);
        pair->value = value;
        pair->next = NULL;
    }

    return pair;
}

// Function to insert a key-value pair into the hash table
struct KeyValuePair * insert(struct SymbolTable* ht, const char* key, int value) {
    unsigned int index = hash(key);

    if (!ht->table[index]) {
		struct KeyValuePair* newPair = createKeyValuePair(key, value);
        ht->table[index] = newPair;
		return newPair;
	} else {
        struct KeyValuePair* current = ht->table[index];
		while (current) {
			if (strcmp(current->key, key) == 0) {
                current->value = value;
				return current;
            }
            if (!current->next) {
				struct KeyValuePair* newPair = createKeyValuePair(key, value);
                current->next = newPair;
				return newPair;
            }
            current = current->next;
		}
	}
    return NULL;
}

// Function to look up a value by key
struct KeyValuePair * lookup(struct SymbolTable* ht, const char* key) {
    unsigned int index = hash(key);
    struct KeyValuePair * current = ht->table[index];

    while (current) {
        if (strcmp(current->key, key) == 0) {return current;}
		current = current->next;
    }

    return NULL;
}

struct KeyValuePair* getAddr_symTab(struct SymbolTable *tab, char *name, int val) {
	struct KeyValuePair* p = lookup(tab, name);
	if (p == NULL) {p = insert(tab, name, val);}
	return p;   
}

// Function to free memory used by the hash table
void destroyHashTable(struct SymbolTable* ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        struct KeyValuePair* current = ht->table[i];
        while (current) {
            struct KeyValuePair* temp = current;
            current = current->next;
            free(temp->key);
            free(temp);
        }
    }
}
