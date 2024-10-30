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

// Generates the beginning of the mips file under .text
void genMain(DLinkList * instructions) {
    char *inst = nssave(3,  ".text\n",
                            ".globl main\n", 
                            "main:\tnop"
                        );
    dlinkPush(dlinkNodeAlloc((Generic) inst), instructions);
}

// Generates the space allocation instructions
void genSpace(DLinkList * instructions, int n) {
    char num[12];
    sprintf(num, "%d", n);
    
    char *inst = nssave(4,  "sw $gp, ($sp)\n", 
                            "move $gp, $sp\n", 
                            "add $sp, $sp, ", num
                        );
    dlinkAppend(instructions, dlinkNodeAlloc((Generic) inst));
}

// Generates the exit commands
void genEnd(DLinkList * instructions) {
    char *inst = nssave(2,  "li $v0, 10\n",
                            "syscall"
                        );
    dlinkAppend(instructions, dlinkNodeAlloc((Generic) inst));
}

// Generates a unqiue string variable for each literal read in
int genString(DLinkList * declarations, SymTable symtab, int index) {
    char name[20];
    sprintf(name, ".string%d", index);

    char *inst = nssave(5, name, ": .asciiz ", "\"", (char *) SymGetFieldByIndex(symtab, index, SYM_NAME_FIELD), "\"");
    dlinkAppend(declarations, dlinkNodeAlloc((Generic) inst));

    return index;
}

// Generates a new line
void genNewLine(DLinkList * instructions) {
    char *inst = nssave(3, "la $a0, .newLine\n",
                            "li $v0, 4\n",
                            "syscall"
                        );
    dlinkAppend(instructions, dlinkNodeAlloc((Generic) inst));
}

// Generates a load integer command
int genInt(DLinkList * instructions, SymTable regSymTab, int n) {
    int resultInd = getFreeIntegerRegisterIndex(regSymTab);
    char * resultReg = getIntegerRegisterName(resultInd);

    char num[12];
    sprintf(num, "%d", n);

    char *inst = nssave(4, "li ", resultReg, ", ", num);
    dlinkAppend(instructions, dlinkNodeAlloc((Generic) inst));

    return resultInd;
}

// Generates a variable assign command structure
void genAssign(DLinkList * instructions, SymTable regSymTab, int index, int resultInd, int offset) {
    int freeInd = getFreeIntegerRegisterIndex(regSymTab);
    char * freeReg = getIntegerRegisterName(freeInd);
    char * resultReg = getIntegerRegisterName(resultInd);
    
    char num[12];
    sprintf(num, "%d", offset);

    char *inst = nssave(11, "add ", freeReg, ", $gp, ", num, "\n",
                            "sw ", resultReg, ", ", "0(", freeReg, ")"
                        );
    dlinkAppend(instructions, dlinkNodeAlloc((Generic) inst));

    freeIntegerRegister(freeInd);
    freeIntegerRegister(resultInd);
}

// Genereates the commands to retrieve a variables value
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

// Generates instructions that utilize <type> reg0, reg1, reg2, such as: add or and
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

// Generates the command to reverse or not a registers value
int genNot(DLinkList * instructions, SymTable regSymTab, int rightInd) {  
    int resultInd = getFreeIntegerRegisterIndex(regSymTab);
    char * resultReg = getIntegerRegisterName(resultInd);
    char * rightReg = getIntegerRegisterName(rightInd);

    char num[20];
    sprintf(num, "%d", 1);

    char *inst = nssave(6, "xori ", resultReg, ", ", rightReg, ", ", num);
    dlinkAppend(instructions, dlinkNodeAlloc((Generic) inst));

    freeIntegerRegister(rightInd);
    return resultInd;
}

// Generates the commands to find if two registers values are equal
int genEqual(DLinkList * instructions, SymTable regSymTab, int leftInd, int rightInd) {
    int resultInd = getFreeIntegerRegisterIndex(regSymTab);
    int freeInd = getFreeIntegerRegisterIndex(regSymTab);
    char * resultReg = getIntegerRegisterName(resultInd);
    char * freeReg = getIntegerRegisterName(freeInd);
    char * leftReg = getIntegerRegisterName(leftInd);
    char * rightReg = getIntegerRegisterName(rightInd);

    char num[20];
    sprintf(num, "%d", 1);

    char *inst = nssave(13,  "xor ", freeReg, ", ", leftReg, ", ", rightReg, "\n",
                            "sltiu ", resultReg, ", ", freeReg, ", ", num
                        );
    dlinkAppend(instructions, dlinkNodeAlloc((Generic) inst));
    freeIntegerRegister(leftInd);
    freeIntegerRegister(rightInd);
    freeIntegerRegister(freeInd);

    return resultInd;
}

// Generates the opposite of above
int genNotEqual(DLinkList * instructions, SymTable regSymTab, int leftInd, int rightInd) {
    return genNot(instructions, regSymTab, genEqual(instructions, regSymTab, leftInd, rightInd));
}

// Generates the command to find if one value is less than the other
int genLT(DLinkList * instructions, SymTable regSymTab, int leftInd, int rightInd) {
    int resultInd = getFreeIntegerRegisterIndex(regSymTab);
    char * resultReg = getIntegerRegisterName(resultInd);
    char * leftReg = getIntegerRegisterName(leftInd);
    char * rightReg = getIntegerRegisterName(rightInd);

    char num[20];
    sprintf(num, "%d", 1);

    char *inst = nssave(6,  "slt ", resultReg, ", ", leftReg, ", ", rightReg);
    dlinkAppend(instructions, dlinkNodeAlloc((Generic) inst));
    freeIntegerRegister(leftInd);
    freeIntegerRegister(rightInd);

    return resultInd;
}

// Generates Less than or Equal by "oring" genLT and genEqual
int genLE(DLinkList * instructions, SymTable regSymTab, int leftInd, int rightInd) {
    int a = genLT(instructions, regSymTab, leftInd, rightInd);
    int b = genEqual(instructions, regSymTab, leftInd, rightInd);
    return genArith(instructions, regSymTab, a, b, "or");
}

// Generates Greater than by taking the not of LE
int genGT(DLinkList * instructions, SymTable regSymTab, int leftInd, int rightInd) {
    return genNot(instructions, regSymTab, genLE(instructions, regSymTab, leftInd, rightInd));
}

// Generates Greater than or equal by taking the not of LT
int genGE(DLinkList * instructions, SymTable regSymTab, int leftInd, int rightInd) {
    return genNot(instructions, regSymTab, genLT(instructions, regSymTab, leftInd, rightInd));
}

// Generates the instructions to output a string
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

// generates the instructions to output a number
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

// Generates the instructions to input a number
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
