
#include "expr.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/*
Create one node in an expression tree and return the structure.
*/

struct expr * expr_create( expr_t kind, struct expr *left, struct expr *right )
{
	/* Shortcut: sizeof(*e) means "the size of what e points to" */
	struct expr *e = malloc(sizeof(*e));

	e->kind = kind;
	e->value = 0;
	e->left = left;
	e->right = right;

	return e;
}

struct expr * expr_create_value( int value )
{
	struct expr *e = expr_create(EXPR_VALUE,0,0);
	e->value = value;
	return e;
}

/*
Recursively delete an expression tree.
*/

void expr_delete( struct expr *e )
{
	/* Careful: Stop on null pointer. */
	if(!e) return;
	expr_delete(e->left);
	expr_delete(e->right);
	free(e);
}

/*
Recursively print an expression tree by performing an
in-order traversal of the tree, printing the current node
between the left and right nodes.
*/

void expr_print( struct expr *e )
{
	/* Careful: Stop on null pointer. */
	if(!e) return;

	printf("(");

	expr_print(e->left);

	switch(e->kind) {
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
			printf("%d",e->value);
			break;
		case EXPR_SIN:
			printf("sin " );
			break;
		case EXPR_COS:
			printf("cos " );
			break;		
	}

	expr_print(e->right);
	printf(")");
}

/*
Recursively evaluate an expression by performing
the desired operation and returning it up the tree.
*/

float expr_evaluate( struct expr *e )
{
	/* Careful: Return zero on null pointer. */
	if(!e) return 0;

	float l = expr_evaluate(e->left);
	float r = expr_evaluate(e->right);

	switch(e->kind) {
		case EXPR_ADD:
			return l+r;
		case EXPR_SUBTRACT:
			return l-r;
		case EXPR_MULTIPLY:
			return l*r;
		case EXPR_DIVIDE:
			if(r==0) {
				printf("runtime error: divide by zero\n");
				exit(1);
			}
			return l/r;	
		case EXPR_VALUE:
			return e->value;
		case EXPR_SIN:
		   printf("sin( %f )\n",r);
		   return sin(r);
		case EXPR_COS:
		   printf("cos( %f )\n",r);
		   return cos(r);
		   
	}

	return 0;
}


extern struct SymbolTable symtab;

// Hash function to convert a string key into an index
unsigned int hash(const char* key) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash * 31) + (*key++);
    }
    return hash % TABLE_SIZE;
}

// Function to create a new key-value pair
struct KeyValuePair* createKeyValuePair(const char* key, int value) {
    struct KeyValuePair* pair = (struct KeyValuePair*)malloc(sizeof(struct KeyValuePair));
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
    struct KeyValuePair* newPair = createKeyValuePair(key, value);

    if (!ht->table[index]) {
        // No collision, insert at the beginning of the chain
        ht->table[index] = newPair;
        printf("index is %u\n", index);
	} else {
        // Collision, insert at the end of the chain
        struct KeyValuePair* current = ht->table[index];
        while (current->next) {
            current = current->next;
            
		}
        
		current->next = newPair;
        printf("Insert( ) returns index %d key %s\n,", index,ht->table[index]->key);
	}
    return newPair;
}

// Function to look up a value by key
struct KeyValuePair * lookup(struct SymbolTable* ht, const char* key) {
    unsigned int index = hash(key);
    struct KeyValuePair * current = ht->table[index];

    while (current) {
        if (strcmp(current->key, key) == 0) {
            return current ;
        }
		current = current->next;
    }

    // Key not found, return a default value (you can choose your own behavior)
    return NULL;
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


struct KeyValuePair* getAddr_symTab(struct SymbolTable * tab, char *name){
  
   struct KeyValuePair * p = lookup(tab, name);
   if( p == NULL )
      p = insert(tab, name, 0);
   
   return p;   
}





