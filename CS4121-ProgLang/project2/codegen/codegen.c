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
    free(inst);
}

void genEnd() {
    char *inst = nssave(1, "li $v0, 10\nsyscall");
    printf("%s\n", inst);
    free(inst);
}

void genSpace(int num) {
    //printf("sw $fp, ($sp)\nmove $fp, $sp\nsub $sp, $sp, %d\n", num);
    char *inst = nssave(4, "sw $fp, ($sp)\nmove $fp, $sp\nsub $sp, $sp, ");
    printf("%s\n", inst);
    free(inst);
}

int genString(SymTable symtab, int index) {
    int counter = 1;
    char name[12];
    sprintf(name, ".string%d", counter);
    SymPutFieldByIndex(symtab, index, SYM_VARNAME_FIELD, (Generic) name);

    char *inst = nssave(4, name, ": .asciiz ", "\"", (char *) SymGetFieldByIndex(symtab, index, SYM_NAME_FIELD), "\"");
    printf("%s\n", inst);
    free(inst);

    return index;
}

int genInt(SymTable regSymTab, int n) {
    int resultInd = getFreeIntegerRegisterIndex(regSymTab);
    char * resultReg = getIntegerRegisterName(resultInd);

    char num[12];
    sprintf(num, "%d", n);

    char *inst = nssave(4, "li ", resultReg, ", ", num);
    printf("%s\n", inst);
    free(inst);

    return resultInd;
}

int genArith(SymTable regSymTab, int leftInd, int rightInd, char * type) {  
    int resultInd = getFreeIntegerRegisterIndex(regSymTab);
    char * resultReg = getIntegerRegisterName(resultInd);
    char * leftReg = getIntegerRegisterName(leftInd);
    char * rightReg = getIntegerRegisterName(rightInd);

    char *inst = nssave(7, type, " ", resultReg, ", ", leftReg, ", ", rightReg);
    printf("%s\n", inst);

    freeIntegerRegister(leftInd);
    freeIntegerRegister(rightInd);
    free(inst);

    return resultInd;
}

void genWriteStr(SymTable symtab, int index) {
    char *inst = nssave(5,  "la $a0, ", (char *) SymGetFieldByIndex(symtab, index, "VariableName"), "\n",
                            "li $v0, 4\n",
                            "syscall"
                        );
    printf("%s\n", inst);

    free(inst);
}

void genNewLine() {
    char *inst1 = nssave(1, ".newLine: .asciiz \"\\n\"");
    char *inst = nssave(3,  "la $a0, .newLine\n",
                            "li $v0, 4\n",
                            "syscall"
                        );
    printf("%s\n", inst);
    
    free(inst);
    free(inst1);
}
