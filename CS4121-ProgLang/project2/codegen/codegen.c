#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <util/string_utils.h>
#include "../util/symtab.h"
#include <util/dlink.h>
#include "reg.h"
#include "codegen.h"
#include "symfields.h"
#include "types.h"

void genMain(DLinkList * instructions) {
    char *inst = nssave(3,  ".text\n",
                            ".globl main\n", 
                            "main:\tnop"
                        );
    dlinkPush(dlinkNodeAlloc((Generic) inst), instructions);
}

void genSpace(DLinkList * instructions, int n) {
    char num[12];
    sprintf(num, "%d", n);
    
    char *inst = nssave(4,  "sw $gp, ($sp)\n", 
                            "move $gp, $sp\n", 
                            "add $sp, $sp, ", num
                        );
    dlinkAppend(instructions, dlinkNodeAlloc((Generic) inst));
}

void genEnd(DLinkList * instructions) {
    char *inst = nssave(2,  "li $v0, 10\n",
                            "syscall"
                        );
    dlinkAppend(instructions, dlinkNodeAlloc((Generic) inst));
}

int genString(DLinkList * declarations, SymTable symtab, int index) {
    char name[20];
    sprintf(name, ".string%d", index);

    char *inst = nssave(5, name, ": .asciiz ", "\"", (char *) SymGetFieldByIndex(symtab, index, SYM_NAME_FIELD), "\"");
    dlinkAppend(declarations, dlinkNodeAlloc((Generic) inst));

    return index;
}

void genNewLine(DLinkList * instructions) {
    char *inst = nssave(3, "la $a0, .newLine\n",
                            "li $v0, 4\n",
                            "syscall"
                        );
    dlinkAppend(instructions, dlinkNodeAlloc((Generic) inst));
}

int genInt(DLinkList * instructions, SymTable regSymTab, int n) {
    int resultInd = getFreeIntegerRegisterIndex(regSymTab);
    char * resultReg = getIntegerRegisterName(resultInd);

    char num[12];
    sprintf(num, "%d", n);

    char *inst = nssave(4, "li ", resultReg, ", ", num);
    dlinkAppend(instructions, dlinkNodeAlloc((Generic) inst));

    return resultInd;
}

void genAssign(DLinkList * instructions, SymTable regSymTab, int index, int resultInd, int offset) {
    int freeInd = getFreeIntegerRegisterIndex(regSymTab);
    char * freeReg = getIntegerRegisterName(freeInd);
    char * resultReg = getIntegerRegisterName(resultInd);
    
    char num[12];
    sprintf(num, "%d", offset);

    char *inst = nssave(11,  "add ", freeReg, ", $gp, ", num, "\n",
                            "sw ", resultReg, ", ", "0(", freeReg, ")"
                        );
    dlinkAppend(instructions, dlinkNodeAlloc((Generic) inst));

    freeIntegerRegister(freeInd);
    freeIntegerRegister(resultInd);
}

int genVal(DLinkList * instructions, SymTable regSymTab, int index, int offset) {
    int resultInd = getFreeIntegerRegisterIndex(regSymTab);
    int freeInd = getFreeIntegerRegisterIndex(regSymTab);
    char * resultReg = getIntegerRegisterName(resultInd);
    char * freeReg = getIntegerRegisterName(freeInd);
    
    char num[12];
    sprintf(num, "%d", offset);

    char *inst = nssave(11,  "add ", freeReg, ", $gp, ", num, "\n",
                            "lw ", resultReg, ", ", "0(", freeReg, ")"
                        );
    dlinkAppend(instructions, dlinkNodeAlloc((Generic) inst));

    freeIntegerRegister(freeInd);
    return resultInd;
}

int genArith(DLinkList * instructions, SymTable regSymTab, int leftInd, int rightInd, char * type) {  
    int resultInd = getFreeIntegerRegisterIndex(regSymTab);
    char * resultReg = getIntegerRegisterName(resultInd);
    char * leftReg = getIntegerRegisterName(leftInd);
    char * rightReg = getIntegerRegisterName(rightInd);

    char *inst = nssave(7, type, " ", resultReg, ", ", leftReg, ", ", rightReg);
    dlinkAppend(instructions, dlinkNodeAlloc((Generic) inst));

    freeIntegerRegister(leftInd);
    freeIntegerRegister(rightInd);
    return resultInd;
}

void genWriteStr(DLinkList * instructions, int index) {
    char name[20];
    sprintf(name, ".string%d", index);
    
    char *inst = nssave(5,  "la $a0, ", name, "\n",
                            "li $v0, 4\n",
                            "syscall"
                        );
    dlinkAppend(instructions, dlinkNodeAlloc((Generic) inst));
    genNewLine(instructions);
}

void genWriteNum(DLinkList * instructions, int resultInd) {
    char * resultReg = getIntegerRegisterName(resultInd);
    char *inst = nssave(5,  "move $a0, ", resultReg, "\n",
                            "li $v0, 1\n",
                            "syscall"
                        );
    dlinkAppend(instructions, dlinkNodeAlloc((Generic) inst));
    genNewLine(instructions);

    freeIntegerRegister(resultInd);
}

void genRead(DLinkList * instructions, SymTable regSymTab, int index, int offset) {
    int freeInd = getFreeIntegerRegisterIndex(regSymTab);
    char * freeReg = getIntegerRegisterName(freeInd);
    
    char *inst = nssave(5,  "li $v0, 5\n",
                            "syscall\n",
                            "move ", freeReg, ", $v0"
                        );
    dlinkAppend(instructions, dlinkNodeAlloc((Generic) inst));
    genAssign(instructions, regSymTab, index, freeInd, offset);
}
