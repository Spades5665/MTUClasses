#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <util/string_utils.h>
#include <util/symtab.h>
#include <util/dlink.h>
#include "reg.h"
#include "codegen.h"
#include "symfields.h"
#include "types.h"



void genMain() {
    char *inst = nssave(1, ".text\n.globl main\nmain:\tnop");
    printf("%s\n", inst);
    return inst;
}

void genEnd() {
    char *inst = nssave(1, "li $v0, 10\nsyscall");
    printf("%s\n", inst);
}

void genSpace(int num) {
    //printf("sw $fp, ($sp)\nmove $fp, $sp\nsub $sp, $sp, %d\n", num);
    char *inst = nssave(4, "sw $fp, ($sp)\nmove $fp, $sp\nsub $sp, $sp, ");
    printf("%s\n", inst);
}

void genString(char * string) {
    char *inst = nssave(4, "str: .asciiz ", "\"", string, "\"");
    printf("%s\n", inst);
}